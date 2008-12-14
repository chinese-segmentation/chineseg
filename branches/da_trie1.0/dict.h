
#ifndef __DICTIONARY_H
#define __DICTIONARY_H

#include "typedefs.h"
#include "trie.h"
#include "token.h"


class Dictionary
{
	private:
        Trie* trie;

	public:
		Dictionary() { trie = new Trie(); }
		~Dictionary() { delete trie; }
		/**
         * initial a dictionary from a "dictionary" file with some standard
         * format.
         */
        Dictionary(const char* dict_file);
		

        /**
         * re-construct this dictionary from a  "dictionary" file with some
         * standard format
         */
        void loadDict(const char* dict);
		
		void reload(const char* dict);

        /**
         * search a Word
         */
        bool search(Token *key);
		bool search(char *key);
		bool add(Token *key);
		bool add(char *key);

		void info();

};
#endif


