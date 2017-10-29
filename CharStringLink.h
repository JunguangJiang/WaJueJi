#pragma once
#include "CharString.h"
#define StringNodePosi StringNode*

class StringNode{//字符串链表节点
public:
	CharString data;//数据区
	StringNodePosi prev;//前驱
	StringNodePosi succ;//后继
	StringNode(const char* d = "", StringNodePosi p = NULL, 
		StringNodePosi s = NULL):prev(p), succ(s){data = d;}//字符串的初始化
};


class CharStringLink//字符串链表，用于存储分词结果、作为hash表中的桶元素
	//（此处可以在空间上进一步优化，改成只有头结点的单向链表）
{
private:
	StringNodePosi header;//头节点
	StringNodePosi tailer;//尾节点
	int _size;//规模
public:
	CharStringLink(void);
	~CharStringLink(void);
	void add(const char* data);//添加元素
	bool remove(const char* data);//删除值为data的元素，若删除成功，则返回true
	bool remove(int i);//删除第i个元素，assert： 0 <= i < size
	int search(const char* data);//查找某个元素的位置，若失败则返回-1
	void print();//打印所有的元素，用作调试
};

