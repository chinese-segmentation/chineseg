#include "../sentence.h"

void test_sentence()
{
	char *src = "这个是测试句子";
	int length = strlen(src)/2;
	word * result = CharsToWords(src);
	
	Sentence sent;
	printf("\nOriginal Words is: \n");
	for(int i = 0; i < length; ++i)
	{
		word cur = result[i];
		printf("%d:%s\t",cur,WordToTwoChars(cur));
		sent.add(result[i]);
	}
	
	printf("\nIterator Result Words is: \n");
	int i = 0;
	
	IIterator* it = sent.iterator();
	while(it->has_next())
	{
		word cur = it->next();
		printf("%d:%s\t",cur,WordToTwoChars(cur));
	}
	delete [] it;
	printf("\nReserve Iterator Result Words is: \n");

	IIterator* re_it = sent.reserve_iterator();
	while(re_it->has_next())
	{
		word cur = re_it->next();
		printf("%d:%s\t",cur,WordToTwoChars(cur));
	}
	delete [] re_it;

	printf("\n");



	printf("Original Sentence is: %s\n", sent.to_string());
}