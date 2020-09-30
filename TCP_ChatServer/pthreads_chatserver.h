/*
 * pthreads_chatserver.h
 *
 *  Created on: Dec 24, 2014
 *      Author: root
 */

#ifndef PTHREADS_CHATSERVER_H_
#define PTHREADS_CHATSERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include "ClientUser.h"
#include "err.h"

void* run(void* );
void handleClientConnect(int socketfd);
int handleJoin(int socketfd, ClientUser** currentUser);
int handleList(int connfd, ClientUser** currentUser);
int handleMsg(int connfd, ClientUser** currentUser);
int handleBmsg(int connfd, ClientUser** currentUser);
int handleLeav(int connfd, ClientUser** currentUser);

int MSG_SIZE = 4;
int sServListenfd ;
struct sockaddr_in serverAddr;
pthread_t** __tids;
const char* MSG_JOIN = "JOIN";
const char* MSG_LIST = "LIST";
const char* MSG_UMSG = "UMSG";
const char* MSG_BMSG = "BMSG";
const char* MSG_LEAV = "LEAV";
static pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t maplock = PTHREAD_MUTEX_INITIALIZER;
string EOL("\r\n");




#endif /* PTHREADS_CHATSERVER_H_ */
