#pragma once

#include "CharString.h"
#include "DocList.h"
class TermWord{//单词
public:
	CharString Term;//单词
	int TermID;//单词ID
	int DF()const{return docList->Size();}//单词出现在多少篇文章中
	int Occur()const{return docList->Times();}//单词的总出现次数
	DocList *docList;//文档链表指针

	TermWord(CharString Term, int TermID = -1);
};

class BBST//平衡二叉搜索树
{
public:
	BBST(void);
	~BBST(void);
};

