#include "stdafx.h"
#include "CharString.h"
using namespace std;

inline int max(int a, int b){//返回整数的最大值
	return (a<b)?b:a;
}

CharString::CharString(int capacity)://字符串的初始化
	_capacity(capacity), _size(0)
{
	_elem = new char[_capacity];
}

CharString::CharString(const std::string& s){//用一个string去初始化CharString
	_capacity = max(s.size(), minStringSize);
	_elem = new char[_capacity];
	for(int i=0; i<s.size(); i++){
		_elem[i] = s[i];
	}
	_size = s.size();
}

CharString::~CharString(void){//析构函数
	delete [] _elem;
}

void CharString::expand(){//扩容
	if(_size < _capacity) return;//尚未满员时不必扩容
	_capacity <<= 1;//容量加倍
	char* oldElem = _elem;//开辟一个新的空间
	_elem = new char[_capacity];
	for(int i=0; i<_size; i++){
		_elem[i] = oldElem[i];//复制数据元素
	}
	delete [] oldElem;//删除原来的空间
}

void CharString::insert(char c){//在字符串末尾插入字符c
	expand();
	_elem[_size++] = c;
}

int* buildNext(const CharString& subString){//生成子串subString对应的next表
	int* next = new int[subString.size()];
	int t = next[0] = -1; int i=0;
	while(i<subString.size()-1){
		if(t < 0 || subString[i] == subString[t]){//匹配
			t++; i++;
			next[i] = (subString[i] != subString[t])? t : next[t];
		}else{//失配
			t = next[t];
		}
	}
	return next;
}

int CharString::indexOf(const CharString& subString, const int pos)const{
	//在目标字符串中,从pos的位置开始查找子串,
	//并返回子串第一次出现的位置。如果不存在子串,那么返回-1。

	int i=pos, j=0;
	int* next = buildNext(subString);//得到next
	while(i<_size && j<subString.size()){
		if(j==-1 || _elem[i] == subString[j]){
			j++; i++;
		}else{
			j = next[j];
		}
	}
	delete [] next;
	if(j == subString.size())//若匹配成功
		return i-j;//返回匹配成功的位置
	else//匹配失败
		return -1;
}

int CharString::indexOf(const char* subString, const int pos)const{
	CharString sub(subString);
	return indexOf(sub, pos);
}


bool CharString::subString(int left, int right, CharString& sub)const{//将原字符串[left,right)的子串的拷贝到sub中
	sub._size = 0;
	for(int i=left; i<right; i++){
		sub.insert(_elem[i]);
	}
	return true;
}

void CharString::concat(const CharString& string){//将string接到当前字符串的末尾
	for(int i=0; i<string.size(); i++){
		insert(string[i]);
	}
}

CharString& CharString::operator=(const CharString& string){//将string赋值给当前字符串
	_size = 0;
	for(int i=0; i<string.size(); i++){
		insert(string[i]);
	}
	return *(this);
}

CharString& CharString::operator=(const std::string& s){//用stl中的string赋给当前字符串
	_size = 0;
	for(int i=0; i<s.size(); i++){
		insert(s[i]);		
	}
	return *(this);
}

std::ostream& operator <<(std::ostream& out, CharString& string){//重载输出流
	for(int i=0; i<string.size(); i++){
		out << string[i];
	}
	return out;
}

char* CharString::data() const{//返回当前字符串存储的字符数组
	char* data = new char[_size+1];
	for(int i=0; i<_size; i++){
		data[i] = _elem[i];
	}
	data[_size] = '\0';
	return data;
}

bool CharString::operator==(const char* string){//判等，判断当前字符串是否和另外一个字符数组string相等
	int m = strlen(string);
	if(_size != m)//如果大小都不相等
		return false;//那么肯定不相等
	
	for(int i=0; i<m; i++){//假如
		if(_elem[i] != string[i])//每个字符都相等
			return false;
	}
	return true;//则两个字符串相等
}
