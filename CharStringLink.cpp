#include "stdafx.h"
#include "CharStringLink.h"
#include <iostream>
using namespace std;

CharStringLink::CharStringLink(void)
{
	header = new StringNode();
	tailer = new StringNode();
	header->succ = tailer;//��ʼ��ʱͷ��
	tailer->prev = header;//β�ڵ�����
	_size = 0;//��ʼ��ģΪ0
}


CharStringLink::~CharStringLink(void)
{
	while(_size>0){//ɾ�����еĽڵ�
		remove(0);//ֱ����ģΪ0
	}
	if(header){
		header->succ = NULL; 
		delete header; 
		header = NULL;//Ȼ��ɾ��ͷ�ڵ�
	}
	if(tailer){
		tailer->prev = NULL; 
		delete tailer;
		tailer = NULL;//��β�ڵ�
	}
}

CharStringLink::CharStringLink(const CharStringLink& rhs){//�������캯��
	header = new StringNode();
	tailer = new StringNode();
	header->succ = tailer;//��ʼ��ʱͷ��
	tailer->prev = header;//β�ڵ�����
	_size = 0;//��ʼ��ģΪ0
	
	StringNodePosi node = rhs.header->succ;
	while(node != rhs.tailer){
		add(node->data);
		node = node->succ;
	}
}

void CharStringLink::add(const CharString& data){//���Ԫ��
	add(data.data());
}
void CharStringLink::remove(const CharString& data){//ɾ��ֵΪdata��Ԫ�أ���ɾ���ɹ����򷵻�true
	remove(data.data());	
}

int CharStringLink::search(const CharString& data){//����ĳ��Ԫ�ص�λ�ã���ʧ���򷵻�-1
	return search(data.data());
}

void CharStringLink::add(const char* data){//����dataԪ��
	StringNodePosi node = new StringNode(data);//����һ���µĽڵ�
	node->prev = tailer->prev; node->succ = tailer;//���������ĩ�ڵ�֮��
	tailer->prev->succ = node; tailer->prev = node;//β�ڵ�֮ǰ
	_size++;//��ģ��1
}

bool CharStringLink::remove(int i){//ɾ����i��Ԫ�أ�assert�� 0 <= i < size
	if(i<0 || i>=_size)//�ų��Ƿ������
		return false;

	StringNodePosi node = header->succ;
	while(i--){
		node = node->succ;//�ҵ���i��Ԫ��
	}
	node->prev->succ = node->succ;
	node->succ->prev = node->prev;//����ǰ���ͺ������
	node->prev = NULL; node->succ = NULL;//����Ԫ��
	delete node; node = NULL;//ɾ��
	_size--;//��ģ��һ
	return true;
}

int CharStringLink::search(const char* data){//����ĳ��Ԫ�ص�λ�ã���ʧ���򷵻�-1
	StringNodePosi node = header->succ; int i = 0;//���׽ڵ㿪ʼ����
	while(node!=tailer){
		if(node->data == data){//���ĳ���ڵ��ֵ��Ϊdata
			return i;//���ظ�Ԫ�ص�λ��
		}else{
			node = node->succ; i++;//�����������
		}
	}
	return -1;//����û���ҵ�������-1
}

bool CharStringLink::remove(const char* data){//ɾ��ֵΪdata��Ԫ�أ���ɾ���ɹ����򷵻�true
	StringNodePosi node = header->succ;//���׽ڵ㿪ʼ����
	while(node!=tailer){
		if(node->data == data){//���ĳ���ڵ��ֵ��Ϊdata
			node->prev->succ = node->succ;
			node->succ->prev = node->prev;
			node->prev = NULL;
			node->succ = NULL;
			delete node; node = NULL;//ɾ���ýڵ�
			_size--;//��ģ��һ
			return true;
		}else{
			node = node->succ; //�����������
		}
	}
	return false;//���û���ҵ���Ӧ�ڵ㣬����false
}


void CharStringLink::print(ostream& out){//��ӡ���еĽڵ���������
	StringNodePosi node = header->succ; 
	while(node!=tailer){
		out << node->data << " | ";
		node = node->succ;
	}
	out << endl;
}

void CharStringLink::printReverse(ostream& out){
	StringNodePosi node = tailer->prev; 
	while(node!=header){
		out << node->data << " | ";
		node = node->prev;
	}
	out << endl;
}

void CharStringLink::add(CharStringLinkPosi link){//��������һ���ַ������������Ԫ��
	StringNodePosi node = link->header->succ;
	while(node != link->tailer){
		add(node->data);
		node = node->succ;
	}
}

ostream& operator<<(ostream& out, const CharStringLink& link){
	StringNodePosi node = link.tailer->prev;
	while(node != link.header ){
		out << node->data << " ";
		node = node->prev;//�������
	}
	return out;
}
