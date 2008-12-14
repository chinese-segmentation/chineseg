
#ifndef __PARAGRAPH_ANALYSER_H
#define __PARAGRAPH_ANALYSER_H

#include "SentenceAnalyser.h"
#include "Paragraph.h"

class ParagraphAnalyser
{

private:
	SentenceAnalyser sa;

	ParagraphAnalyser(ParagraphAnalyser &);
	ParagraphAnalyser operator=(ParagraphAnalyser &);
public:
	
	ParagraphAnalyser(Dictionary *fmm_dict,Dictionary *rmm_dict)
	{
		sa.setFMMDict(fmm_dict);
		sa.setRMMDict(rmm_dict);
	}

	// analysis in a Paragraph list
	void analysis(Paragraph* paras, int length);
    // analysis 
	void analysis(Paragraph* para);

private:

};

#endif
