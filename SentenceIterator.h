
#ifndef __SENTENCEITERATOR_H
#define __SENTENCEITERATOR_H

#include "common.h"

class Sentence;

// Iterator interface for sentence
class IIterator
{
public:
	virtual bool has_next()=0;
	virtual word next()=0;

	virtual void reset()=0;
	virtual void push_back()=0;
};

class Iterator : public IIterator
{
private:
	int size;
	int cur;
	Sentence *sent;
	Iterator(){}

public:
	Iterator(Sentence *sent);
	bool has_next();
	word next();
	void reset();
	void push_back();
};

class ReserveIterator : public IIterator
{
private:
	Sentence *sent;
	int size;
	int cur;
	ReserveIterator() {}

public:
	ReserveIterator(Sentence *sent);
	bool has_next();
	word next();
	void reset();
	void push_back();
};

#endif