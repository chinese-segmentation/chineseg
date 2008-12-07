
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
	
	Sentence sent1("ż�����ǻ���ϣ������Ĺ��캯���������һ�����캯��");
	Sentence sent2("���Ժ���������뾭���о������ʽ����о��������鳤������Ϊ�����µı�̬�������������Ѿ��ڿ����Ա�ֵ���������Ŀ�������ҵ�����ʽ�Ӫ��������ϯ����ѧ��³��ί������������ָ�����Ǿ��߲����һ��������û����ֶ�");
	analyser.analysis(sent1);
	analyser.analysis(sent2);
	//rdict.load_from_txt(rdictFile);
	
}