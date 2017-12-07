#pragma once
#include "BBST.h"
#include "CharString.h"
#include <ostream>
#include "DocList.h"
#include <memory>
#include "WebsiteProcessor.h"
class SearchEngine:public WebsiteProcessor//搜素引擎
{
	BBST* bbst;//平衡二叉树
	const int weight;
public:
	SearchEngine(int weight = 10);
	~SearchEngine(void);
	void buildInvertedFile(const CharString& infile, const CharString& outfile);//从本地文件infile读取信息，构建倒排文档,输出到outfile
	void searchWordList(const CharStringLink& wordList, std::ostream& out);//搜索词，返回搜素结果
	void searchSentences(std::vector<CharString> sentences, std::ostream& out);//先对每个句子进行分词，然后搜索多个关键词，返回搜素结果
	void query(const CharString& queryFile, const CharString& resultFile);//进行批量查询，查询文件为queryFile,结果文件为resultFile
};

