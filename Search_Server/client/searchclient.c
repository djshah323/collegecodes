/*
 * searchclient.c
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>

#define MAX_CHAR 256;

int sockfd;


void
send_query(char* query_string)
{
	write(sockfd,query_string,strlen(query_string));
	printf("Server replied ... \n");
	char recvMessage[4096];
	read(sockfd,recvMessage,4096);
	write(STDOUT_FILENO,recvMessage,4096);

}

void
command_loop(char* command, int max_size)
{
 char c = '\0';
 int N = 0;

 while(1)
 {
	c = getchar();
	if (c == '\n' || N == max_size)
	{
		break;
	}
	else
	{
		if(c == 32)
		{
			command[N] = ' ';
		}
		else
		{
			command[N] = c;
		}
	}
	++N;
 }
 command[N] =  '\0';
}

int main( int argc, char* argv[] )
{
   char *host;
   int result = 0;
   int response;

   if(argc < 2)
   {
     printf(
      "usage: %s server_ip:port \n",
      argv[0]);
      exit(1);
   }

   host = argv[1];
   char* server_ip = strtok(host,":");
   char* server_port = strtok(NULL,":");
   if(server_ip == NULL || strlen(server_ip) == 0 ||
		   server_port == NULL || strlen(server_port) == 0)
   {
	   printf("usage: %s server_ip:port \n",
	         argv[0]);
	         exit(1);
   }

   	struct sockaddr_in servaddr;
   	sockfd = socket(AF_INET, SOCK_STREAM, 0);
   	bzero(&servaddr,sizeof(servaddr));
   	servaddr.sin_family = AF_INET;
   	servaddr.sin_port = htons(atoi(server_port));
   	inet_pton(AF_INET, host, &servaddr.sin_addr);

   	result = connect(sockfd, (struct sockaddr*) &servaddr, sizeof(servaddr));

   if(result)
   {
	   printf("Errorr connecting %d %s \n", result, strerror(errno));
	   exit(1);
   }

   printf("Connected to search server Following operations available:\n");
   printf("Enter ... \n");
   printf("1.	search\n");
   printf("99.	Exit \n");

   char res[2];
   read(STDIN_FILENO, res,2);
   res[1] = '\0';
   response = atoi(res);
   while(response != 99 && response > 0 && response < 2)
   {
	   switch(response)
	   {
	   	   case(1):
			{
	   		  size_t cmdLen = 0;
			  char* query_string = NULL;
			  printf("query string: \n");
			  char buf[256];
			  command_loop(buf, 256);
			  cmdLen  = cmdLen + strlen(buf);
			  cmdLen  += 1;  //for  $
			  printf("In previous results?\n");
			  char yesorno = '\0';
			  command_loop(&yesorno, 1);
			  if(!(yesorno == 'n' ||
				   yesorno == 'y' ||
				   yesorno == 'Y' ||
				   yesorno == 'N'))
			  {
				  	  continue;
			  }
			  cmdLen += 1; //for Y or N

			  if(yesorno == 'n' || yesorno == 'N')
			  {
				  cmdLen += 1; // for $
				  printf("Enter file name:\n");
				  char filename[256];
				  command_loop(filename, 256);
				  cmdLen += strlen(filename);

				  query_string = (char*) malloc(cmdLen + 1);
				  strncpy(query_string,buf,strlen(buf));
				  query_string[strlen(buf)] = '$';
				  query_string[strlen(buf) + 1] = 'N';
				  query_string[strlen(buf) + 2] = '$';
				  query_string[strlen(buf) + 3] = '\0';
				  strcat(query_string,filename);
				  query_string[cmdLen]  = '\0';
			  }
			  else
			  {
				  query_string = (char*) malloc(cmdLen + 1);
				  strncpy(query_string,buf,strlen(buf));
				  query_string[strlen(buf)] = '$';
				  query_string[strlen(buf) +  1] = 'Y';
				  query_string[strlen(buf) + 2] = '\0';
			  }
			  send_query(query_string);

			  break;
			}
	   }

	   printf("Connected to search server Following operations available:\n");
	   printf("Enter ... \n");
	   printf("1.	search\n");
	   printf("99.	Exit \n");

	   char res[2];
	   read(STDIN_FILENO, res,2);
	   res[1] = '\0';
	   response = atoi(res);
   }

   printf("Exiting.");
   exit(0);
}
