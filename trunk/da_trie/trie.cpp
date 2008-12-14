#include "trie.h"
#include "token.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Trie::Trie()
{
    da_size = INITIAL_SIZE;
    da = new da_state[da_size];
	for(int i = 0; i < da_size; i++)
	{
		da[i].init();
	}
    base_pos = 1;
    w_base(base_pos, 1); /* initial base_pos value 1 */
    entry_size = 0;
}

Trie::~Trie() 
{ 
	delete [] da; 
}

bool Trie::retrieve(Token * token)
{
    int32 s = base_pos;   /* base */
    int32 t;              /* check */
    word w;
	token->reset();
	while( token->hasNext())
    {
        w = token->nextWord(); 
		t = forward(s, w);
        if( t == NON_MATCH)
            return false;

		if( token->hasNext()) s = t;
		else return is_final(t);
    }
    return false;
}

int32 Trie::forward(int32 s, word a)
{
    int32 t = r_base(s) + a;
    if(t < da_size && r_check(t) == s) return t;
    else return  NON_MATCH;
}

bool Trie::insert(Token * token)
{
	//printf("\nadding entry:%s", token->tostring()); 
    
	word w=0;
    int32 cur_pos = base_pos;
	int32 next_pos = -1;
	/**
	 * Subject to next state's *check* value, there are three conditions:
     *
	 * If it is zero:
	 * 1. A zero value indicates that state yet have been used, so there 
	 * is no collision, the state can be used directly.
     
	 * If it is a non-zero value:
     * 2. The value is identifed to current state.This is common
     * because of there existing many *prefix* in human natural language. It's not
     * a collision, we can just walk ove it and do no change to it.
     * 3. Value saved in next state's check is not equal to current state,
     * this indicates that the state has been used.that's say,there has been an arce, one from
     * a different state to it, existing in the trie. A collision
     * happened, so engaged states will be modifed to resolve the collision.
     */
	while(token->hasNext())
    {
        w=token->nextWord();
        next_pos = r_base(cur_pos) + w;

		// check double array length, expand it if necessary
		if( next_pos >= da_size)   re_alloc(next_pos);     

		
		if (r_check(next_pos) == cur_pos)
        {
			//do nothing just walk pass it
		}
        else if( r_check(next_pos) == 0)
        {	
			add_label(cur_pos, w);
			w_check(next_pos, cur_pos); 
			w_base(next_pos, base_pos);     	
        }
        else
        {
			add_label(cur_pos, w);
            
			int32 new_base_pos = x_check(cur_pos);
			int32 old_base_pos = r_base(cur_pos);
			
			// change current state base value.
			w_base(cur_pos, new_base_pos);
			
            //** below modify other labels involved***// 
            for(int32 i = 0; i < label_size(cur_pos) -1; i++)
            {
                int32 old_t = old_base_pos + get_label(cur_pos,i);
                int32 new_t = new_base_pos + get_label(cur_pos,i);
			
                if( label_size(old_t) > 0)
                {
                    for( int32 j = 0; j < label_size(old_t); j++)
                    {
                        int32 sub_label_pos =  r_base(old_t) + get_label(old_t,j);
						w_check(sub_label_pos,new_t);
                    }
                }
				//*** copy old state to new state ****//
				da[new_t] = da[old_t];
				da[old_t].reset();
            }
			
			// next position should be re-calculate based on new base value
			next_pos = new_base_pos + w;
			
			//*** here save the new node 
			w_check(next_pos, cur_pos); 
			w_base(next_pos,base_pos);
        }
		cur_pos = next_pos;
    }
	if(is_final(next_pos))
	{	
		return false;
	}
	else
	{
		set_final(next_pos,true);
		++entry_size;
		return true;
	}
}

bool Trie::remove(Token * token)
{
    return false;
}

int32 Trie::x_check(int32 idx)
{
    int32 handle_size = label_size(idx) ;

    for(int32 new_base = 1; new_base < da_size; new_base++)
    {
		bool is_ok=true;
		int32 j=0;
		for( j = 0; j < handle_size; j++)
		{
			int32 check_pos = new_base+ get_label(idx,j);
			if(check_pos >= da_size) re_alloc(da_size*2);
			if( r_check(check_pos) != 0 )
			{
				is_ok=false;
				break;
			}
		}
		if(is_ok && j==handle_size) return new_base;
     }
     return da_size;     
}

void Trie::re_alloc(int32 min)
{   
	int32 pre_da_size = da_size;
	do da_size *= 2; while( da_size < min);

    //TODO:What's wrong with this statement ????????????? //
    // da = (da_state*) realloc(da, sizeof(struct da_state)*da_size);
	
	// Problem: don't use malloc with delete, always molloc/free, new/delete
	//da_state *new_da = (da_state*) malloc(sizeof(struct da_state)*da_size);
	da_state *new_da = new da_state[da_size];

	// move old date to new array
	for(int32 i = 0; i < pre_da_size; i ++)
	{
		new_da[i] = da[i];
	}
	//delete old da array
	delete [] da;
	da = new_da;
}

void Trie::print_state()
{
	int32 memory_usage = sizeof(struct da_state)* da_size;
	int32 used_state = 0;
	for(int32 i=0; i< da_size; i++)
	{
		if(r_check(i) != 0) ++used_state;
		int j=label_size(i);
		memory_usage += sizeof(int32)*j;
	}

	printf("\n++++++++Trie State+++++++++");
	printf("\nTotal Entry Number: %d", entry_size);
	printf("\nMemory Used: %d bytes",memory_usage);
	printf("\nAvailable State Size(a): %d", da_size);
	printf("\nUsed State Number(u): %d", used_state);
	printf("\nUsed Percentage(a/u): %f",float(used_state)/(float)da_size);
}


