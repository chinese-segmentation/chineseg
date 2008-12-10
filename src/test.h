#ifndef __TEST_H
#define __TEST_H

#include <time.h>
#include "dict.h"
#include <stdlib.h>
#include <string.h>

Dictionary* dict;
clock_t start,finish;
double totaltime;
enum { SMALL, MEDIUM, LARGE };
char* dicts[3] = {".\\small.txt",".\\medium.txt",".\\large.txt"};

void begin();
void end(const char* message);

void print_help();
void print_state();
void reset();
void load(int type);
void detect(int type);
void add(const char*);
void find(const char*);
void exit();

//******help method declare **********//
void find(bool, char *);


//********** below is definition ***************// 
void begin()
{ 
	start=clock();
}
void end(const char* message)
{
	finish=clock();
    totaltime=(double)(finish-start);
	printf("\n%s using time: %f ms.",message, totaltime);
}


void print_help()
{
	printf("Here 'small','medium','large' are dictionary of different size. 'large' contains about 120,000 entries, while 'medium' is");
	printf(" about 60.000 entries,from first half part of 'large' and 'small' is the first 5,000 entries from 'large' dictionary"); 
	printf("\nEnter a command bellow:");
	printf("\n1. help\n\tprint help");
	printf("\n2. load [small|medium|large] \n\tchoose a dictionary file of different size to load.it will do reset at first.");
	printf("\n   time usage:");
    printf("\n       load small: 5,000 entries - 1 seconds");
    printf("\n       load medium: about 60.000 entries - 1 minutes");
    printf("\n       load large: about 120,000 entries - 5 minutes.");
	printf("\n3. reset\n\tclear dictionary");
	printf("\n4. state\n\tprint trie state");
	printf("\n4. detect [small|medium|large] \n\ttest dictionary using all words from the dictionay.");
	printf("\n5. find <chinese_word>\n\tretrive a word(chinese only)");
	printf("\n6. add <chinese_word>\n\tadd a phrase(chinese only) to dictionary");
	printf("\n7. exit\n\ttexit program");
	printf("\n");
}

void print_state()
{
	dict->info();
}

void reset ()
{
	delete dict;
	dict = new Dictionary();
	printf("Reset Finish.");	
}

void load(int type)
{
	begin();
	delete dict;
	dict=new Dictionary(dicts[type]);
	end("loading dictionary");
}

void detect(int type)
{
	FILE * pFile;
	char string[128];
	pFile = fopen (dicts[type], "r");
	if (pFile == NULL) 
	{
		perror ("Error opening file");
		exit(-1);
	}
	else 
	{	
		begin();
		int fail=0;
		int success=0;
		fgets (string, 128, pFile);
		while (!feof(pFile))
		{
			/* there is a 'next-line' char at the end, remove it */
			string[strlen(string)-1] = '\0';
			if( dict->search(string)) ++success;
			else ++fail;
			fgets (string, 128, pFile);
		}
		fclose (pFile);
		end("detecting");
		printf("\n%d words detected.", success);
		printf("\n%d words failed.", fail);
	}	
}

void add(char* key)
{
	begin();
	if(dict->add(key))
		printf("Add succeed");
	else
		printf("Add fail. It has existed");
	end("adding");
}

void find(char* token)
{
	begin();
	find(dict->search(token),token);
	end("finding");
}

void exit()
{
    delete dict;
	exit(0);
}

//********* help method *************//
void find(bool find, char *token)
{
	if(find)
	{
		printf("%s exists", token);
	}
	else
	{
		printf("%s does not exist.", token);
	}
}

#endif