/*
 * shmclient.c
 *
 *  Created on: March 15, 2015
 *      Author: root
 */



#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>
#include "shmclient.h"
#include "common.h"


int main(int argc, char*  argv[])
{
	int semWrite = -1;
	int semRead = -1;
	MESG** message = NULL;
	int _number_of_messages;
	void* __sharedAddr = NULL;

	if(argc !=  2)
	{
		printf("Usage %s numberOfMessages",argv[0]);

		exit(1);
	}
	else
	{
		_number_of_messages = atoi(argv[1]);
	}

	semWrite = sem_write_init();
	if(semWrite == -1)
	{
		printf("Could not write. Semaphore Undefined.");
		exit(1);
	}
	semRead = sem_read_init();
	if(semRead == -1)
	{
		printf("Could not read. Semaphore Undefined.");
		exit(1);
	}


	__sharedAddr = shared_init();

	if(__sharedAddr == NULL)
	{
		printf("Error acquiring shared memory");
		exit(1);
	}
	void* __tempAddr = __sharedAddr;


	printf("The client is going to construct %d messages \n",
			_number_of_messages);

	sem_lock(semWrite);

	int indexM = 0;
	for( ; indexM < _number_of_messages ; indexM ++)
	{
		message =(MESG**) malloc(sizeof(MESG*));
		*message = (MESG*)__tempAddr;

		(*message)->type = 1;
		(*message)->slno = indexM;
		(*message)->pid = getpid();
		(*message)->a = rand() % 100;
		(*message)->b = rand() % 100;
		(*message)->total = 0;

		printf("Client \n");
		printf("pid %d, Mesg %d, a= %d, b= %d, a+b= %d, shmid = %d \n",
				(*message)->pid,
				indexM,
				(*message)->a ,
				(*message)->b,
				(*message)->total,
				get_shmid());

		__tempAddr = __tempAddr + sizeof(MESG);
		message++;
	}
	//Write a empty message to  indicate close of messages.
	message =(MESG**) malloc(sizeof(MESG*));
	*message = (MESG*)__tempAddr;

	(*message)->type = 0;
	(*message)->slno = -1;
	(*message)->pid = 0;
	(*message)->a =  0;
	(*message)->b = 0;
	(*message)->total = -1;

	sem_unlock(semRead);

	printf("*** Messages Submitted ***\n");
	sleep(5);
	__tempAddr = __sharedAddr;
	for(indexM =0 ; indexM < _number_of_messages ; indexM ++)
	{
		sem_lock(semRead);
		MESG*  readMessage = (MESG*) __tempAddr;
		printf("Client \n");
				printf("Received type %d, Mesg %d, a= %d, b= %d, a+b = %d \n",
						(readMessage)->pid,
						indexM,
						(readMessage)->a ,
						(readMessage)->b,
						(readMessage)->total);

		sem_unlock(semRead);
		__tempAddr = __tempAddr + sizeof(MESG);
		sleep(1);
	}
	sem_unlock(semWrite);
}


