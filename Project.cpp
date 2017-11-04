// Project.cpp : 定义控制台应用程序的入口点。
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

int inline stringToValue(const CharString& string){//获得一个字符串的数值大小
	int value = 0;
	for(int i=0; i<string.size(); i++){
		value *= 10;
		value += (int)string[i] - 48;
	}
	return value;
}

CharString decode(const CharString& code){//对&#型编码进行解码
	int value = stringToValue(code);//获得其数值

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
	setlocale(LC_ALL, "chs");//设置为中文地区

	//以下代码实现网页解析
	/*
	CharString urlFile = "./input/urlShort.csv";
	CharString resultFile = "./output/result.csv";//打开提取信息存储的文件

	WebsiteProcessor websiteProcessor;//网页信息处理类
	websiteProcessor.initDictionary();//初始化词典
	websiteProcessor.extractInfo(urlFile, resultFile, false, true);//浏览整个网页，去除无用词
	*/

	//以下代码用于字符串链表的检验
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

	//以下代码用于字典的检验
	/*
	Dictionary dictionary;//新建一个词典
	dictionary.init();//词典的初始化

	CharString string;
	CharString inputFile = "./input/string.txt";
	ifstream in; in.open(inputFile.data());//打开存储字符串的文件
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
	ofstream out; out.open(outputFile.data());//打开存储字符串的文件
	if(!out){
		cout << "error in open string.txt" <<endl;
		exit(-1);
	}else{
		link->printReverse(out);
	}
	out.close();
	*/

	//以下用于测试网页上特殊字符的解码
	//CharString code = "25105";
	CharString string="25105";
	UnicodeToChi convert;
	cout << convert.decode(string);
	//cout << decode("25105");

	//wchar_t wc2 = 31616;

	//wcout<< wc2 << endl;
	return 0;
}

