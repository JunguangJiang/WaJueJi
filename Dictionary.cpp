#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Dictionary::Dictionary(int c)
{
	M = c; N = 0;//初始容量为c，规模为0
	ht = new CharStringLink*[M];//开辟桶数组
	for(int i=0; i<M; i++)
		ht[i] = new CharStringLink();
}


Dictionary::~Dictionary(void)
{
	for(int i=0; i<M; i++){
		delete ht[i]; ht[i] = NULL;
	}
	delete [] ht; ht = NULL;
}

void Dictionary::put(const char* word){//插入词条
	size_t  h = hashCode(word) % M;//得到该字符串的hash码
	ht[h]->add(word);//在hash码对应的字符串链表末尾加入词条
	N++;//规模加一
}

bool Dictionary::search(const char* word){//查询某个词是否在词典中
	size_t h =hashCode(word) % M;//得到该字符串的hash码
	return (ht[h]->search(word) >= 0);//如果在hash码对应的字符串链表中找到了词条word,则返回true；否则返回false
}

void Dictionary::init(){//词典的初始化
	ifstream in; 
	//in.open("./Dictionary/dictionary.dic");
	in.open("./Dictionary/professionalTerms.txt");//打开本地的一个文件
	if(!in){
		cout << "error in open dictionary.txt" <<endl;
		exit(-1);
	}
	while(!in.eof()){//读入文件中的
		string temp;
		getline(in, temp);//每一行，将其转化为
		put(temp.c_str());//加入词典中
		cout << temp << endl;//打印每一个词条，作调试
	}
	in.close();
}