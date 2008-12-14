#include "typedefs.h"

#ifndef __TOKEN_H
#define __TOKEN_H

class Token
{
    enum {HIGH=176, LOW = 160};
    private:
        char * phrase;
        int current;
        int size;
        
    public:
        Token(char* chinese_phrase);
		const char* tostring() { return phrase; }
		void reset();
        bool hasNext();
        word nextWord();
        bool is_end();

        ~Token(){ delete [] phrase;}
};
#endif
