/*
 * Node.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: root
 */

#include "Node.hpp"
#include "nodeinterface.h"
#include "ring.h"

#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>      
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <signal.h>

using namespace std;

Node runningNode;
node_state _state;
int leadervalue;
static pthread_mutex_t stateLock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t valueLock = PTHREAD_MUTEX_INITIALIZER;

Node::Node():nodeip(NULL),
		next_client_node(NULL)
{
}

Node::~Node()
{

}

int
getleadervalue()
{
	int retvalue;
	pthread_mutex_lock(&valueLock);
	retvalue = leadervalue;
	pthread_mutex_unlock(&valueLock);
	return retvalue;
}

void
setleadervalue(int value)
{
	pthread_mutex_lock(&valueLock);
	leadervalue = value;
	pthread_mutex_unlock(&valueLock);
}

int
get_number_of_nodes()
{
	return runningNode.get_number_of_nodes();
}

void
set_state(node_state state)
{
	pthread_mutex_lock(&stateLock);
	_state = state;
	pthread_mutex_unlock(&stateLock);

}

node_state
get_state()
{
	node_state ret_state;
	pthread_mutex_lock(&stateLock);
	ret_state = _state;
	pthread_mutex_unlock(&stateLock);
	return ret_state;
}

void
send_client(int* argp)
{
	send_1(argp,runningNode.get_next_node());
}

void
annouce_leader()
{
	runningNode.send_alive();
}

int
Node::get_number_of_nodes()
{
		return (int) all_client_node.size();
}

CLIENT*
Node::get_next_node()
{
	return next_client_node;
}

char*
Node::getLocalIP()
{
	struct ifaddrs * ifAddrStruct = NULL;
    struct ifaddrs * ifa = NULL;
    void * tmpAddrPtr = NULL;
    char* addressBuffer = NULL;
    getifaddrs(&ifAddrStruct);

    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (!ifa->ifa_addr) {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET) { // check it is IP4
            // is a valid IP4 Address
            tmpAddrPtr=&((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            addressBuffer = (char*) malloc(INET_ADDRSTRLEN + 1);
            inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
            addressBuffer[INET_ADDRSTRLEN] = '\0';
        } 
    }
    if (ifAddrStruct!=NULL)
    	freeifaddrs(ifAddrStruct);
    return addressBuffer;
}
char*
Node::get_Local()
{
	return nodeip;
}

char*
Node::get_Client()
{
	return clientip;
}

void
Node::init()
{
	string ipString;
	ifstream ipconfig;
	//read all nodes from ipconfig file.
	ipconfig.open("ipconfig", ifstream::in);
	if(ipconfig.is_open())
	{
		while(getline(ipconfig,ipString))
		{
			size_t len = ipString.length();
			char* newip = (char*) malloc(len + 1);
			strncpy(newip,ipString.c_str(), len);
			newip[len] = '\0';
			all_ips.push_back(newip);
		}
	}
	nodeip = getLocalIP();
	printf("local node is %s \n", nodeip);
	clientip = runningNode.getClientIP();
	while(1)
	{
		next_client_node = clnt_create(
							clientip,
							RING_PGM,
							RING_PGM_VERSION,
							"udp");
			if (next_client_node == NULL)
			{
				//wait for the  client to come up.
				sleep(5);
			}
			else
			{
				break;
			}
	}


	printf("other nodes are: \n");

	vector<char*>::iterator ip = all_ips.begin();
	for(; ip != all_ips.end();  ip++)
	{
		if(strcmp(nodeip,*ip) != 0)
		{
			printf("%s\n",*ip);
			CLIENT* newClient = clnt_create(
									 *ip,
									 RING_PGM,
									 RING_PGM_VERSION,
									 "udp");
			all_client_node.push_back(newClient);

		}
	}
}

char*
Node::getClientIP()
{
	vector<char*>::iterator ip = all_ips.begin();
	for(; ip != all_ips.end();  ip++)
	{
		if(strcmp(nodeip,*ip) == 0)
		{
			break;
		}
	}
	ip++;
	if(ip == all_ips.end())
	{
		ip = all_ips.begin();
	}
	return (*ip);

}

void* node_start(void* arg)
{
	set_state(INITIAL);
	srand(time(NULL));
	runningNode.init();
	signal(SIGALRM,Node::alarmhandler);
	alarm(ALARM_TIMEOUT);
	while(1)
	{
		if( get_state() == LEADER)
		{
			runningNode.send_alive();
		}
		sleep(30);
	}

}

void
Node::alarmhandler(int sig)
{
	int new_value =-1;
	printf("Awake checking for leader \n");
	switch(get_state())
	{
		case INITIAL:
		case NORMAL:
			new_value = rand() % 100;
			int sendvalue[2];
			sendvalue[0] = new_value;
			sendvalue[1] = END_OF_SEQ;
			send_1(sendvalue,runningNode.get_next_node());
			setleadervalue(sendvalue[0]);
			set_state(LEADER_INIT);
			printf("Initiating select leader call \n");
			printf("Sent %d to %s \n",sendvalue[0], runningNode.get_Client());
			break;
		case LEADER_INIT:
		case LEADER_SELECT:
			printf("Still resolving leader \n");;
			alarm(ALARM_TIMEOUT);
		case LEADER:
			printf("Iam leader \n");
			alarm(ALARM_TIMEOUT);
			break;
	}
}

void
Node::send_alive()
{
	vector<CLIENT*>::iterator ip = all_client_node.begin();
	for(; ip != all_client_node.end();  ip++)
	{
			CLIENT* cl = *ip;
			alivemessage_1(NULL,cl);
	}
}
