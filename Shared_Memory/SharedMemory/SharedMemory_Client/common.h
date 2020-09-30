/*
 * common.h
 *
 *  Created on: Mar 21, 2015
 *      Author: root
 */

#ifndef SHAREDMEMORY_CLIENT_COMMON_H_
#define SHAREDMEMORY_CLIENT_COMMON_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>

#define MAX_SIZE 1000000

typedef struct message
{
	int type;
	int pid; //client's pid
	int slno; //incremented for every message
	int a; //any number
	int b; //any number
	int total;//total of a and b, processed by server
} MESG;


void* shared_init();
int sem_read_init();
int sem_write_init();
int get_shmid();
int get_semrd();
int get_semwr();
void sem_lock(int semid);
void sem_unlock(int semid);

#endif /* SHAREDMEMORY_CLIENT_COMMON_H_ */
