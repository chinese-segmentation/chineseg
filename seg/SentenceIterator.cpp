
#include "SentenceIterator.h"

Iterator::Iterator(Sentence * sent)
{
	this->sent = sent;
	cur = -1;
	size = sent->get_size();
}

bool Iterator::has_next()
{
	return cur < size-1;
}

word Iterator::next()
{
	return sent->get_data(++cur);
}

void Iterator::reset()
{
	cur=-1;
}
void Iterator::push_back()
{
	if( cur != -1) --cur;
}

ReserveIterator::ReserveIterator(Sentence *sent)
{
	this->sent = sent;
	this->size = sent->get_size();
	cur = size;
}

bool ReserveIterator::has_next()
{
	return cur > 0;
}

word ReserveIterator::next()
{
	return sent->get_data(--cur);
}

void ReserveIterator::reset()
{
	cur = size;
}

void ReserveIterator::push_back()
{
	if( cur != size) --cur;
}