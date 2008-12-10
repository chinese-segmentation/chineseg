#include "typedefs.h"
#include "token.h"

#include "stdlib.h"
#include "stdio.h"

#ifndef __TRIE_H
#define __TRIE_H

#define DO_PRINT 1;

struct da_state
{
    enum { INITIAL_SIZE=1};
    int32 base;    /* base array */
    int32 check;   /* check array */
    
	bool is_final;	 /* flag whether the state can be final state */
	int32* label;    /* a list R what is a arc set from current state  */
	
    int32 label_size;
    int32 actual_label_size;


    void init()
	{
        base = check = actual_label_size =label_size= 0;
        label = NULL;
		is_final = false;
    }

	void reset()
	{
		delete [] label;
		init();
	}

    int32 get_label(int32* &handle)
	{	
		handle = label;
        return actual_label_size;
    }

    void add_label(int32 add_label)
    {
        if(label == NULL)
        {
            label_size = INITIAL_SIZE;
            label = new int32[INITIAL_SIZE];
        }
        else if( actual_label_size == label_size)
        {
            int32 pre_size = label_size;
			label_size *= 2;
            int32 * new_label = new int32[label_size];
            for(int i=0; i < pre_size; i++)
			{
				new_label[i] = label[i];
			}
			delete [] label;
			label = new_label;

        }
        label[actual_label_size++] =  add_label;
    }
    
	da_state()
	{
		base = check = actual_label_size =label_size= 0;
        is_final = false;
		label = NULL;
	}


	/* assign construction */
	da_state & operator= (const da_state& o)
	{
		if( this == &o)
			return *this;
		delete [] label; //free old label;
		label = NULL;
		base = o.base;
		check = o.check;
		label_size = o.label_size;
		is_final = o.is_final;
		for(int i = 0; i < o.actual_label_size; i++)
		{
			add_label(o.label[i]);
		}
		return *this;
	}
	
   ~da_state()
	{ 
		delete [] label; 
	}
};


class Trie
{
    enum { INITIAL_SIZE = 1024, NON_MATCH=-1  };

    private:
        da_state *da;	/* an double array */
        int32 da_size;  /* size of double array */
        int32 base_pos; /* current base index of the double array */
		int32 entry_size; /* entry numbers having been added */

    public:
		//**************** default construction ******************//
        Trie();

		//**************** deconstruction function ***************// 
		~Trie();

        /**
         * search a word.
         * if the word exists, then return TRUE;
         * else return FALSE;
         */
        bool retrieve(Token * entry);

        /**
         * insert a Token into
		 * If the entry have exited, return false;
         * if the entry does not exist, the entry will be appended and return true.
         */
        bool insert(Token * entry);

        /**
         * delete a Token,
		 * If the entry does not exist, delete nothing, just return false.
		 * If the entry exists, delete the entry, then return true.
         */
        bool remove(Token * entry);

		/**
		 * print state
		 */
		void print_state();

		int32 entry_number() 
		{
			return entry_size;
		}

    private:
        
		//**** calculate next t = g(s,a), return next state.If NON-MATCH returned, it indicate retireve fail ****//
        int32 forward(int32 s, word a);
		
		//**** do doublize the size of double-array iteraly until array size is not small than min ****/
         void re_alloc(int32 min=-1);
		
		/* find a new base value for index *idx* */
		int32 x_check(int32 idx);

        //****************** method for access double array **********************//
        inline void w_base(int32 index, int32 v) { da[index].base = v;}
        inline void w_check(int32 index, int32 v) { da[index].check = v; }
        inline int32 r_base(int32 index) { return da[index].base; }
        inline int32 r_check(int32 index) { return da[index].check; }

		//******************* method for dealing with label *********************//
		int32 label_size(int32 idx) { return da[idx].actual_label_size; }
		void add_label(int32 idx, int32 label){ da[idx].add_label(label); }
		int32 get_label(int32 idx, int32 lable_idx) { return da[idx].label[lable_idx];}

		//******************* method for accessing final flag *******************//
		bool is_final(int32 idx) { return da[idx].is_final; }
		void set_final(int32 idx, bool is_finale) { da[idx].is_final = idx; }

};

#endif
