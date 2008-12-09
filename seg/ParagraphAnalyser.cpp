
#include "ParagraphAnalyser.h"


void ParagraphAnalyser::analysis(Paragraph *para)
{
	while(para->has_more())
	{
		Sentence * s = para->next_sentence();
		sa.analysis(*s);

		delete s;
	}
}