
#include "Dictionary.h"

int found_length;		// number of words have been found
int last_location_length; // final location that can be a phrase
int location;	// location of last word found



//  *********** construction & deconstruction **************//
Dictionary::Dictionary()
{
	total_prefix = 0;
	cur_pos = -1;
	size = initial_size;
	allNodes = new Node[size];
}

Dictionary::~Dictionary()
{
	delete [] allNodes;
}


// *********** public function **************//
void Dictionary::load_from_txt(const char * file)
{
	FILE * pFile= fopen(file,"r");
	if(pFile == NULL)
	{
		perror("Can't open dictionary file");
		exit(-1);
	}
	int total_line = get_total_line(pFile);

	//*** first iteartion, collect information **//

	bool* more = new bool[total_line];
	bool* is_same_prefix = new bool[total_line];
	int32* parent_pos = new int32[total_line];


	fseek (pFile, 0, SEEK_SET );
	int line = 0;
	char cur[128];

	word pre_word='\0';
	word cur_word;
	//*** collect first column information ****//
	while(fgets(cur,128,pFile) != NULL)
	{
		more[line] = true;
		//is first word same?
		cur_word = word_at(cur,0);
		if(pre_word == cur_word)
		{
			//line value should never be 0 here.
			assert(line != 0);	
			parent_pos[line] = parent_pos[line-1];
			is_same_prefix[line] = true;
		}
		else
		{
			//initialize new Node
			cur[strlen(cur)-1] = '\0';
			add_Node(cur_word);
			parent_pos[line] = cur_pos;
			is_same_prefix[line] = false;

			//**** intitalize total_prefix ***//
			++total_prefix;
		}
		pre_word = cur_word;
		++line;
	}

	//*******now build the whole data ***************//
	int column = 0;

	while(has_more(more,total_line))
	{
		++column;
		fseek (pFile, 0, SEEK_SET);
		line = 0;
		pre_word = 0;
		cur_word = 0;
		cur[0] = '\0';

		while(fgets(cur,128,pFile) != NULL)
		{
			//current line has remaining word to read.
			if(more[line])
			{
				cur[strlen(cur)-1] = '\0';
				cur_word = word_at(cur,column);
				// current word has same prefix with previous word
				if(is_same_prefix[line])
				{			
					if(pre_word != cur_word)   
					{
						
						is_same_prefix[line] = false;
						add_Node(word_at(cur,column));	

						allNodes[parent_pos[line]].size++;	

						if( allNodes[parent_pos[line]].first== 0)
						{
							allNodes[parent_pos[line]].first = cur_pos;
						}
					}
					else
					{
						//printf("\nSame Prefix: Same Word - %s,parent location: %d, size:%d", cur,parent_pos[line],allNodes[parent_pos[line]].size);
					}
					parent_pos[line] = cur_pos;
				}
				//** current word has different prefix with previsous word **//
				else
				{
					add_Node(word_at(cur,column));

					allNodes[parent_pos[line]].size = 1;
					allNodes[parent_pos[line]].first = cur_pos;

					parent_pos[line] = cur_pos;
				}
				pre_word = cur_word;
				check_next(cur,column, more[line]);

			}		// if(more[line]) then

			else	// if(more[line]) else
			{
				pre_word = 0;
			}
			++line;

		} // while(fgets(cur,128,pFile) != NULL)
	}
	fclose(pFile);
}

void Dictionary::save_as_txt(const char* file )
{
	FILE *pFile = fopen(file,"w");

	char buf[128];
	buf[0] = '\0';

	for(int i = 0; i < total_prefix;i++)
	{
		write_as_txt(pFile,i,buf);
		buf[0] = '\0';
	}
	fclose(pFile);
}

void Dictionary::save_as_bin(const char * file)
{ 
	// format:
	// cur_pos: 32
	// total_prefix: 32
	
	// node
	// data: 16
	// size: 16
	// first: 32
	// is_word: 8

	FILE * out = fopen(file,"wb");
	
	fwrite(&this->size,sizeof(int32),1, out);
	fwrite(&this->cur_pos,sizeof(int32),1, out);
	fwrite(&this->total_prefix,sizeof(int32),1,out);

	for(int i  = 0; i < this->cur_pos; ++i)
	{
		fwrite(&this->allNodes[i],sizeof(struct Node),1,out);
	}
	fclose(out);
}


void Dictionary::load_from_bin(const char * file)
{
	FILE * in = fopen(file,"rb");
	
	fread(&this->size,sizeof(int32),1,in);
	fread(&this->cur_pos,sizeof(int32),1,in);
	fread(&this->total_prefix,sizeof(int32),1,in);
	
	this->size = this->cur_pos;
	delete [] allNodes;
	allNodes = new Node[this->size];

	//printf("\n Size of Struct: %d, Number: %d", sizeof(struct Node),cur_pos);
	for( int i = 0 ; i < this->cur_pos; ++i)
	{
		fread(&this->allNodes[i],sizeof(struct Node),1,in);
	}
	fclose(in);
}

