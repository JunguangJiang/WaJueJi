#pragma once

#include "CharString.h"
#include "CharStringLink.h"
#include <iostream>
#include <memory>
const int DictionaryCapacity = 10133;//�ʵ��Ĭ������������ı�ʵ��������Դ���˴���Ҫ�����޸�
const int uselessWordLinkSize = 100;//���ôʴʵ��Ĭ������

const int MaxWordLength = 16;//�涨������Ĵ��ﳤ����8������


class Dictionary//�ʵ�
{
private:
	CharStringLink** ht;//Ͱ���飬ÿһ��Ͱ���һ���ַ�������ָ��
	int M;//Ͱ��������
	int N;//��������
	void download(const char* vocabularyFile, bool isUTF8);//���ر���һ���ʿ��еĴʻ�
	CharStringLinkPosi stopLetterLink;//�洢���е����ı�����
	void initStopLetterLink();//��ʼ��ͣ�ñ�����
	bool isStopLetter(CharString word);//�ж�ĳ���ַ����Ƿ����ĵı�����
	CharStringLinkPosi *uselessWordLink;//�洢����������û������Ĵ�
	void initUselessWordLink();//��ʼ��ueslessWordLink
	bool isUselessWord(CharString word);//�ж�ĳ�����Ƿ�����
public:
	Dictionary(int c = DictionaryCapacity);//����һ��Ͱ����������С��c�Ĵʵ�
	~Dictionary(void);//�ͷ�Ͱ���鼰���и��ǿ�Ԫ����ָ��Ĵ���
	void init();//�ʵ�ĳ�ʼ����ͣ�ôʵĳ�ʼ��
	void put(const CharString& word);//�������
	bool search(const CharString& word);//��ѯĳ�����Ƿ��ڴʵ���
	void put(const char* word);//�������
	bool search(const char* word);//��ѯĳ�����Ƿ��ڴʵ���
	int size() const{return N;}//��ǰ������Ŀ

	CharStringLinkPosi dividePhrase(const CharString& phrase, bool removeUselessWord);
	//��һ��������зִʣ�����ֻ�����ģ��������Ĺؼ�����ɵ��ַ�������
	//���remvoeUseWordΪtrue����ȥ�����ô�

	CharStringLinkPosi divideSentence(const CharString& sentence, bool removeUselessWord);
	//��һ�����ӽ��зִʣ��������г��ֱ����š����֡�Ӣ���ַ���������ȡ�����Ĺؼ���
	//���remvoeUseWordΪtrue����ȥ�����ô�

	//�����������Ժ����ܷ���
	int getMaxHtSize();//���ع�ģ����Ͱ�Ĵ�С
	void print();//��ӡ�����ʵ�
};





