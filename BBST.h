#pragma once

#include "CharString.h"
#include "DocList.h"
class TermWord{//����
public:
	CharString Term;//����
	int TermID;//����ID
	int DF()const{return docList->Size();}//���ʳ����ڶ���ƪ������
	int Occur()const{return docList->Times();}//���ʵ��ܳ��ִ���
	DocList *docList;//�ĵ�����ָ��

	TermWord(CharString Term, int TermID = -1);
};

class BBST//ƽ�����������
{
public:
	BBST(void);
	~BBST(void);
};

