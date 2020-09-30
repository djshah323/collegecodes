/* This file defines methods exposed by server
* It exposes following methods :
*  
* int 		AddWord(string word, string meaning)
* string 	FindWord(string word)
* int 		DeleteWord(string word);
*/

typedef string word<255>;

struct WORD
{
	word name;
	word meaning;
};

program DICTIONARYPROG {
    version DICTIONARYVERS{
        int 		ADDWORD(WORD) 		= 1;
	string 		FINDWORD(string) 		= 2;
	int 		DELETEWORD(string)		= 3;
    } = 1;
} = 99;
