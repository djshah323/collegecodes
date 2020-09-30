/*
 * ServerMain.c
 *
 *  Created on: Dec 23, 2014
 *      Author: root
 */

#include "pthreads_chatserver.h"

U_MAP user_map;


int main(int c, char* argv[])
{
	void* res;
	int  THREADPOOL  = 0;

	if(c!= 3)
	{
		printf("Usage %s ThreadPoolSize PORT#\n",argv[0]);
		exit(ERR_INVALID_ARGS);
	}

	THREADPOOL = atoi((const char*)(argv[1]));

	//initiate TCP Server

	sServListenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&serverAddr,sizeof(serverAddr));

	serverAddr.sin_family  = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(atoi(argv[2]));

	bind(sServListenfd, (sockaddr*) &serverAddr ,sizeof(serverAddr) );

	listen(sServListenfd,100);

	printf("Listening @port# %d \n",atoi(argv[2]));

	__tids = new pthread_t*[THREADPOOL];

	for(int i = 0; i < THREADPOOL ; i++)
	{
		__tids[i] = new pthread_t();
		pthread_create(__tids[i],NULL,run,(void*)&i);
		printf("Created thread %d \n",i);
	}

	for(int i = 0; i < THREADPOOL ; i++)
	{
		pthread_join(*(__tids[i]), &res);
	}

}


void* run(void* arg)
{
	int connfd;
	socklen_t clientLength;
	struct sockaddr_in clientAddr;
	for(;;)
	{
		clientLength = sizeof(clientAddr);
		pthread_mutex_lock(&mlock);
		printf("Waiting for client connection %d \n",*(int*)(arg) );
		connfd = accept(sServListenfd,(sockaddr*)&clientAddr, &clientLength);
		pthread_mutex_unlock(&mlock);
		handleClientConnect(connfd);
	}
	return arg;
}

void handleClientConnect(int connfd)
{
	char mesg_buffer[MSG_SIZE];
	ssize_t sizeRead;
	string welcome("\nWelcome to chat server \n");
	welcome.append("1. JOIN <name> (enter)\n");
	welcome.append("2. LIST (enter)\n");
	welcome.append("3. UMSG <name> (enter) <message> (enter)\n");
	welcome.append("4. BMSG <message> (enter)\n" );
	welcome.append("5. LEAV (enter)\n");
	welcome.append("*(enter) indicates to press enter\n");
	write(connfd,welcome.c_str(), welcome.length() );
	ClientUser* currentUser = NULL;
	while(true)
	{
		do{
			sizeRead = read(connfd,mesg_buffer,MSG_SIZE);
			}while(sizeRead <= 0);

			if(strcmp(mesg_buffer,MSG_JOIN) == 0 )
			{
				handleJoin(connfd, &currentUser);
				continue;
			}
			else if(strcmp(mesg_buffer,MSG_LIST) == 0)
			{
				if(currentUser != NULL)
				{
					handleList(connfd,  &currentUser);
					continue;
				}
				string needJoin("Use JOIN <name>");
				write(connfd,needJoin.c_str(), needJoin.length());
				continue;
			}
			else if(strcmp(mesg_buffer,MSG_UMSG) == 0)
			{
				if(currentUser != NULL)
				{
					handleMsg(connfd ,  &currentUser);
					continue;
				}
				string needJoin("Use JOIN <name>");
				write(connfd,needJoin.c_str(), needJoin.length());
				continue;

			}
			else if(strcmp(mesg_buffer,MSG_BMSG) == 0)
			{
				if(currentUser != NULL)
				{
					handleBmsg(connfd,  &currentUser);
					continue;
				}
				string needJoin("Use JOIN <name>");
				write(connfd,needJoin.c_str(), needJoin.length());
				continue;
			}
			else if(strcmp(mesg_buffer,MSG_LEAV) == 0)
			{
				if(currentUser != NULL)
				{
					handleLeav(connfd,  &currentUser);
					break;
				}
				string needJoin("Use JOIN <name>");
				write(connfd,needJoin.c_str(), needJoin.length());
				continue;
			}
	}


}

int handleJoin(int connfd, ClientUser** currentUser)
{
	char name[256];
	size_t retType = 0;
    read(connfd, name, 256) ;

	std::string nameString(name);
	retType = nameString.find(EOL,0);
	if(retType == string::npos)
	{
		return ERR_NAME;
	}
	else
	{
		memset(name,0,256);
		nameString.copy(name, retType, 0);
		*currentUser = new ClientUser(connfd,name);
		pthread_mutex_lock(&maplock);
			user_map.insert(U_MAP_TYPE(name,*currentUser));
		pthread_mutex_unlock(&maplock);
		printf("Added user %s",name);
	}
	return ERR_SUCCESS;
}

int handleList(int connfd, ClientUser** currentUser)
{
	U_MAP_ITR itr;
	pthread_mutex_lock(&maplock);
	for(itr = user_map.begin(); itr != user_map.end();  itr ++ )
	{
		write(connfd,itr->first.c_str(), itr->first.length());
		string newline("\n");
		write(connfd, newline.c_str(), newline.length());
	}
	pthread_mutex_unlock(&maplock);
	return ERR_SUCCESS;
}

int handleMsg(int connfd, ClientUser** currentUser)
{
	char name[256];
	char mesg[3000];
	size_t retType = 0;
	size_t retType2 = 0;
	read(connfd, name, 256) ;

	std::string name_buffer(name);
	retType = name_buffer.find(EOL,0);
	if(retType == string::npos)
	{
		return ERR_NAME;
	}
	else
	{
		memset(name,0,256);
		name_buffer.copy(name, retType, 0);
		string nameString(name);
		U_MAP_ITR itr = user_map.find(name);
		if(itr != user_map.end())
		{
			ClientUser* sendUser = itr->second;
			read(connfd, mesg, 3000) ;
			std::string mesg_buffer(mesg);
			retType2 = mesg_buffer.find(EOL,0);
			if(retType2 != string::npos)
			{
				memset(mesg,0,3000);
				mesg_buffer.copy(mesg, retType2 ,  0);
				sendUser->sendMessage(mesg, (*currentUser)->getName());
				return ERR_SUCCESS;
			}
		}
		else
		{
			return (ERR_NO_USER);
		}
	}
	return ERR_UNKNOWN;
}

int handleBmsg(int connfd, ClientUser** currentUser)
{
	U_MAP_ITR itr;
	size_t retType = 0;
	char mesg_buffer[3000];

	read(connfd, mesg_buffer, 3000) ;

	std::string mesgString(mesg_buffer);
	retType = mesgString.find(EOL,0);
	if(retType == string::npos)
	{
		return ERR_NAME;
	}
	else
	{
		memset(mesg_buffer,0,3000);
		mesgString.copy(mesg_buffer, retType, 0);
		pthread_mutex_lock(&maplock);
			for(itr = user_map.begin(); itr != user_map.end();  itr ++ )
			{
				ClientUser* listedUser = itr->second;
				listedUser->sendMessage(mesg_buffer, (*currentUser)->getName());
			}
		pthread_mutex_unlock(&maplock);
	}
}

int handleLeav(int connfd, ClientUser** currentUser)
{
	U_MAP_ITR itr;
	pthread_mutex_lock(&maplock);
		for(itr = user_map.begin(); itr != user_map.end();  itr ++ )
		{
			ClientUser* listedUser = itr->second;
			if(listedUser->getConnectionId() == connfd)
			{
				delete listedUser;
				user_map.erase(itr);
			}
		}
	pthread_mutex_unlock(&maplock);
	*currentUser = NULL;
	close(connfd);
	return ERR_SUCCESS;
}
