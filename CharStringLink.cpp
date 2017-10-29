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
	delete header; header = NULL;//Ȼ��ɾ��ͷ�ڵ�
	delete tailer; tailer = NULL;//��β�ڵ�
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
	delete node;//ɾ��
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
			delete node;//ɾ���ýڵ�
			_size--;//��ģ��һ
			return true;
		}else{
			node = node->succ; //�����������
		}
	}
	return false;//���û���ҵ���Ӧ�ڵ㣬����false
}


void CharStringLink::print(){//��ӡ���еĽڵ���������
	StringNodePosi node = header->succ; 
	while(node!=tailer){
		cout << node->data << endl;
		node = node->succ;
	}
}