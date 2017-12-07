#include "stdafx.h"
#include "CharString.h"
#include <string>
#include <fstream>
using namespace std;

inline int max(int a, int b){//�������������ֵ
	return (a<b)?b:a;
}

inline int min(int a, int b){//������������Сֵ
	return (a<b)?a:b;
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

CharString::CharString(const CharString& rhs){//�������캯��
	_capacity = max(rhs.size(), minStringSize);
	_elem = new char[_capacity];
	for(int i=0; i<rhs.size(); i++){
		_elem[i] = rhs[i];
	}
	_size = rhs.size();
}

CharString::~CharString(void){//��������
	if(_elem){
		delete [] _elem;
		_elem = NULL;
	}
}

void CharString::expand(){//����
	if(_size < _capacity) return;//��δ��Աʱ��������
	_capacity <<= 1;//�����ӱ�
	char* oldElem = _elem;//����һ���µĿռ�
	_elem = new char[_capacity];
	for(int i=0; i<_size; i++){
		_elem[i] = oldElem[i];//��������Ԫ��
	}
	delete [] oldElem; oldElem = NULL;//ɾ��ԭ���Ŀռ�
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
	delete [] next; next = NULL;
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

CharString CharString::subString(int left, int right)const{
	CharString sub;
	subString(left, right, sub);
	return sub;
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

std::ostream& operator <<(std::ostream& out, const CharString& string){//���������
	for(int i=0; i<string.size(); i++){
		out << string[i];
	}
	return out;
}

std::ifstream& operator>>(std::ifstream& in, CharString& string){//�����ļ�������
	string._size = 0;
	std::string temp;
	in >> temp;
	string = temp;
	return in;
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

bool CharString::operator==(const CharString& string){//�еȣ��жϵ�ǰ�ַ����Ƿ������һ���ַ���string���
	if(_size != string.size())//�����С�������
		return false;//��ô�϶������

	for(int i=0; i<_size; i++){//����
		if(_elem[i] != string[i])//ÿ���ַ������
			return false;
	}
	return true;//�������ַ������
}

void CharString::remove(int i){//ɾ����i���ַ�
	//Note:0<= i < size
	for(int j = i; j<size()-1; j++){
		_elem[j] = _elem[j+1];
	}
	_size--;
}

void CharString::removeSpace(){//ɾ���ַ����е����пո�
	for(int i=0; i<size();){
		if(_elem[i] == ' ' || _elem[i] == '\n'){
			remove(i);
		}else{
			i++;
		}
	}
}


//����ʵ�������ַ����Ĵ�С�Ƚϣ���λ�Ƚ��ַ���ASCII�룬��ǰ׺��ͬ���򳤶Ƚϳ��߽ϴ�
bool CharString::operator<(const CharString& string){
	int i=0;
	while( i<_size && i<string.size() ){//�ӵ�λ��ʼ�Ƚ������ַ���ASCII���С
		if( _elem[i] < string[i] )
			return true;
		else if( _elem[i] > string[i] )
			return false;
		else
			i++;
	}//������ߵ�ǰ׺��ͬ
	return _size < string.size();//���ж϶��ߵĳ���
}
	
bool CharString::operator<=(const CharString& string){
	return ~(*this > string);
}

bool CharString::operator>=(const CharString& string){
	return ~(*this < string);
}
	
bool CharString::operator>(const CharString& string){
	int i=0;
	while( i<_size && i<string.size() ){//�ӵ�λ��ʼ�Ƚ������ַ���ASCII���С
		if( _elem[i] > string[i] )
			return true;
		else if( _elem[i] < string[i] )
			return false;
		else
			i++;
	}//������ߵ�ǰ׺��ͬ
	return _size > string.size();//���ж϶��ߵĳ���
}

vector<CharString> CharString::split(const CharString& c) const{
	int i = 0, j = 0;
	vector<CharString> result;
	j = indexOf(c, i);
	while(j>=0){
		result.push_back(subString(i,j));//[i,j)Ϊһ���µ��Ӵ�
		i = j+c.size(); j = indexOf(c, i);
	}
	result.push_back(subString(i, size()));
	return result;
}
