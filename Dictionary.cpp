#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

Dictionary::Dictionary(int c)
{
	M = c; N = 0;//��ʼ����Ϊc����ģΪ0
	ht = new CharStringLink*[M];//����Ͱ����
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

void Dictionary::put(const char* word){//�������
	size_t  h = hashCode(word) % M;//�õ����ַ�����hash��
	ht[h]->add(word);//��hash���Ӧ���ַ�������ĩβ�������
	N++;//��ģ��һ
}

bool Dictionary::search(const char* word){//��ѯĳ�����Ƿ��ڴʵ���
	size_t h =hashCode(word) % M;//�õ����ַ�����hash��
	return (ht[h]->search(word) >= 0);//�����hash���Ӧ���ַ����������ҵ��˴���word,�򷵻�true�����򷵻�false
}

void Dictionary::init(){//�ʵ�ĳ�ʼ��
	ifstream in; 
	//in.open("./Dictionary/dictionary.dic");
	in.open("./Dictionary/professionalTerms.txt");//�򿪱��ص�һ���ļ�
	if(!in){
		cout << "error in open dictionary.txt" <<endl;
		exit(-1);
	}
	while(!in.eof()){//�����ļ��е�
		string temp;
		getline(in, temp);//ÿһ�У�����ת��Ϊ
		put(temp.c_str());//����ʵ���
		cout << temp << endl;//��ӡÿһ��������������
	}
	in.close();
}