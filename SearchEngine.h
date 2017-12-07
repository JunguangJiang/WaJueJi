#pragma once
#include "BBST.h"
#include "CharString.h"
#include <ostream>
#include "DocList.h"
#include <memory>
#include "WebsiteProcessor.h"
class SearchEngine:public WebsiteProcessor//��������
{
	BBST* bbst;//ƽ�������
	const int weight;
public:
	SearchEngine(int weight = 10);
	~SearchEngine(void);
	void buildInvertedFile(const CharString& infile, const CharString& outfile);//�ӱ����ļ�infile��ȡ��Ϣ�����������ĵ�,�����outfile
	void searchWordList(const CharStringLink& wordList, std::ostream& out);//�����ʣ��������ؽ��
	void searchSentences(std::vector<CharString> sentences, std::ostream& out);//�ȶ�ÿ�����ӽ��зִʣ�Ȼ����������ؼ��ʣ��������ؽ��
	void query(const CharString& queryFile, const CharString& resultFile);//����������ѯ����ѯ�ļ�ΪqueryFile,����ļ�ΪresultFile
};

