
#include "SentenceAnalyser.h"
#include "SentenceIterator.h"

//buffer for output
//assume a sentence has no more than 1000 word.
char sentence_buffer[4048];

void SentenceAnalyser::setFMMDict(Dictionary *dict)
{
	this->dict = dict;
}

void SentenceAnalyser::setRMMDict(Dictionary *rdict)
{
	this->rdict = rdict;
}

//TODO: how to collect analysis result
void SentenceAnalyser::analysis(Sentence &sent)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
	char *original = sent.to_string();
	printf("\nOriginal Sentence:\n\t%s", original);
	delete [] original;
   
	if( dict != NULL)
	{
		printf("\nForward Maximum Match:\n\t");
		this->fmm_analysis(sent);
	} 
	
		
	if( rdict != NULL)
	{
		printf("\nReserve Maximum Match:\n\t");
		this->rmm_analysis(sent);
	}
}

void SentenceAnalyser::fmm_analysis(Sentence &sent)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
		
	IIterator *iterator=sent.iterator();
	
	sentence_buffer[0] = '\0';
	while(iterator->has_next())
	{
		word w = iterator->next();
		
		strcat(sentence_buffer,"/");
		//*****
		char *result = WordToTwoChars(w);
		strcat(sentence_buffer,result);
		delete [] result;
		//*****

		int first = dict->find_entrance(w);
		if(first == Dictionary::NO_FIRST_WORD)
		{
			continue;
		}
		while(iterator->has_next())
		{
			w = iterator->next();
			bool found = dict->search(w);
			if(found)
			{
				//*******
				char *result = WordToTwoChars(w);
				strcat(sentence_buffer,result);
				delete [] result;
				//*******
			}
			else
			{
				//push back the word just read
				iterator->push_back();

				//push back all word until the location which is the end of a phrase.
				while(found_length>last_location_length)
				{
					iterator->push_back();
					--found_length;
					sentence_buffer[strlen(sentence_buffer)-2] = '\0'; 
				}
				break;
			}
		}
	}
	delete iterator;
	printf(sentence_buffer);
}


void SentenceAnalyser::rmm_analysis(Sentence &sent)
{
	if(sent.get_size() <= 1)
	{
		printf(sent.to_string());
		return;
	}
		
	IIterator *iterator=sent.reserve_iterator();
	
	sentence_buffer[0] = '\0';
	while(iterator->has_next())
	{
		word w = iterator->next();
		
		strcat(sentence_buffer,"/");
		//*****
		char *result = WordToTwoChars(w);
		strcat(sentence_buffer,result);
		delete [] result;
		//*****

		int first = rdict->find_entrance(w);
		if(first == Dictionary::NO_FIRST_WORD)
		{
			continue;
		}
		while(iterator->has_next())
		{
			w = iterator->next();
			bool found = rdict->search(w);
			if(found)
			{
				//*****
				char *result = WordToTwoChars(w);
				strcat(sentence_buffer,result);
				delete [] result;
				//*****
			}
			else
			{
				// push the word just read back
				iterator->push_back();

				//push back all word until the location which is the end of a phrase.
				while(found_length>last_location_length)
				{
					iterator->push_back();
					--found_length;
					sentence_buffer[strlen(sentence_buffer)-2] = '\0'; 
				}
				break;
			}
		}
	}
	delete iterator;
	printf(sentence_buffer);
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

