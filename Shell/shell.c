/*
 * shell.c
 *
 *  Created on: Mar 21, 2015
 *      Author: root
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "shell.h"
#include "job.h"

int status;
pid_t childpid;
pid_t shellpid;
volatile int isBackGround;
job* joblist = NULL;

int createNewJob(pid_t pid)
{
	int createdNumber = 0;
	if(joblist == NULL)
	{
		job* newJob = (job*)	malloc(sizeof(job));
		newJob->job_no = 1;
		newJob->pid = pid;
		newJob->next  = NULL;
		joblist = newJob;
		createdNumber = newJob->job_no;
	}
	else
	{
		job* temp = joblist;
		while(temp->next != NULL)
		{
			temp = temp->next;
		}
		job* newJob = (job*)	malloc(sizeof(job));
		newJob->job_no = temp->job_no  + 1;
		newJob->pid = pid;
		newJob->next  = NULL;
		temp->next= newJob;
		createdNumber = newJob->job_no;
	}
	return createdNumber;
}
void removejob(int jid)
{
	job* retJob = fetchjob(jid);
	job* prev = fetchjobbefore(jid);
	if(retJob != NULL && prev != NULL)
	{
		prev->next = retJob->next;
		free(retJob);
	}
}

job* fetchjobbefore(int jid)
{
	if(joblist != NULL)
	{
		job* temp = joblist;
		job* prev = temp;
		while(temp->next != NULL && temp->job_no != jid)
		{
			prev = temp;
			temp = temp->next;
		}
		if(temp->job_no == jid)
		{
			return prev;
		}
	}
		return NULL;
}

job* fetchjob(int jid)
{
	if(joblist != NULL)
	{
		job* temp = joblist;
		job* prev = temp;
		while(temp->next != NULL && temp->job_no != jid)
		{
			prev = temp;
			temp = temp->next;
		}
		if(temp->job_no == jid)
		{
			return temp;
		}
	}
	return NULL;
}

int jobCount()
{
	int count = 0;
	if(joblist != NULL)
	{
		job* temp = joblist;
		while(temp->next != NULL)
		{
			count++;
			temp = temp->next;
		}
	}
	return count;
}

pid_t fetchprocess(int jid)
{
	if(joblist != NULL)
	{
		job* temp = joblist;
		while(temp->next != NULL && temp->job_no != jid)
		{
			temp = temp->next;
		}
		if(temp->job_no == jid)
		{
			return temp->pid;
		}
	}
	return 0;
}


void jobWalk()
{
	if(joblist != NULL)
	{
		printf("jobid %d pid %d\n",joblist->job_no,joblist->pid);
		job* temp = joblist;
		while(temp->next != NULL)
		{
			temp = temp->next;
			printf("jobid %d pid %d\n",temp->job_no,temp->pid);
		}
	}

}
void shell_loop(char* command)
{
	 char c = '\0';
	 int N = 0;

	 while(1)
	 {
		c = getchar();
		if (c == '\n')
		{
			break;
		}
		else
		{
			if (N == MAX_SIZE)
			{
				break;
			}
			if(c == '&')
			{
				isBackGround = 1;
			}
			else if(c == 32)
			{
				command[N] = ' ';
			}
			else
			{
				command[N] = c;
			}
		}
		++N;
	  }

}

void wait_at_background()
{
	while(1)
	{
		sleep(1);
		if(isBackGround == 0)
		{
			int ret = waitpid(childpid,&status,WNOHANG);
			if(ret != 0)
			{
				printf("pid %d status %d \n", childpid,status);
				break;
			}

		}
		else
		{
			int ret = createNewJob(childpid);
			printf("jobid %d pid %d \n", ret,childpid);
			break;
		}
	}
}

int main(int argc, char* argv[])
{
	 shell_init();
	 while(1)
	 {
		 printf("\ndjs>");
		 char	 command[MAX_SIZE];
		 char 	 commd[MAX_SIZE];
		 char*	 arg[10];
		 isBackGround = 0;

		 shell_loop(command);

		 if(strlen(command) > 1)
		 {
			 parseCommand(command, commd, arg);
		 }
		 else
		 {
			 printf("Invalid command.\n");
			 continue;
		 }

		 if(strcmp(commd,"jobs") == 0)
		 {
			// printf("Total number of jobs: %d\n", jobCount());
			 jobWalk();
		 }
		 else if(strcmp(commd,"bg") == 0)
		 {
			pid_t targetProcess = fetchprocess(atoi(arg[0]));
			kill(targetProcess,SIGCONT);
		 }
		 else if(strcmp(commd,"fg") == 0)
		 {
			 pid_t targetProcess = fetchprocess(atoi(arg[0]));
			 removejob(atoi(arg[0]));
			 kill(targetProcess,SIGCONT);
			 childpid = targetProcess;
			 wait_at_background();
		 }
		 else if(strcmp(commd,"kill") == 0)
		 {
			 pid_t targetProcess = fetchprocess(atoi(arg[0]));
			 kill(targetProcess,SIGSTOP);
		 }
		 else
		 {
			if( ( childpid = fork() )!= 0)
			{
				wait_at_background();

			}
			else
			{
				if(isBackGround == 1)
				{
					   /* Redirect standard files to /dev/null */
					freopen( "/dev/null", "r", stdin);
					freopen( "/dev/null", "w", stdout);
					freopen( "/dev/null", "w", stderr);
				}
				Execute(commd,arg);
			}

		 }
		memset(command,0,MAX_SIZE);
		memset(commd,0,MAX_SIZE);
		isBackGround  = 0;
	 }

}

int parseCommand(char* command, char* cmd, char** arg)
{
	int ret = 0;
	char*  token;

	memset(cmd,0,MAX_SIZE);

	token =  strtok(command, " -");
	if(token != NULL)
	{
		strcpy(cmd,token);
		int c = 0;
		while((token = strtok(NULL, " -"))!= NULL)
		{
			if(c > 9)
			{
				break;
			}
			char* argument = token;
			arg[c] = (char*) malloc(sizeof(strlen(argument) + 1));
			strcpy(arg[c],argument);
			arg[c][strlen(argument)] = '\0';
			c++;
		}
		arg[c] = NULL;
	}
	else
	{
		strcpy(cmd,command);
		return ret;
	}

	return ret;
}

int Execute(char* command, char** args)
{
	 execvp(command, args);
}

void shell_init()
{
	shellpid = getpid();

	if(signal(SIGCHLD,sigchildhandler) == SIG_ERR)
	{
		exit(1);
	}

	if(signal(SIGINT,siginthandler) == SIG_ERR)
	{
		exit(1);
	}

	if(signal(SIGTSTP,sigstphandler) == SIG_ERR)
	{
		exit(1);
	}

	printf("jobs\n");
	printf("bg -jobnum\n");
	printf("fg -jobnum\n");
	printf("kill -jobnum\n");
}

static void sigchildhandler(int sig)
{
	//waitpid(-1,&status,0);
}

static void siginthandler(int sig)
{
	kill(childpid, sig);
}

static void sigstphandler(int sig)
{
	if(  getpid() == shellpid )
	{
		isBackGround = 1;
		int ret = createNewJob(childpid);
		printf("jobid %d pid %d \n", ret,childpid);
		kill(childpid,sig);
	}

}
