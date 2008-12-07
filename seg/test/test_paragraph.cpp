
#include "test_Paragraph.h"
#include "../common.h"

void test_paragraph()
{
	char path[]="C:\\paragraph_test.txt";
	char out[] ="C:\\paragraph_out.txt";
	FILE* file = fopen(out,"w");
	Paragraph p(path);
	
	Sentence *sent = NULL;

	while(p.has_more())
	{
		sent = p.next_sentence();
		char * str = sent->to_string();
		printf("%s\n",str);
		fputs(str,file);
		fputc(0,file);
		delete [] str;
		delete sent;
	}

	fclose(file);
}