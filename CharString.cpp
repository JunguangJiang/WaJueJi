#include "stdafx.h"
#include "CharString.h"
using namespace std;

inline int max(int a, int b){//�������������ֵ
	return (a<b)?b:a;
}

CharString::CharString(int capacity)://�ַ����ĳ�ʼ��
	_capacity(capacity), _size(0)
{
	_elem = new char[_capacity];
}

CharString::CharString(const std::string& s){//��һ��stringȥ��ʼ��CharString
	_capacity = max(s.size(), minStringSize);
	_elem = new char[_capacity];
	for(int i=0; i<s.size(); i++){
		_elem[i] = s[i];
	}
	_size = s.size();
}

CharString::~CharString(void){//��������
	delete [] _elem;
}

void CharString::expand(){//����
	if(_size < _capacity) return;//��δ��Աʱ��������
	_capacity <<= 1;//�����ӱ�
	char* oldElem = _elem;//����һ���µĿռ�
	_elem = new char[_capacity];
	for(int i=0; i<_size; i++){
		_elem[i] = oldElem[i];//��������Ԫ��
	}
	delete [] oldElem;//ɾ��ԭ���Ŀռ�
}

void CharString::insert(char c){//���ַ���ĩβ�����ַ�c
	expand();
	_elem[_size++] = c;
}

int* buildNext(const CharString& subString){//�����Ӵ�subString��Ӧ��next��
	int* next = new int[subString.size()];
	int t = next[0] = -1; int i=0;
	while(i<subString.size()-1){
		if(t < 0 || subString[i] == subString[t]){//ƥ��
			t++; i++;
			next[i] = (subString[i] != subString[t])? t : next[t];
		}else{//ʧ��
			t = next[t];
		}
	}
	return next;
}

int CharString::indexOf(const CharString& subString, const int pos)const{
	//��Ŀ���ַ�����,��pos��λ�ÿ�ʼ�����Ӵ�,
	//�������Ӵ���һ�γ��ֵ�λ�á�����������Ӵ�,��ô����-1��

	int i=pos, j=0;
	int* next = buildNext(subString);//�õ�next
	while(i<_size && j<subString.size()){
		if(j==-1 || _elem[i] == subString[j]){
			j++; i++;
		}else{
			j = next[j];
		}
	}
	delete [] next;
	if(j == subString.size())//��ƥ��ɹ�
		return i-j;//����ƥ��ɹ���λ��
	else//ƥ��ʧ��
		return -1;
}

int CharString::indexOf(const char* subString, const int pos)const{
	CharString sub(subString);
	return indexOf(sub, pos);
}


bool CharString::subString(int left, int right, CharString& sub)const{//��ԭ�ַ���[left,right)���Ӵ��Ŀ�����sub��
	sub._size = 0;
	for(int i=left; i<right; i++){
		sub.insert(_elem[i]);
	}
	return true;
}

void CharString::concat(const CharString& string){//��string�ӵ���ǰ�ַ�����ĩβ
	for(int i=0; i<string.size(); i++){
		insert(string[i]);
	}
}

CharString& CharString::operator=(const CharString& string){//��string��ֵ����ǰ�ַ���
	_size = 0;
	for(int i=0; i<string.size(); i++){
		insert(string[i]);
	}
	return *(this);
}

CharString& CharString::operator=(const std::string& s){//��stl�е�string������ǰ�ַ���
	_size = 0;
	for(int i=0; i<s.size(); i++){
		insert(s[i]);		
	}
	return *(this);
}

std::ostream& operator <<(std::ostream& out, CharString& string){//���������
	for(int i=0; i<string.size(); i++){
		out << string[i];
	}
	return out;
}

char* CharString::data() const{//���ص�ǰ�ַ����洢���ַ�����
	char* data = new char[_size+1];
	for(int i=0; i<_size; i++){
		data[i] = _elem[i];
	}
	data[_size] = '\0';
	return data;
}

bool CharString::operator==(const char* string){//�еȣ��жϵ�ǰ�ַ����Ƿ������һ���ַ�����string���
	int m = strlen(string);
	if(_size != m)//�����С�������
		return false;//��ô�϶������
	
	for(int i=0; i<m; i++){//����
		if(_elem[i] != string[i])//ÿ���ַ������
			return false;
	}
	return true;//�������ַ������
}
