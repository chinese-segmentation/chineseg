
#include "SentenceAnalyser.h"
#include "SentenceIterator.h"

void SentenceAnalyser::setFMMDict(Dictionary *dict)
{
	this->dict = dict;
}

void SentenceAnalyser::setRMMDict(Dictionary *rdict)
{
	this->rdict = rdict;
}

void SentenceAnalyser::analysis(Sentence &sent)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
	if( dict != NULL)
		this->fmm_analysis(sent);
	if( rdict != NULL)
		this->rmm_analysis(sent);
}

void SentenceAnalyser::fmm_analysis(Sentence &sent)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
		
	IIterator *iterator=sent.iterator();
	
	while(iterator->has_next())
	{
		word w = iterator->next();
		printf("/%s",WordToTwoChars(w));
		int first = dict->find_entrance(w);
		if(first == Dictionary::NO_FIRST_WORD)
		{
			//TODO: how to collect result
			continue;
		}
		while(iterator->has_next())
		{
			w = iterator->next();
			bool found = dict->search(w);
			if(found)
			{
				printf("%s",WordToTwoChars(w));
			}
			else
			{
				iterator->push_back();
				break;
			}
		}
	}
	delete iterator;
}


void SentenceAnalyser::rmm_analysis(Sentence &sent)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
		
	IIterator *iterator=sent.reserve_iterator();
	
	while(iterator->has_next())
	{
		word w = iterator->next();
		printf("/%s",WordToTwoChars(w));
		int first = dict->find_entrance(w);
		if(first == Dictionary::NO_FIRST_WORD)
		{
			//TODO: how to collect result
			continue;
		}
		while(iterator->has_next())
		{
			w = iterator->next();
			bool found = dict->search(w);
			if(found)
			{
				printf("%s",WordToTwoChars(w));
			}
			else
			{
				iterator->push_back();
				break;
			}
		}
	}
	delete iterator;
}

void SentenceAnalyser::analysis(Sentence &sent, bool flag)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
		
	IIterator *iterator=0;
	Dictionary *mydict=0;
	if(flag == FMM)
	{
		iterator = sent.iterator();
		mydict = this->dict;
	}
	else if( flag == RMM) 
	{
		iterator = sent.reserve_iterator();
		mydict = this->rdict;
	}
	
	while(iterator->has_next())
	{
		word w = iterator->next();
		printf("/%s",WordToTwoChars(w));
		int first = dict->find_entrance(w);
		if(first == Dictionary::NO_FIRST_WORD)
		{
			//TODO: how to collect result
			continue;
		}
		while(iterator->has_next())
		{
			w = iterator->next();
			bool found = dict->search(w);
			if(found)
			{
				printf("%s",WordToTwoChars(w));
			}
			else
			{
				iterator->push_back();
				break;
			}
		}
	}
	delete iterator;
}

