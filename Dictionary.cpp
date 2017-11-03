#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
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
	//cout << h <<endl;
	ht[h]->add(word);//在hash码对应的字符串链表末尾加入词条
	N++;//规模加一
}

bool Dictionary::search(const char* word){//查询某个词是否在词典中
	size_t h =hashCode(word) % M;//得到该字符串的hash码
	return (ht[h]->search(word) >= 0);//如果在hash码对应的字符串链表中找到了词条word,则返回true；否则返回false
}

string UTF8ToGB(const char* str)//将utf8转化为GB编码，来源于网上 http://blog.csdn.net/zhancf/article/details/49930969
{
	 string result;
	 WCHAR *strSrc;
	 LPSTR szRes;

	 //获得临时变量的大小
	 int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	 strSrc = new WCHAR[i+1];
	 MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	 //获得临时变量的大小
	 i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	 szRes = new CHAR[i+1];
	 WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	 result = szRes;
	 delete []strSrc; strSrc = NULL;
	 delete []szRes; szRes = NULL;

	 return result;
}

void Dictionary::download(const char* vocabularyFile, bool isUTF8){//下载本地的一个词汇文件
	ifstream in; 
	in.open(vocabularyFile, ios::binary);
	if(!in){
		cout << "error in open dictionary " << vocabularyFile <<endl;
		exit(-1);
	}
		if(isUTF8){//对应utf8文件
			while(!in.eof()){//读入文件中的
			char temp[50];//每个词语
			in >> temp;
			put(UTF8ToGB(temp).c_str());//并将其加入词典中
		}
		}else{//对应gb文件
			while(!in.eof()){//读入文件中的
			string temp;//每个词语
			in >> temp;
			put(temp.c_str());//并将其加入词典中
			cout << temp << endl;
		}
	}
	in.close();
}

void Dictionary::init(){//词典的初始化
	download("./Dictionary/dictionary.dic", true);
	download("./Dictionary/professionalTerms.dic", false);
}

int Dictionary::getMaxHtSize(){
	int max=0;
	for(int i=0; i<M; i++){
		if(ht[i]->size() > max)
			max = ht[i]->size();
	}
	return max;
}

void Dictionary::print(){
	for(int i=0; i<M;i++){
		cout << "chap "<< i;
		ht[i]->print();
	}
}


CharStringLinkPosi Dictionary::divideWord(const CharString& string){
//将string按照当前加载的词库进行分词，并以字符串链表的形式返回结果
	CharStringLinkPosi link(new CharStringLink());//新建一个字符串链表
	//CharStringLinkPosi link = new CharStringLink();
	//CharStringLink link;
	
	int left, right = string.size();//子串的左右界
	while(right > 0){
		left = max(right-MaxWordLength, 0);//子串的左界
		while(left < right){
			CharString subString;//子串
			string.subString(left, right, subString);//subString = string[left, right)
			cout << subString << endl;
			if( search( subString.data() ) ){//如果subString是一个词
				link->add(subString.data());//将subString加入字符串链表
				break;
			}else{//如果subString不是一个词
				left+=2;//则左界向右移动一个汉字
			}
		}

		//Note:如果此时left==right，则内层循环中始终没有找到一个词,并且[left-2,right)并不是一个词典中的词，此处暂时将其加入链表
		//Note:如果此时left!=right,则找到了词[left,right)
		if(left == right){
			CharString subString;//子串
			string.subString(left-2, right, subString);//subString = string[left-2, right)
			link->add(subString.data());
			cout << subString << endl;

			right = left-2;
		}else{
			right = left;
		}
	}
	return link;
}