
#include "test.h"
#include "dict.h"

#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[])
 {
	dict = new Dictionary();
	char input[128];
	print_help();
	while(true)
	{
		printf("\n> ");
		gets(input);
		if(!strcmp(input,"help")) print_help();
		else if(!strcmp(input,"reset")) reset();
		else if(!strcmp(input,"exit")) exit();
		else if(!strcmp(input,"state")) print_state();
		else
		{	
			char command[128];
			char argu[128];
			uint32 i=0;
			for(i=0; i< strlen(input);++i)
			{
				if(input[i]==' ')
				{ 
					command[i]='\0';
					++i;
					break;
				}
				else command[i] = input[i];
			}
			for(int j=0;i<=strlen(input);++i,++j)
			{
				argu[j] = input[i];
			}

			if(!strcmp(command,"load") || !strcmp(command,"detect"))
			{
				int type=-1;
				if( !strcmp(argu,"small")) type = SMALL;
				else if(!strcmp(argu,"medium")) type= MEDIUM;
				else if(!strcmp(argu,"large")) type=LARGE;
				if( type != -1)
				{
					if(!strcmp(command,"load")) load(type);
					if(!strcmp(command,"detect")) detect(type);
				}
				else
				{
					printf("Error Argu.See Help");
				}
			}
			else if(!strcmp(command,"add"))
			{
				add(argu);
			}
			else if(!strcmp(command,"find"))
			{
				find(dict,argu);
			}
			else
			{
				printf("Error Command. Please enter `help` to see usage.");
			}
		}
	}

	/* Dictionary* dict = new Dictionary();
	 dict->add("รว");
	 dict->add("ฮา");

	 delete dict;
    return 0;*/
}
//---------------------------------------------------------------------------
