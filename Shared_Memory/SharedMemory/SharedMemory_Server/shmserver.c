/*
 * shmserver.c
 *
 *  Created on: March 29, 2015
 *      Author: root
 */

#include <stdio.h>
#include "common.h"

int main(int argc, char*  argv[])
{
	int semWrite = -1;
	int semRead = -1;
	MESG** message = NULL;
	int _number_of_messages;
	void* __sharedAddr = NULL;

	__sharedAddr = shared_init();
	void* __tempAddr = __sharedAddr;

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

	int indexM = 0;
	while(1)
	{
		sem_lock(semRead);
		message =(MESG**) malloc(sizeof(MESG*));
		*message = (MESG*)__tempAddr;
		if(		(*message)->type != 1 )
		{

			//wee have reached end of messages.
			printf("End of messages. Waiting for new clients\n");
			sem_unlock(semRead);
			__tempAddr = __sharedAddr;
			sleep(1);
			continue;
		}
		(*message)->type  = (*message)->pid;
		(*message)->total =  (*message)->a + (*message)->b ;

		printf("Server %d\n",getpid());
		printf("Client pid %d, Mesg %d, a= %d, b= %d, sum= %d, shmid = %d \n",
				(*message)->pid,
				(*message)->slno,
				(*message)->a ,
				(*message)->b,
				(*message)->total,
				get_shmid());

		indexM ++;
		__tempAddr = __tempAddr + sizeof(MESG);
		message++;
		sem_unlock(semRead);
		sleep(1);

	}
}


