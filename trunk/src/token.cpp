#include "token.h"

#include <string.h>
#include <stdio.h>

Token::Token(char* chinese_phrase)
{
    size = strlen(chinese_phrase);
    current = -1;
    phrase = new char[size+1];
    memcpy(phrase,chinese_phrase,size + 1);
#if 0
    for(int j = 0; j < size; j++)
    {
        printf("%d:%d ", j,(uint8)phrase[j]);
    }

#endif
}

void Token::reset()
{
    current = -1;
}

word Token::nextWord()
{
    if(hasNext())
    {
        ++current;
        return ((uint32)((uint8)phrase[2*current] - HIGH)<<8)
                 + (uint8)phrase[2*current+1] - LOW;
    }
    else
    {
        return 0;
    }
}

bool Token::hasNext()
{
    return (current < size/2-1 && size>0);
}

bool Token::is_end()
{
    return !hasNext();
}


