/*
 * wordserver.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: root
 */

#include <rpc/rpc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <map>
#include "dictionary.h"
#include "wordserver.h"

WORD_MAP word_map;
using namespace std;

int* addword_1(WORD * newWord, CLIENT *)
{
	string word(newWord->name);
	string meaning(newWord->meaning);

	if(word_map.find(word)  == word_map.end())
	{
		cout << "\nInserting new word \n";
		cout << word.c_str();
		cout << "\n";
		cout << meaning.c_str();

		word_map.insert(WORD_MAP_TYPE(word,meaning));
	}

	return 0;
}

int* addword_1_svc(WORD * newWord, struct svc_req *)
{
	CLIENT* client;
	return (addword_1(newWord, client));
}

char** findword_1(char** word, CLIENT *)
{
	char** result = NULL;
	string findWord(word[0]);
	cout << "finding word " << findWord.c_str();
	if(word_map.find(findWord) != word_map.end())
	{
		string meaning(word_map.find(findWord)->second);
		result = new char*[1];
		result[0] = (char*) meaning.c_str();
	}
	return (char**) result;
}

char** findword_1_svc(char** word, struct svc_req *)
{
	CLIENT* client;
	return (findword_1(word,client));
}

int* deleteword_1(char** word, CLIENT *)
{
	string findWord(word[0]);
	cout << "finding word " << findWord.c_str();
	if(word_map.find(findWord) != word_map.end())
	{
		word_map.erase(word_map.find(findWord));
		cout << "Deleted  word: " << findWord;
	}
	else
	{
		cout << "Cannot find word: " << findWord;
	}
	return 0;
}

int* deleteword_1_svc(char ** word, struct svc_req *)
{
	CLIENT* client;
	return (deleteword_1(word, client));

}

