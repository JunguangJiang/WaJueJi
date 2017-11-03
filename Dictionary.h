#pragma once

#include "CharString.h"
#include "CharStringLink.h"
#include <iostream>
#include <memory>
const int DictionaryCapacity = 10133;//词典的默认容量，如果改变词典的数据来源，此处需要进行修改

const int MaxWordLength = 16;//规定最长的中文词语长度是8个汉字


class Dictionary//词典
{
private:
	CharStringLink** ht;//桶数组，每一个桶存放一个字符串链表指针
	int M;//桶数组容量
	int N;//词条数量
	void download(const char* vocabularyFile, bool isUTF8);//下载本地一个词库中的词汇

public:
	Dictionary(int c = DictionaryCapacity);//创建一个桶数组容量不小于c的词典
	~Dictionary(void);//释放桶数组及其中各非空元素所指向的词条
	void init();//词典的初始化
	void put(const CharString& word);//插入词条
	bool search(const CharString& word);//查询某个词是否在词典中
	void put(const char* word);//插入词条
	bool search(const char* word);//查询某个词是否在词典中
	int size() const{return N;}//当前词条数目

	CharStringLinkPosi dividePhrase(const CharString& phrase);
	//对一个短语进行分词，其中只有中文，返回中文关键词组成的字符串链表

	CharStringLinkPosi divideSentence(const CharString& sentence);
	//对一个句子进行分词，允许其中出现标点符号、数字、英文字符，从中提取出中文关键词

	//以下用作调试和性能分析
	int getMaxHtSize();//返回规模最大的桶的大小
	void print();//打印整个词典
};





