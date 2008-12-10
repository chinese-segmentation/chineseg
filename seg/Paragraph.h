
#ifndef __PARAGRAPH_H
#define __PARAGRAPH_H

#include "common.h"
#include "Sentence.h"

class Paragraph
{
	enum { BUFFER_SIZE = 4096};
	
	enum { END_OF_FILE=0,NEXT_LINE=10,STOP=1};
	
	/** 
	 * GB2312 code range for character.
	 * First half:	0xB0-0xF7
	 * Second half: 0xA0-0xFE
	 */
	enum {HIGH_DOWN=0xB0, HIGH_UP=0xF7, LOW_DOWN=0xA0, LOW_UP=0xFE}; 

private:	
	// a txt file source provider, we assume that the source file
	// is totally GB2312 Encoded.
	FILE * source;
	char buffer[BUFFER_SIZE];
	int size;
	int cursor;
	Sentence * sent;
	
	bool more;
public:
	Paragraph(const char * );
	Sentence *next_sentence();
	bool has_more();
	
private:
	word next();
	char nextchar();
};


#endif