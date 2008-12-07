
#include "Paragraph.h"
#include "Utilities.h"


Paragraph::Paragraph(const char * file)
{
	source = fopen(file,"r");
	if(source == NULL)
	{
		printf("\nCan't open file %s.",file);
		exit(-1);
	}
		
	size = fread(buffer,sizeof(char),BUFFER_SIZE,source);
	cursor = -1;
	more=true;
}

// load next sentence here.
bool Paragraph::has_more()
{
	if(!more) return false;

	word w;

	sent = new Sentence();
	do{
		w = next();
		if( w == END_OF_FILE) 
		{
			more=false;
			break;
		}
		if( w == STOP) break;
		else sent->add(w);
	}while(true);
	
	return true;
}

Sentence *Paragraph::next_sentence()
{
	return sent;
}



// this implmentation assume that source file is 
// GB2312 Encoding.
word Paragraph::next()
{
	char temp[2];

	temp[0] = nextchar();

	// come across the end of file
	if(temp[0] == '\0')	return (word)END_OF_FILE;
	
	
	unsigned char c = (unsigned char)temp[0];
	//come across a sign
	if( !( c>= HIGH_DOWN && c<= HIGH_UP)) 
	{
		
		if(temp[0]>0 && temp[0]<127) 
		{
			return next();
		}
		
		return (word)STOP;
	}
	// return a chinese character.
	temp[1] = nextchar();
	return TwoCharsToWord(temp);
}

char Paragraph::nextchar()
{
	char c;
	if( cursor < size-1 && size!=0)
		c= buffer[++cursor];
	else
		c='\0';

	if(cursor == BUFFER_SIZE-1)
		size = fread(buffer,sizeof(char),BUFFER_SIZE,source);
	
	return c;
}