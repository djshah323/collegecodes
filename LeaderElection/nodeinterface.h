/*
 * nodeinterface.h
 *
 *  Created on: Mar 25, 2015
 *      Author: root
 */

#ifndef NODEINTERFACE_H_
#define NODEINTERFACE_H_

typedef enum node_state
{
		INITIAL = 0,
		NORMAL = 1,
		LEADER_INIT =2 ,
		LEADER_SELECT = 3,
		LEADER =4
} STATE;

#define ALARM_TIMEOUT  60
#define END_OF_SEQ 0

#ifdef __cplusplus
extern "C" {
#endif

extern void* node_start(void*);
extern STATE get_state();
extern void set_state(STATE state);
extern void setleadervalue(int value);
extern int getleadervalue();
extern void send_client(int* argp);
extern int get_number_of_nodes();
extern void annouce_leader();

#ifdef __cplusplus
}
#endif

#endif /* NODEINTERFACE_H_ */
