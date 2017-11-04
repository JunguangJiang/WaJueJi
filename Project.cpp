// Project.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;
#include <string>
#include "Stack.h"
#include "CharString.h"
#include "WebsiteProcessor.h"
#include <fstream>

#include "CharStringLink.h"
#include "Dictionary.h"

#include "UnicodeToChi.h"
/*
#include <codecvt>



#define GBK_NAME ".936"

typedef codecvt_byname<wchar_t, char, mbstate_t> WCHAR_GBK;

int inline stringToValue(const CharString& string){//���һ���ַ�������ֵ��С
	int value = 0;
	for(int i=0; i<string.size(); i++){
		value *= 10;
		value += (int)string[i] - 48;
	}
	return value;
}

CharString decode(const CharString& code){//��&#�ͱ�����н���
	int value = stringToValue(code);//�������ֵ

	wstring_convert<WCHAR_GBK> cvtGBK(new WCHAR_GBK(GBK_NAME));

	wchar_t uchar = value;
	wstring ustring; ustring.push_back(uchar);
	wcout << ustring << endl;

	CharString string = cvtGBK.to_bytes(ustring);
	cout << string;

	return string;
}
*/
int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "chs");//����Ϊ���ĵ���

	//���´���ʵ����ҳ����
	/*
	CharString urlFile = "./input/urlShort.csv";
	CharString resultFile = "./output/result.csv";//����ȡ��Ϣ�洢���ļ�

	WebsiteProcessor websiteProcessor;//��ҳ��Ϣ������
	websiteProcessor.initDictionary();//��ʼ���ʵ�
	websiteProcessor.extractInfo(urlFile, resultFile, false, true);//���������ҳ��ȥ�����ô�
	*/

	//���´��������ַ�������ļ���
	/*
	CharStringLink link;
	link.add("hello");
	link.add("world");
	link.add("hi");
	link.add("tertogl");
	link.add("13");
	link.add("chen:");
	cout << link.remove("hi");
	cout << link.remove("14");
	link.remove(0);
	cout << link.search("13");
	cout << link.search("3");
	link.print();
	*/

	//���´��������ֵ�ļ���
	/*
	Dictionary dictionary;//�½�һ���ʵ�
	dictionary.init();//�ʵ�ĳ�ʼ��

	CharString string;
	CharString inputFile = "./input/string.txt";
	ifstream in; in.open(inputFile.data());//�򿪴洢�ַ������ļ�
	if(!in){
		cout << "error in open string.txt" <<endl;
		exit(-1);
	}else{
		while(!in.eof()){
			CharString temp;
			in >> temp;
			string.concat(temp);
		}
		
	}
	in.close();

	CharStringLinkPosi link = dictionary.divideSentence(string,false);

	CharString outputFile = "./output/string.txt";
	ofstream out; out.open(outputFile.data());//�򿪴洢�ַ������ļ�
	if(!out){
		cout << "error in open string.txt" <<endl;
		exit(-1);
	}else{
		link->printReverse(out);
	}
	out.close();
	*/

	//�������ڲ�����ҳ�������ַ��Ľ���
	//CharString code = "25105";
	CharString string="25105";
	UnicodeToChi convert;
	cout << convert.decode(string);
	//cout << decode("25105");

	//wchar_t wc2 = 31616;

	//wcout<< wc2 << endl;
	return 0;
}

