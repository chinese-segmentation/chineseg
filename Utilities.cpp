#include "Utilities.h"

//********** function definition ****************//
word TwoCharsToWord(char  chars[])
{
	word result = 0;
	result = ((unsigned char)chars[0])<<8 | (unsigned char)chars[1] ;
	return result;
}

char* WordToTwoChars(word w)
{
	char *result = new char[3];
	result[0] = (char)(w>>8);
	result[1] = (char)w;
	result[2] = '\0';

	return result;
}


word * CharsToWords(const char * chars)
{
	int length = strlen(chars)/2;
	
	word * words = new word[length];
	char temp[2];
	for( int i = 0; i < length; ++i)
	{
		temp[0] = chars[2*i];
		temp[1] = chars[2*i+1];

		words[i] = TwoCharsToWord(temp);
	}
	return words;
}

char * WordsToChars(word * word, int size)
{
	char * temp = new char[size*2 + 1];
	temp[size*2] = '\0';
	for( int i = 0; i < size; ++i)
	{
		char * ctemp = WordToTwoChars(word[i]);
		temp[2*i] = ctemp[0];
		temp[2*i + 1] = ctemp[1];
		delete [] ctemp;
	}
	return  temp;
}

