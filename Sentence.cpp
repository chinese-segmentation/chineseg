#include "Sentence.h"
#include "Utilities.h"

Sentence::Sentence()
{
	capacity = 4;
	data = new word[capacity];
	size = 0;
	cur = -1;
}

Sentence::Sentence(char * sent)
{
	capacity = 4;
	data = new word[capacity];
	size = 0;
	cur = -1;

	for( int i=0; i < strlen(sent)/2; ++i)
	{
		char temp[2];
		temp[0] = sent[2*i];
		temp[1] = sent[2*i+1];
		add(TwoCharsToWord(temp));
	}
}
Sentence::~Sentence()
{

	delete [] data;
}

int Sentence::get_size()	
{
	return size;	
}

word Sentence::get_data(int i)
{
		return data[i];
}
void Sentence::add(word d)
{
	if( size == capacity) double_capacity();
	data[size++] = d;
}

void Sentence::double_capacity()
{
	int temp = capacity;
	capacity *= 2;

	word * new_data = new word[capacity];

	for(int i = 0;  i < size; i++)
	{
		new_data[i] = data[i];
	}
	delete [] data;
	data = new_data;
}

IIterator* Sentence::iterator()
{
	return new Iterator(this);
}

IIterator* Sentence::reserve_iterator()
{
	return new ReserveIterator(this);
}

char * Sentence::to_string()
{	
	return	WordsToChars(data,size);	
}
