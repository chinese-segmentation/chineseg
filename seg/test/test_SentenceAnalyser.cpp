
#include "test_SentenceAnalyser.h"

void test_sentence_analyser()
{
	char dictFile[] = "C:\\dict_final.txt";
	char rdictFile[] = "C:\\dict_reserved_final.txt";

	Dictionary dict;
	//Dictionary rdict;
	dict.load_from_txt(dictFile);
	
	SentenceAnalyser analyser;
	analyser.setFMMDict(&dict);
	
	Sentence sent1("偶尔我们还是希望在类的构造函数里调用另一个构造函数");
	Sentence sent2("社科院世界政治与经济研究所国际金融研究中心秘书长张明认为从最新的表态来看央行至少已经在考虑以贬值来保增长的可能性兴业银行资金营运中心首席经济学家鲁政委则旗帜鲜明地指出这是决策层面第一次提出运用汇率手段");
	analyser.analysis(sent1);
	analyser.analysis(sent2);
	//rdict.load_from_txt(rdictFile);
	
}