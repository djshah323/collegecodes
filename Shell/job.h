/*
 * job.h
 *
 *  Created on: Mar 23, 2015
 *      Author: root
 */

#ifndef JOB_H_
#define JOB_H_

#include <unistd.h>

int createNewJob(pid_t pid);
void removejob(int jid);
job* fetchjobbefore(int jid);
job* fetchjob(int jid);
int jobCount();
pid_t fetchprocess(int jid);



#endif /* JOB_H_ */
