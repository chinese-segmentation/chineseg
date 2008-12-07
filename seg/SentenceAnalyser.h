
#ifndef __SENTENCE_ANALYSER_H
#define __SENTENCE_ANALYSER_H

#include "common.h"
#include "Dictionary.h"
#include "Sentence.h"


class SentenceAnalyser
{
	enum { MAX_MATCH = 7};
private:

	Dictionary * dict;	// Dictionary for FMM search
	Dictionary * rdict; // Dictionary for RMM search

public:
	
	void setFMMDict(Dictionary *dict);
	void setRMMDict(Dictionary *rdict);

	void analysis(Sentence &sent);
	void fmm_analysis(Sentence &sent);
	void rmm_analysis(Sentence &sent);
};


#endif