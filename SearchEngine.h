#pragma once
#include "BBST.h"
#include "CharString.h"
#include <ostream>
class SearchEngine//��������
{
	BBST* bbst;//ƽ�������
public:
	SearchEngine(void);
	~SearchEngine(void);
	void buildInvertedFile(const CharString& infile, const CharString& outfile);//�ӱ����ļ�infile��ȡ��Ϣ�����������ĵ�,�����outfile
	void searchWordList(std::vector<CharString> wordList, std::ostream& out);//�����ʣ��������ؽ��
	void searchSentence(const CharString& sentence);//�������ӣ��������ؽ��
};

