
#include "common.h"

#ifndef __UTILITIES_H
#define __UTILITIES_H

//*********** function declaration ***************//
/**
 * a chinese character is two bytes, convert it to word(16-bits) type
 */
word TwoCharsToWord(char  chars[]);

/**
 * convert a word into two chars
 */
char* WordToTwoChars(word w);

/**
 * convert char array into word array
 */
word * CharsToWords(const char * chars);

/**
 * convert word array into char array)
 */
char * WordsToChars(word * word, int size);

#endif