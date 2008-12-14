
#include "ParagraphAnalyser.h"


void ParagraphAnalyser::analysis(Paragraph * para)
{
	while(para->has_more())
	{
		Sentence * s = para->next_sentence();
		sa.analysis(*s);
		delete s;
	}
}

void ParagraphAnalyser::analysis(Paragraph *para,int length)
{
	for(int i = 0; i < length; ++i)
		this->analysis(&para[i]);
}