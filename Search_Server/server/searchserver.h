/*
 * searchserver.h
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#ifndef SEARCHSERVER_H_
#define SEARCHSERVER_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define  MAX_LEN 256

#define READ 0
#define WRITE 1

int sServListenfd ;
struct sockaddr_in serverAddr;

void perform_search(int connfd);

#endif /* SEARCHSERVER_H_ */
