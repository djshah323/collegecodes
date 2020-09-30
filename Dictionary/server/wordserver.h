/*
 * wordserver.h
 *
 *  Created on: Nov 28, 2014
 *      Author: root
 */


#ifndef WORDSERVER_H_
#define WORDSERVER_H_

#include <stdlib.h>
#include <string>
#include <map>
#include <iterator>


using  namespace std;

typedef std::map<string,string> WORD_MAP;
typedef WORD_MAP::iterator WORD_MAP_ITR;
typedef WORD_MAP::const_iterator WORD_MAP_CONST_ITR;
typedef WORD_MAP::value_type WORD_MAP_TYPE;



#endif /* WORDSERVER_H_ */
