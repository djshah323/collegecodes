/*
 * Node.h
 *
 *  Created on: Mar 24, 2015
 *      Author: root
 */

#ifndef NODE_HPP_
#define NODE_HPP_

#include <stdlib.h>
#include <vector>
#include <pthread.h>
#include "ring.h"


class Node
{
	private:
		char* nodeip;
		char* clientip;
		std::vector<char*> all_ips;
		CLIENT* next_client_node;
		std::vector<CLIENT*> all_client_node;

	public:
		Node();
		virtual ~Node();
		void init();
		char* getLocalIP();
		char* getClientIP();
		char* get_Local();
		char* get_Client();
		static void alarmhandler(int sig);
		void send_alive();
		CLIENT* get_next_node();
		int get_number_of_nodes();
};

#endif /* NODE_HPP_ */

