#include "dictionary_sort.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum Result
{
	Smaller = -1,
	Equal = 0,
	Larger = 1
};

// We assume that th
const int CHARS_SIZE = 32;

Result compare(const char* c1, const char* c2);
int partitial(char** all_line, int begin, int end);
void quick_sort(char** all_line, int begin, int end);
void exchange( char* &a, char* &b);


void sort_dictionary(const char * file_path, bool reserved)
{
	FILE* file = fopen(file_path, "r");
	char buf[CHARS_SIZE];

	int line = 0;
	while(fgets(buf,CHARS_SIZE, file) != NULL)
	{
		// remove single words
		if(strlen(buf) == 3) continue;
		++line;
	}
	if( line == 0)  return;
	
	char** all_lines = new char*[line];
	for(int i = 0; i < line; i++)
	{
		all_lines[i] = new char[CHARS_SIZE];
	}

	fseek(file,0,SEEK_SET);

	int i = 0;
	while(fgets(buf,CHARS_SIZE,file) != NULL)
	{
		if(strlen(buf) == 3) continue;
		strcpy(all_lines[i++],buf);
	}
	fclose(file);

	if(reserved)
	{
		for( int i = 0; i < line; ++i)
		{
			int len = ( strlen(all_lines[i])-1 ) / 2;
			for(int j = 0; j < len/2; ++j)
			{
				char temp = all_lines[i][2*j];
				all_lines[i][2*j] = all_lines[i][2*(len-j-1)];
				all_lines[i][2*(len-j-1)] = temp;

				temp = all_lines[i][2*j+1];
				all_lines[i][2*j+1] = all_lines[i][2*(len-j-1)+1];
				all_lines[i][2*(len-j-1)+1] = temp;
			}
		}
	}

	srand(time(0));
	printf("\nBegin Quick Sort...");
	quick_sort(all_lines, 0, line-1);
	
	char output_file[128];
	char path[128];

	if(reserved)
	{
		sprintf(output_file,"C:\\dict_reserved_%d.txt", time(0)); 
	}
	else
	{
		sprintf(output_file,"C:\\dict_%d.txt", time(0)); 
	}
	
	FILE* output = fopen(output_file,"w");
	
	printf("\nSort Finish.Begin Write to File: %s",output_file);
	
	FILE * removed = fopen("C:\\removed.txt","w");
	int j = 0;

	fputs(all_lines[0], output);
	for(int i=1; i < line; ++i)
	{
		if(compare(all_lines[i-1],all_lines[i]) == Equal)
		{
			++j;
			fputs(all_lines[i],removed);	
			continue;
		}
		fputs(all_lines[i],output);
	}
	fclose(output);
	printf("\nFinish.\n%d Lines Removed.\n", j);

	for(int i = 0; i < line; ++i)
	{
		delete [] all_lines[i];
	}
	delete [] all_lines;
}

void exchange( char* &a, char* &b)
{
	char * temp = a;
	a = b;
	b = temp;
}

int partitial(char** all_line, int begin, int end)
{
	//printf("\nPartition %d -> %d", begin, end);
	// random partitial
	if(begin != end)
	{
		int r = (rand()<<3) % (end-begin) + begin;
		exchange(all_line[r],all_line[end]);
	//	printf("\tExchange %d <=> %d", r, end);
	}
	char *x = all_line[end];
	int i = begin-1;
	int j;
	for( j = begin; j < end; ++j)
	{
		Result result = compare(all_line[j],x);
		if( result == Smaller || result ==Equal)
		{
			++i;
			exchange(all_line[j],all_line[i]);
		}
	}
	++i;
	exchange(all_line[i],all_line[end]);

//	printf("\tPartitial At: %d",i);
	return i;
}

void quick_sort(char** all_line, int begin, int end)
{
	if( begin < end ) {
		
		int partition = partitial(all_line,begin, end);
		
		if( partition != begin) quick_sort(all_line,begin,partition-1);
		if( partition != end) quick_sort(all_line,partition+1,end);
	}
}

Result compare(const char* arr1, const char* arr2)
{
	int f = strlen(arr1);
	int s = strlen(arr2);

	int min = f<s ? f : s;
	for(int i = 0; i < min; ++i)
	{
		unsigned char c1 = arr1[i];
		unsigned char c2 = arr2[i];

		if( c1 < c2) return Smaller;
		if ( c1 > c2) return Larger;
		
		continue;
	}

	if( f == s) return Equal;
	if( f < s) return Smaller;
	if( f > s) return Larger;
}



