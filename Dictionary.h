#pragma once

#include "CharString.h"
#include "CharStringLink.h"

const int DictionaryCapacity = 500009;//�ʵ��Ĭ������������ı�ʵ��������Դ���˴���Ҫ�����޸�

static size_t hashCode(const char* string){//�����ַ�����ѭ����λɢ����
	int h = 0;//ɢ����
	for(size_t n = strlen(string), i = 0; i < n; i++){
		h = ( h << 5 ) | ( h >> 27 ); h += (int)string[i];//ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
	}
	return (size_t) h;
}

class Dictionary//�ʵ�
{
private:
	CharStringLink** ht;//Ͱ���飬ÿһ��Ͱ���һ���ַ�������ָ��
	int M;//Ͱ��������
	int N;//��������
public:
	Dictionary(int c = DictionaryCapacity);//����һ��Ͱ����������С��c�Ĵʵ�
	~Dictionary(void);//�ͷ�Ͱ���鼰���и��ǿ�Ԫ����ָ��Ĵ���
	void init();//�ʵ�ĳ�ʼ��
	void put(const char* word);//�������
	bool search(const char* word);//��ѯĳ�����Ƿ��ڴʵ���
	int size() const{return N;}//��ǰ������Ŀ
};

