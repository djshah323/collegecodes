/*
 * ClientUser.h
 *
 *  Created on: Dec 24, 2014
 *      Author: root
 */

#ifndef CLIENTUSER_H_
#define CLIENTUSER_H_

#include <map>
#include <stdlib.h>
#include <string>
#include "err.h"


#define NAME_MAX = 256;

using  namespace std;

class ClientUser;

typedef std::map<string,ClientUser*> U_MAP;
typedef U_MAP::iterator U_MAP_ITR;
typedef U_MAP::const_iterator U_MAP_CONST_ITR;
typedef U_MAP::value_type U_MAP_TYPE;

class ClientUser
{
	private:
		int connfd;
		char name[256];
	public:
		ClientUser(int connfd, char* name);
		virtual ~ClientUser();
		int sendMessage(char* message, char* sender);
		int getConnectionId();
		char* getName();
};

#endif /* CLIENTUSER_H_ */
