#include "stdafx.h"
#include "UnicodeToChi.h"
#include "CharString.h"
using namespace std;

#define GBK_NAME ".936"


int inline stringToValue(const CharString& string){//���һ���ַ�������ֵ��С
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

CharString UnicodeToChi::decode(const CharString& word){//��һ��������н���
	
	std::wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));//����ת����

	int value = stringToValue(word);//��õ��ʵ���ֵ

	wchar_t uchar = value;//����ת��Ϊwchar_t
	wstring ustring; ustring.push_back(uchar);//ת��Ϊwstring
	wcout << ustring << endl;

	CharString string = cvtGBK.to_bytes(ustring);//���ת��ΪCharString
	cout << string;

	return string;
}