/*
 * shmserver.h
 *
 *  Created on: Mar 21, 2015
 *      Author: root
 */

#ifndef SHAREDMEMORY_CLIENT_SHMSERVER_H_
#define SHAREDMEMORY_CLIENT_SHMSERVER_H_

key_t key; /* key to be passed to shmget() */ 
int shmflg; /* shmflg to be passed to shmget() */ 
int shmid; /* return value from shmget() */ 
int size; /* size to be passed to shmget() */ 



#endif /* SHAREDMEMORY_CLIENT_SHMSERVER_H_ */
