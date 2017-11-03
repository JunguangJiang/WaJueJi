#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
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
	//cout << h <<endl;
	ht[h]->add(word);//��hash���Ӧ���ַ�������ĩβ�������
	N++;//��ģ��һ
}

bool Dictionary::search(const char* word){//��ѯĳ�����Ƿ��ڴʵ���
	size_t h =hashCode(word) % M;//�õ����ַ�����hash��
	return (ht[h]->search(word) >= 0);//�����hash���Ӧ���ַ����������ҵ��˴���word,�򷵻�true�����򷵻�false
}

string UTF8ToGB(const char* str)//��utf8ת��ΪGB���룬��Դ������ http://blog.csdn.net/zhancf/article/details/49930969
{
	 string result;
	 WCHAR *strSrc;
	 LPSTR szRes;

	 //�����ʱ�����Ĵ�С
	 int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	 strSrc = new WCHAR[i+1];
	 MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	 //�����ʱ�����Ĵ�С
	 i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	 szRes = new CHAR[i+1];
	 WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	 result = szRes;
	 delete []strSrc; strSrc = NULL;
	 delete []szRes; szRes = NULL;

	 return result;
}

void Dictionary::download(const char* vocabularyFile, bool isUTF8){//���ر��ص�һ���ʻ��ļ�
	ifstream in; 
	in.open(vocabularyFile, ios::binary);
	if(!in){
		cout << "error in open dictionary " << vocabularyFile <<endl;
		exit(-1);
	}
		if(isUTF8){//��Ӧutf8�ļ�
			while(!in.eof()){//�����ļ��е�
			char temp[50];//ÿ������
			in >> temp;
			put(UTF8ToGB(temp).c_str());//���������ʵ���
		}
		}else{//��Ӧgb�ļ�
			while(!in.eof()){//�����ļ��е�
			string temp;//ÿ������
			in >> temp;
			put(temp.c_str());//���������ʵ���
			cout << temp << endl;
		}
	}
	in.close();
}

void Dictionary::init(){//�ʵ�ĳ�ʼ��
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
//��string���յ�ǰ���صĴʿ���зִʣ������ַ����������ʽ���ؽ��
	CharStringLinkPosi link(new CharStringLink());//�½�һ���ַ�������
	//CharStringLinkPosi link = new CharStringLink();
	//CharStringLink link;
	
	int left, right = string.size();//�Ӵ������ҽ�
	while(right > 0){
		left = max(right-MaxWordLength, 0);//�Ӵ������
		while(left < right){
			CharString subString;//�Ӵ�
			string.subString(left, right, subString);//subString = string[left, right)
			cout << subString << endl;
			if( search( subString.data() ) ){//���subString��һ����
				link->add(subString.data());//��subString�����ַ�������
				break;
			}else{//���subString����һ����
				left+=2;//����������ƶ�һ������
			}
		}

		//Note:�����ʱleft==right�����ڲ�ѭ����ʼ��û���ҵ�һ����,����[left-2,right)������һ���ʵ��еĴʣ��˴���ʱ�����������
		//Note:�����ʱleft!=right,���ҵ��˴�[left,right)
		if(left == right){
			CharString subString;//�Ӵ�
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