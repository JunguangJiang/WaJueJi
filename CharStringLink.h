#pragma once
#include "CharString.h"
#include <memory>
#define StringNodePosi StringNode*
#define CharStringLinkPosi  std::shared_ptr<CharStringLink>

class StringNode{//�ַ�������ڵ�
public:
	CharString data;//������
	StringNodePosi prev;//ǰ��
	StringNodePosi succ;//���
	StringNode(const char* d = "", StringNodePosi p = NULL, 
		StringNodePosi s = NULL):prev(p), succ(s){data = d;}//�ַ����ĳ�ʼ��
	~StringNode(){prev = succ = NULL;}
};


class CharStringLink//�ַ����������ڴ洢�ִʽ������Ϊhash���е�ͰԪ��
	//���˴������ڿռ��Ͻ�һ���Ż����ĳ�ֻ��ͷ���ĵ�������
{
private:
	StringNodePosi header;//ͷ�ڵ�
	StringNodePosi tailer;//β�ڵ�
	int _size;//��ģ
public:
	int size()const {return _size;}
	CharStringLink(void);
	~CharStringLink(void);
	void add(const char* data);//���Ԫ��
	bool remove(const char* data);//ɾ��ֵΪdata��Ԫ�أ���ɾ���ɹ����򷵻�true
	bool remove(int i);//ɾ����i��Ԫ�أ�assert�� 0 <= i < size
	int search(const char* data);//����ĳ��Ԫ�ص�λ�ã���ʧ���򷵻�-1

	void print();//��ӡ���е�Ԫ�أ���������
};


