
#ifndef __DICTIONARY_SORT_H
#define __DICTIONARY_SORT_H

/*
 * sort a text dictionary in dictionary order.
 * if argument *reserved* is true, reserved the word and then sort it.
 */

enum Result
{
	Smaller = -1,
	Equal = 0,
	Larger = 1
};
void sort_dictionary(const char * in_file, bool reserved=false);


#endif