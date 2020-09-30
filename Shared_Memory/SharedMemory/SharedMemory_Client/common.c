/*
 * common.c
 *
 *  Created on: Mar 21, 2015
 *      Author: root
 */



#include <sys/sem.h>

#include "common.h"

int shmid; /* return value from shmget() */
int sem_rd_id;
int sem_wr_id;
const key_t key_shm = 121;
const key_t key_sem_wr = 122;
const key_t key_sem_rd = 123;
const char* READ_SEM = "read_sem";
const char* READ_WRITE_SEM = "read_write_sem";

void* shared_init()
{
	void* shm  = NULL;
	if ((shmid = shmget(key_shm, MAX_SIZE,  0666)) < 0)
	{
		perror("error fetching shared memory");
		exit(1);
	}
	if ((shm = shmat(shmid, NULL, 0)) == (char *) -1)
 	{
		perror("error attaching to shared memory");
		exit(1);
 	}
	return shm;
}

int get_shmid()
{
	return shmid;
}

int  get_semrd()
{
	return sem_rd_id;
}

int get_semwr()
{
	return sem_wr_id;
}


int sem_read_init()
{
	sem_rd_id = semget(key_sem_rd,	1,	0666);
}

int sem_write_init()
{
	sem_wr_id = semget(key_sem_wr,	1,	0666);

}

void sem_lock(int  semid)
{
	struct sembuf lock;
	lock.sem_num  = 0;
	lock.sem_op = -1;
	lock.sem_flg  = 0;
	semop(semid,&lock,1);
}

void sem_unlock(int semid)
{
	struct sembuf unlock;
	unlock.sem_num  = 0;
	unlock.sem_op = 1;
	unlock.sem_flg  = 0;
	semop(semid,&unlock,1);
}
