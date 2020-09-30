/*
 * shell.h
 *
 *  Created on: Mar 21, 2015
 *      Author: root
 */

#ifndef SHELL_H_
#define SHELL_H_


#define MAX_SIZE 256

typedef struct job
{
	int job_no;
	pid_t pid;
	struct job* next;
} job;

int parseCommand(char* command, char* cmd, char** arg);
static void sigchildhandler(int sig);
static void siginthandler(int sig);
static void sigstphandler(int sig);
void shell_init();

#endif /* SHELL_H_ */
