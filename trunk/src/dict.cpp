#include "dict.h"
#include "trie.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Dictionary::Dictionary(const char* dict_file)
{
	trie = new Trie();
	loadDict(dict_file);
}

void Dictionary::reload(const char* dict_file)
{
	delete trie;
    trie = new Trie();
	loadDict(dict_file);
}

void Dictionary::loadDict(const char* dict_file)
{
	FILE * pFile;
	char string[128];
	pFile = fopen (dict_file , "r");
	if (pFile == NULL) 
	{
		perror ("Error opening file");
		exit(-1);
	}
	else 
	{	
		int fail=0;
		int success=0;
		fgets (string, 128, pFile);
		while (!feof(pFile))
		{
			/* there is a 'next-line' char at the end, remove it */
			string[strlen(string)-1] = '\0';
			if(add(string)) ++success;
			else ++fail;
			fgets (string, 128, pFile);
		}
		fclose (pFile);
		printf("\n%d words has been added into dictionary.", success);
		printf("\n%d words failed, some words are duplicated in dictionary file", fail);
	}	
}

bool Dictionary::search(Token *key)
{
	return trie->retrieve(key);
}

bool Dictionary::search(char* key)
{
	return search(&Token(key));
}

bool Dictionary::add(Token *key)
{
	return trie->insert(key);
}

bool Dictionary::add(char *key)
{
	return add(&Token(key));
}

void Dictionary::info()
{
	trie->print_state();
}

