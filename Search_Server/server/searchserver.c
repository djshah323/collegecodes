/*
 * searchserver.c
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#include "searchserver.h"

int main( int argc, char* argv[] )
{
    int port;
	int sServListenfd ;
	struct sockaddr_in serverAddr;
	pid_t childpid;
	
   if(argc < 2)
   {
     printf(
      "usage: %s port \n",
      argv[0]);
      exit(1);
   }

   	port = atoi(argv[1]);

   	sServListenfd = socket(AF_INET,SOCK_STREAM,0);
	bzero(&serverAddr,sizeof(serverAddr));

	serverAddr.sin_family  = AF_INET;
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddr.sin_port = htons(port);

	bind(sServListenfd, (struct sockaddr*) &serverAddr ,sizeof(serverAddr));

	listen(sServListenfd,100);


	int connfd;
	socklen_t clientLength;
	struct sockaddr_in clientAddr;
	for(;;)
	{
		clientLength = sizeof(clientAddr);
		printf("Waiting for client connection \n" );
		connfd = accept(sServListenfd,(struct sockaddr*)&clientAddr, &clientLength);
		if((childpid = fork()) == 0)
		{
			close(sServListenfd);
			printf("Client connected.\n");
			perform_search(connfd);
		}

	}


}

void perform_search(int connfd)
{
	int in_pipe[2];
	int result_pipe[2];
	char buffer[4096];
	memset(buffer,'\0',4096);

	while(1)
	{
		int n = 0;
		char query[MAX_LEN];
		memset(query,'\0',MAX_LEN);

		//printf("Begining search ...\n");
		n = read(connfd,query,MAX_LEN);
		//query[n-2] = '\0';
		query[n] = '\0';
		if(strlen(query) == 0)
		{
			continue;
		}
		printf("Received search query %s\n", query);
		char* querystring = strtok(query,"$");
		char* isPrev = strtok(NULL,"$");
		if(isPrev != NULL)
		{

			pid_t childpid;
			char* arg[4];

			arg[0] = (char*) malloc(strlen("/usr/bin/grep") + 1);
			strcpy(arg[0],"/usr/bin/grep");
			arg[0][strlen("/usr/bin/grep")] = '\0';
			arg[1] = (char*) malloc(strlen(querystring) + 1);
			strcpy(arg[1],querystring);
			arg[1][strlen(querystring)] = '\0';

			if(isPrev[0] == 'N' || isPrev[0] == 'n')
			{
				pipe(in_pipe);
				pipe(result_pipe);
				// check if new file is provided
				char* filename = strtok(NULL,"$");
				arg[2] = (char*) malloc(strlen(filename) + 1);
				strcpy(arg[2],filename);
				arg[2][strlen(filename) + 1] = '\0';
				arg[3] = NULL;

				if( ( childpid = fork() )== 0)
				{
					close(in_pipe[READ]);
					close(result_pipe[READ]);
					close(result_pipe[WRITE]);
					dup2(in_pipe[WRITE],STDOUT_FILENO);
					close(in_pipe[WRITE]);
					if(execve("/usr/bin/grep", arg, NULL) < 0)
					{
						perror("execve");
					}
				}
				else
				{
					read(in_pipe[READ],buffer,4096) ;
					write(connfd,buffer,4096);
					write(in_pipe[WRITE],buffer,4096);
				}

			}
			else
			{
				arg[2] = (char*) malloc(strlen("-a") + 1);
				strcpy(arg[2],"-a");
				arg[strlen("-a") + 1] = '\0';
				arg[3] = NULL;

				if( ( childpid = fork() )== 0)
				{
					close(result_pipe[READ]);
					dup2(in_pipe[READ], STDIN_FILENO);
					close(in_pipe[READ]);
					dup2(result_pipe[WRITE],STDOUT_FILENO);
					close(result_pipe[WRITE]);
					close(in_pipe[WRITE]);
					if(execve("/usr/bin/grep", arg, NULL) < 0)
					{
						perror("execve");
					}
				}
				else
				{
					close(in_pipe[WRITE]);
					read(result_pipe[READ],buffer,4096);
					write(connfd,buffer,4096);
					write(in_pipe[WRITE],buffer,4096);
				}
			}
		}
	}

}
