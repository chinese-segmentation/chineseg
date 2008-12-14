
#ifndef __SENTENCE_H
#define __SENTENCE_H

#include "common.h"
#include "SentenceIterator.h"

class IIterator;

class Sentence
{
private:
	word * data;
	int capacity;
	
	int size;
	int cur;

public:
	Sentence();
	Sentence(char * sent);
	~Sentence();

	int get_size();
	word get_data(int i);

	IIterator* iterator();
	IIterator* reserve_iterator();

	/*bool has_next();
	word next();
	void reset();
	void push_back();*/
	
	char *to_string();
    void add(word d); 
	
private:
	void double_capacity();

	//friend class IIterator;
};

#endif

