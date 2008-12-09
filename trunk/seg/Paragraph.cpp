
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
	do
	{ 
		w=next();
	}while(w==STOP);
	//if( w == END_OF_FILE) 

	sent = new Sentence();
	//sent->add(w);

	do{
		//w = next();
		if( w == END_OF_FILE) 
		{
			more=false;
			break;
		}
		else if( w == STOP) 
		{
			break;
		}
		else {
			sent->add(w);
			w = next();
		}
	}while(true);
	
	return true;
}

Sentence *Paragraph::next_sentence()
{
	return sent;
}



// this implmentation assumes that source is 
// totally GB2312 Encoded except NEXT_LINE with value 10
// and END_OF_FILE with value 0.
word Paragraph::next()
{
	char temp[2];
	temp[0] = nextchar();

	// come across the end of file
	
	if(temp[0] == END_OF_FILE)	return (word)END_OF_FILE;
	else if(temp[0] == NEXT_LINE) temp[0] = nextchar();
	
	unsigned char c = (unsigned char)temp[0];
	//come across a non-chinese-character
	if( !( c>= HIGH_DOWN && c<= HIGH_UP)) 
	{
		//just consume next char	
		nextchar();
		
		//return next word recursively.
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