void Dictionary::write_as_txt(FILE * file, int i, char * buf)
{
	char * temp = new char[3];

	if(allNodes[i].is_word == true)
	{
		getchars(i,temp);
		char * temp = WordToTwoChars(allNodes[i].data);
		int length = strlen(buf);
		strncat(buf,temp,2);
		buf[length+2] = '\n';
		buf[length+3] = '\0';
		fputs(buf,file);
		buf[length]='\0';
	}

	if(allNodes[i].size > 0)
	{
		getchars(i,temp);
		int length = strlen(buf);

		strncat(buf,temp,2);
		int32 first = allNodes[i].first;
		for(int j = 0; j < allNodes[i].size; ++j)
		{
			write_as_txt(file, first+j,buf);
		}
		buf[length] = '\0';
	}
	delete [] temp;
}

bool Dictionary::search(word key)
{	
	int32 first_location = allNodes[location].first;
	int32 label_size = allNodes[location].size;

	for(int i = 0; i < label_size; ++i)
	{
		if(allNodes[first_location+i].data == key)
		{
			++found_length;
			if(allNodes[first_location+i].is_word)
			{
				last_location_length = found_length;
			}

			location = first_location+i;
			return true;
		}
	}
	return false;
}

// Error With this method.
bool Dictionary::search(word * words, int words_size)
{
	if(words == NULL || words_size <= 0 ) return false;

	this->reset_initial();

	int32 first_word = find_entrance(words[0]);
	if( first_word == NO_FIRST_WORD) return false;

	// initial global variable
	found_length = 1; 
	location = first_word;

	int32 next_location = allNodes[first_word].first;
	int32 next_size = allNodes[first_word].size;

	int32 cur_size = next_size;
	int32 cur_location = next_location;

	word w = 0;

	int i = 1;
	while(i < words_size)
	{
		w = words[i];
		int j = 0;
		for(j=0; j < cur_size; ++j)
		{
			cur_location = next_location+j;
			if( allNodes[cur_location].data == w) 
			{
				// revise global variable
				++found_length; 
				location = cur_location;
				
				next_location = allNodes[cur_location].first;
				next_size = allNodes[cur_location].size;
				break;
			}
		}
		++i; 
		// some time on the last word j=size=0. so check length first.
		if( i == words_size) break;
		if( j == cur_size) return false;

		cur_location = next_location;
		cur_size = next_size;
	}
	if( allNodes[cur_location].is_word)
		return true;
	else
		return false;
}

bool Dictionary::search(const char * str)
{	
	int size = strlen(str);
	
	if( size%2 != 0)
	{
		printf("\nGB2312 Encoding Input Needed");
		return false;
	}

	word * words = CharsToWords(str);
	bool result = this->search(words,size/2);
	delete [] words;

	return result;
}

int32 Dictionary::find_entrance(word w)
{
	return find_entrance_common_impl(w);
}

int32 Dictionary::find_entrance_common_impl(word w)
{
	for( int32 i = 0; i < total_prefix; ++i)
	{
		if( allNodes[i].data == w)
		{
			last_location_length=0;
			found_length = 0;
			location = i;
			return i;
		}
	}
	return NO_FIRST_WORD;
}

void Dictionary::state()
{
	for( int i = 0; i <= cur_pos; ++i)
	{
		char * buf = WordToTwoChars(allNodes[i].data);
		printf("\n#%d %s", i, buf);
		printf("\nis word? %d", allNodes[i].is_word);
		printf("\nchild size: %d", allNodes[i].size);
		printf("\nfirst child: %d\n", allNodes[i].first);
		delete [] buf;
	}
}

//*********** private function **************//

bool Dictionary::has_more(bool * more, int size)
{
	for(int i = 0; i < size; ++i)
	{
		if(more[i]) return true;
	}
	return false;
}

bool Dictionary::equal(const char* c1, const char* c2)
{
	return !strcmp(c1,c2);
}

word Dictionary::word_at(const char* c, int pos)
{
	return  (word)(((unsigned char)c[2*pos])<<8 ) 
		+ (word)(unsigned char)c[2*pos+1];
}

void Dictionary::check_next(const char * word, int column, bool &has_more )
{
	if( word[2*(column+1) + 1] == '\0')
	{
		has_more = false;
		allNodes[cur_pos].is_word = true;
	}
	else
	{
		has_more = true;
		//** may be a phrase's prefix is a phrase,then we won't change
		//** the flag.
		if( allNodes[cur_pos].is_word ) 
			return;
		allNodes[cur_pos].is_word = false;
	}
}

void Dictionary::add_Node(word _word)
{
	increment_cur_pos();
	allNodes[cur_pos] = Node(_word);
}

void Dictionary::increment_cur_pos()
{
	++ cur_pos;
	if(cur_pos == size)	expand();
}

void Dictionary::getchars(int i, char* & buf)
{
	word w = allNodes[i].data;
	buf[0] = (w&0xff00)>>8;
	buf[1] = w&0x00ff;
	buf[2] = '\0';
}

void Dictionary::expand()
{
	int pre_size = size;
	size *= 2;
	Node * new_allNodes = new Node[size];

	for(int i = 0; i < pre_size; i++)
	{
		new_allNodes[i] = allNodes[i];
	}
	delete [] allNodes;
	allNodes = new_allNodes;
}

int Dictionary::get_total_line(FILE* pFile)
{
	char str[128];
	int total_line = 0;
	while(fgets(str,128,pFile) != NULL)
	{
		total_line++;
	}
	return total_line;
}

void Dictionary::reset_initial()
{
	location=found_length=last_location_length=INITIAL_VALUE;
}

