/*
 * ring_leader.c
 *
 *  Created on: Mar 23, 2015
 *      Author: root
 */

#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#include <unistd.h>


#include "ring.h"
#include "nodeinterface.h"

int  isLeader = 0;
int  isLeaderMessageSent = 0;
int _leaderCost;


int receiptcount(int* argp)
{
	int count = 0;
	while(argp[count] != END_OF_SEQ )
	{
		printf("%d\n",argp[count]);
		count ++;
	}
	return count +1;
}

int getmax_value(int* argp)
{
	int count = 0;
	int max = argp[count];
	while(argp[count] != END_OF_SEQ)
	{
		if(argp[count] > max)
			max = argp[count];
		count++;
	}
	return max;
}

void * send_1_svc(int *argp, struct svc_req *rqstp)
{
	printf("Received integer sequence \n");
	int result = receiptcount(argp);
	switch(get_state())
	{
		case INITIAL:
		case NORMAL:
				printf("INITIAL or NORMAL\n");
				argp[result] = rand()  %100;
				argp[result + 1] = END_OF_SEQ;
				send_client(argp);
				setleadervalue(argp[result]);
				set_state(LEADER_SELECT);
				break;
		case LEADER_INIT:
			//search if its own leadervalue is the highest ?
			printf("INIT\n");
				if(result == get_number_of_nodes()
					&& getleadervalue() == getmax_value(argp))
				{
					//yup we have a leader !!
					set_state(LEADER);
					annouce_leader();
				}
				else
				{
					//step down from leader initiator
					// add a leader value for the next node
					argp[result] = rand()  %100;
					argp[result + 1] = END_OF_SEQ;
					send_client(argp);
					setleadervalue(argp[result]);
					set_state(LEADER_SELECT);
				}
				break;
		case LEADER_SELECT:
			if(getleadervalue() == getmax_value(argp))
			{
				//yup we have a leader !!
				set_state(LEADER);
				annouce_leader();

			}
			else
			{
				//forward and drop to normal
				send_client(argp);
				setleadervalue(-1);
				set_state(NORMAL);
			}
			break;
		case LEADER:
			break;
	}

	return (void*) NULL;
}

void * alivemessage_1_svc(void *argp, struct svc_req *rqstp)
{
	alarm(ALARM_TIMEOUT);
	set_state(NORMAL);
	setleadervalue(-1);
	return (void*) NULL;
}

