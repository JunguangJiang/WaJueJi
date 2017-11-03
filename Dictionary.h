#pragma once

#include "CharString.h"
#include "CharStringLink.h"
#include <iostream>
#include <memory>
const int DictionaryCapacity = 10133;//�ʵ��Ĭ������������ı�ʵ��������Դ���˴���Ҫ�����޸�

const int MaxWordLength = 16;//�涨������Ĵ��ﳤ����8������


class Dictionary//�ʵ�
{
private:
	CharStringLink** ht;//Ͱ���飬ÿһ��Ͱ���һ���ַ�������ָ��
	int M;//Ͱ��������
	int N;//��������
	void download(const char* vocabularyFile, bool isUTF8);//���ر���һ���ʿ��еĴʻ�

public:
	Dictionary(int c = DictionaryCapacity);//����һ��Ͱ����������С��c�Ĵʵ�
	~Dictionary(void);//�ͷ�Ͱ���鼰���и��ǿ�Ԫ����ָ��Ĵ���
	void init();//�ʵ�ĳ�ʼ��
	void put(const CharString& word);//�������
	bool search(const CharString& word);//��ѯĳ�����Ƿ��ڴʵ���
	void put(const char* word);//�������
	bool search(const char* word);//��ѯĳ�����Ƿ��ڴʵ���
	int size() const{return N;}//��ǰ������Ŀ

	CharStringLinkPosi dividePhrase(const CharString& phrase);
	//��һ��������зִʣ�����ֻ�����ģ��������Ĺؼ�����ɵ��ַ�������

	CharStringLinkPosi divideSentence(const CharString& sentence);
	//��һ�����ӽ��зִʣ��������г��ֱ����š����֡�Ӣ���ַ���������ȡ�����Ĺؼ���

	//�����������Ժ����ܷ���
	int getMaxHtSize();//���ع�ģ����Ͱ�Ĵ�С
	void print();//��ӡ�����ʵ�
};





