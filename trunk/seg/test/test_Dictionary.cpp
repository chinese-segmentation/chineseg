
#include "test_Dictionary.h"
// *********** test function *****************//

void test_search(Dictionary dd)
{
	char input[128];
	while(true)
	{
		printf("\n> ");
		gets(input);

		if(dd.search(input))
		{
			printf("\nFound %s",input);
		}
		else
		{
			printf("\nNot Found %s",input);
		}
	}
}

void test_all_dict(Dictionary &dd, char * dict)
{
	char input[128];
	FILE * file = fopen(dict,"r");
	FILE * out_file = fopen("C:\\test_all_dict.txt", "w");
	if( file == NULL) 
	{
		printf("Error With Open File: %s",dict);
		exit(-1);
	}
	int i = 0;
	while(fgets(input,128,file) != NULL)
	{
		input[strlen(input)-1] = '\0';
		if(!dd.search(input))
		{
			++i;
			//printf("\nNOT FOUND: %s",input);
			fputs(input, out_file);
			fputs("\n",out_file);
		}
	}
	if( i != 0)
	{
		printf("\n%d Failed!", i );
	}
	else
	{
		printf("\nAll Pass!");
	}
	fclose(out_file);
	fclose(file);
}
void test_dictionary()
{
	printf("\n\nStart test_dictionary()");

	Dictionary txt_fmm_dict;
	txt_fmm_dict.load_from_txt(TXT_FMM_DICT);
	test_all_dict(txt_fmm_dict,TXT_FMM_DICT);

	Dictionary bin_fmm_dict;
	bin_fmm_dict.load_from_bin(BIN_FMM_DICT);
	test_all_dict(bin_fmm_dict, TXT_FMM_DICT);

	printf("\nFinish");
}
