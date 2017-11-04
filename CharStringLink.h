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
	CharStringLink(void);
	~CharStringLink(void);
	CharStringLink(const CharStringLink& rhs);//�������캯��

	int size()const {return _size;}
	void add(const CharString& data);//���Ԫ��
	void remove(const CharString& data);//ɾ��ֵΪdata��Ԫ�أ���ɾ���ɹ����򷵻�true
	int search(const CharString& data);//����ĳ��Ԫ�ص�λ�ã���ʧ���򷵻�-1

	void add(const char* data);//���Ԫ��
	bool remove(const char* data);//ɾ��ֵΪdata��Ԫ�أ���ɾ���ɹ����򷵻�true
	bool remove(int i);//ɾ����i��Ԫ�أ�assert�� 0 <= i < size
	int search(const char* data);//����ĳ��Ԫ�ص�λ�ã���ʧ���򷵻�-1

	void add(CharStringLinkPosi link);//��������һ���ַ������������Ԫ��

	void print(std::ostream&);//��ӡ���е�Ԫ�أ���������
	void printReverse(std::ostream&);//�����ӡ

	friend std::ostream& operator<<(std::ostream& out, const CharStringLink& link);
};


