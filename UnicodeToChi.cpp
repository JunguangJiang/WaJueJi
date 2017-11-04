#include "stdafx.h"
#include "UnicodeToChi.h"
#include "CharString.h"
using namespace std;

#define GBK_NAME ".936"


int inline stringToValue(const CharString& string){//获得一个字符串的数值大小
	int value = 0;
	for(int i=0; i<string.size(); i++){
		value *= 10;
		value += (int)string[i] - 48;
	}
	return value;
}

UnicodeToChi::UnicodeToChi(void)
{
}


UnicodeToChi::~UnicodeToChi(void)
{
}

CharString UnicodeToChi::decode(const CharString& word){//将一个词语进行解码
	
	std::wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));//解码转化器

	int value = stringToValue(word);//获得单词的数值

	wchar_t uchar = value;//将其转化为wchar_t
	wstring ustring; ustring.push_back(uchar);//转化为wstring
	wcout << ustring << endl;

	CharString string = cvtGBK.to_bytes(ustring);//最后转化为CharString
	cout << string;

	return string;
}