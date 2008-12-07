
#ifndef __DICT_H
#define __DICT_H

#include "common.h"


typedef int16 LABEL_SIZE;
typedef int32 label_f;


extern int found;		// number of words have been found
extern int location;	// location of last word found

int have_found();
int last_location();

/**
 *	a Node represent a state in Trie data struct 
 */
struct Node
{
	word data;			// 16 bits
	LABEL_SIZE size;		
	label_f first;
	bool is_word;
	 
	Node()
	{
		data=0;
		size=first=0;
		is_word=false;
	}

	Node(word data):data(data)
	{
		size=first=0;
		is_word=false;
	}

	Node(word data, LABEL_SIZE size, label_f f, bool is_word):
		data(data),
		size(size),
		first(f),
		is_word(is_word)
	{ 
	}
};

class Dictionary
{
public:
	int const static INITIAL_VALUE=-1;
	int const static NO_FIRST_WORD=0xBAADBABE;

private:
	const static int32 initial_size = 1;
	Node * allNodes;
	int32 size;
	int32 cur_pos;
	int32 total_prefix;


public:
	Dictionary();
	~Dictionary();

private:

	bool has_more(bool * more, int size);
	bool equal(const char* c1, const char* c2);
	word word_at(const char* c, int pos);
	void check_next(const char * word, int column, bool &has_more );
	void add_Node(word _word);
	void increment_cur_pos();
	void getchars(int i, char* & buf);
	void expand();
	int get_total_line(FILE* pFile);
	

	void write_as_txt(FILE * file, int i, char * buf);
	void reset_initial();

	//a primary implementation for find_entrance
	int32 find_entrance_common_impl(word w);
public:
	
	//TODO: these method should me remove to factory class
	void load_from_txt(const char * file);
	void load_from_bin(const char * file);
	void save_as_txt(const char * file);
	void save_as_bin(const char * file);
	
	//********** method for search *********//
	bool search(word key);
	bool search(const char * str);
	bool search(word * words, int width);
	
	// find first word location
	int32 find_entrance(word w);
	

	void state();
};



#endif