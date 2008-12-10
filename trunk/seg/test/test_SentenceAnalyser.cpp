
#include "test_SentenceAnalyser.h"

void test_sentence_analyser()
{
	printf("\nStart test SentenceAnalyser");

	Dictionary dict;
	Dictionary rdict;
	dict.load_from_txt(TXT_FMM_DICT);
	rdict.load_from_txt(TXT_RMM_DICT);
	
	SentenceAnalyser analyser;
	analyser.setFMMDict(&dict);
	analyser.setRMMDict(&rdict);
	
	Sentence sent1("ż�����ǻ���ϣ������Ĺ��캯���������һ�����캯��");
	Sentence sent2("���Ժ���������뾭���о������ʽ����о��������鳤������Ϊ�����µı�̬�������������Ѿ��ڿ����Ա�ֵ���������Ŀ�������ҵ�����ʽ�Ӫ��������ϯ����ѧ��³��ί������������ָ�����Ǿ��߲����һ��������û����ֶ�");
	
	analyser.analysis(sent1);
	analyser.analysis(sent2);
	
	printf("\nFinish.");
}