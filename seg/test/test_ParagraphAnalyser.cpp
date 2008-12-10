
#include "test_ParagraphAnalyser.h"

const char *test_input="./test_data/paragraph_test.txt";
const char *test_output="./test_data/paragraph_test_out.txt";

void test_paragraph_analyser()
{
	printf("\nStart test ParagrapnAnalyser.");

	Dictionary fdict;
	fdict.load_from_txt(TXT_FMM_DICT);
	Dictionary rdict;
	rdict.load_from_txt(TXT_RMM_DICT);
	
	ParagraphAnalyser pa(&fdict,&rdict);
	
	Paragraph para(test_input);
	pa.analysis(&para);

	printf("\nFinish.");
}