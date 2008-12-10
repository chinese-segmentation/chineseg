#include "Dictionary.h"
#include "Sentence.h"
#include "SentenceAnalyser.h"

#include "tools/dictionary_sort.h"
#include "./test/test_all.h"
int main()
{
	/*sort_dictionary("C:\\large.txt", true);
	sort_dictionary("C:\\large.txt", false);
	test_sentence();
	test_load_from_txt();
	test_sentence_analyser();*/

	//test_all();

	//test_paragraph();
	test_paragraph_analyser();
}