/*
 * ClientUser.cpp
 *
 *  Created on: Dec 24, 2014
 *      Author: root
 */

#include "ClientUser.h"
#include <string.h>


ClientUser::ClientUser(int connfd, char* name)
{
	this->connfd = connfd;
	strcpy((this->name),(const char*) name);
}

ClientUser::~ClientUser() {

}

int
ClientUser::sendMessage(char* message, char* sender)
{
	int retErr = ERR_SUCCESS;
	string messageStr(message);
	string incoming("Incoming message from ");
	incoming.append(sender);
	incoming.append("\n");
	write(connfd, incoming.c_str(), incoming.length());
	write(connfd,messageStr.c_str(), messageStr.length() );
	return retErr;
}

int
ClientUser::getConnectionId()
{
	return connfd;
}

char*
ClientUser::getName()
{
	return name;
}
