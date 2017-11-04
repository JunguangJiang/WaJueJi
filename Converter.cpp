#include "stdafx.h"
#include "Converter.h"
using namespace std;

int inline stringToValue(const CharString& string){//���һ���ַ�������ֵ��С
	int value = 0;
	for(int i=0; i<string.size(); i++){
		value *= 10;
		value += (int)string[i] - 48;
	}
	return value;
}

CharString UnicodeToChinese(const CharString& sentence){//��Unicode����ת��Ϊ����
	typedef std::codecvt_byname<wchar_t, char, mbstate_t> WCHAR_GBK;
	const char* GBK_NAME = ".936";
	std::wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));//����ת����
	CharString result;//���ص������ַ���
	int left=-1, right=-1;
	while(true){//��ԭ����unicode�ַ�����
		left = sentence.indexOf("&#", left+1);//�ҵ�����"&#25105;"���Ӵ��Ŀ�ͷ
		if(left >= 0){
			if( (right+1) < left ){//���[right+1, left)֮����ڷ�unicode�ַ���
				result.concat( sentence.subString(right+1, left) );//����ֱ�Ӽ��뵽����ַ�����
			}
			right = sentence.indexOf(";", right+1);//�ҵ�����"&#25105;"���Ӵ��Ľ�β

			CharString word = sentence.subString(left+2, right);//ȡ�����е����ֲ���25105
			int value = stringToValue(word);//������Ӧ����ֵ
			wchar_t uchar = value;//����ת��Ϊwchar_t
			wstring ustring; ustring.push_back(uchar);//ת��Ϊustring
			result.concat( cvtGBK.to_bytes(ustring) );//���ustringת��ΪCharString�����뵽����������ַ�����	
		}else{//����Ҳ��������Ĵ���
			if(right < sentence.size()-1){//˵����β�з�unicode�ַ���
				result.concat(sentence.subString(right+1, sentence.size()));
			}
			break;//������˳���
		}
	}

	return result;
}