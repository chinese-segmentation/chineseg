
#include "test_Paragraph.h"
#include "../common.h"

char * INPUT = "./test_data/paragraph_test.txt";
char * OUTPUT = "./test_data/paragraph_output.txt";

void test_paragraph()
{
	printf("\nStart test Paragraph");

	FILE* file = fopen(OUTPUT,"w");
	Paragraph p(INPUT);
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
	printf("\nFinish");
}