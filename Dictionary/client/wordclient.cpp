/*
 * wordclient.cpp
 *
 *  Created on: Nov 28, 2014
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "dictionary.h"

using namespace std;


#define MAX_CHAR 256;

int main( int argc, char* argv[] )
{
   char *host;
   CLIENT *cl;
   WORD wordMeaning;
   int *result;
   int response;

   if(argc < 2)
   {
     printf(
      "usage: %s server_host \n",
      argv[0]);
      exit(1);
   }

   host = argv[1];
   cl = clnt_create(argv[1], DICTIONARYPROG, DICTIONARYVERS, "udp");
   if (cl == NULL) 
   {
		clnt_pcreateerror(argv[1]);
		exit(1);
   }
   cout << "Connected to dictionary server Following operations available:\n";
   cout << "Enter ... \n";
   cout << "1.	Add new word to dictionary\n";
   cout << "2.	Lookup a word \n";
   cout << "3.	Delete word \n";
   cout << "99.	Exit \n";

   cin >> response;

   while(response != 99 && response > 0 && response < 4)
   {
	   switch(response)
	   {
		   case(1) :
					{
			   	   	   	   cout << "\nEnter new word \n";
			   	   	   	   string word = "";
			   	   	   	   string meaning =  "";

			   	   	   	   cin >> word;

			   	   	   	  // char* wordPtr[1] ;
			   	   	   	  // wordPtr[0] = (char*) word.c_str();
			   	   	   	   wordMeaning.name = (char*) word.c_str();

			   	   	   	   cout << "\nEnter the meaning of word, use _ as space \n";
			   	   	   	  cin >> meaning;
			   	   	   	   wordMeaning.meaning = (char*) meaning.c_str();

						   result = addword_1(&wordMeaning, cl);
							  if (result != 0) {
								clnt_perror(cl, "Error adding the word.");
								cout << "Error adding the word.";
							  }
							  else
							  {
								  cout << "Added.";
							  }
							break;
					}
		   case(2) :
					{
			   	   	   	   cout << "\nEnter word\n";
			   	   	   	   string word = "";
			   	   	   	   cin >> word;
			   	   	   	   char** meaning = NULL;
			   	   	   	   char* find[1];
			   	   	   	   find[0] = (char*)word.c_str();
			   	   	   	   meaning = findword_1(find, cl);
							  if (meaning == NULL) {
								cout << "Cannot find word.";
							  }
						  cout << meaning[0];
						  cout << "\n";
						  break;
					}
		   case(3) :
					{
			   	   	   	   cout << "\nEnter word to delete\n";
			  			   string word = "";
			  			   cin >> word;
			  			 char* find[1];
			  			 find[0] = (char*)word.c_str();
			  			 result = deleteword_1(find,cl);
			  			 if (result != 0) {
							clnt_perror(cl, "Error deleting the word.");
							cout << "Error deleting the word.";
						  }
						  else
						  {
							  cout << "Deleted.";
						  }
						   break;
					}
	   }
	  cout << "\nEnter ... \n";
	  cout << "1.	Add new word to dictionary\n";
	  cout << "2.	Lookup a word \n";
	  cout << "3.	Delete word \n";
	  cout << "99.	Exit \n";



	  cin >> response;
   }

   cout << "Exitting.";
   exit(0);
}
