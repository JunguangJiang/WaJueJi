#pragma once
#include "BBST.h"
#include "CharString.h"
#include <ostream>
class SearchEngine//搜素引擎
{
	BBST* bbst;//平衡二叉树
public:
	SearchEngine(void);
	~SearchEngine(void);
	void buildInvertedFile(const CharString& infile, const CharString& outfile);//从本地文件infile读取信息，构建倒排文档,输出到outfile
	void searchWordList(std::vector<CharString> wordList, std::ostream& out);//搜索词，返回搜素结果
	void searchSentence(const CharString& sentence);//搜索句子，返回搜素结果
};

