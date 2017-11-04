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

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "chs");//设置为中文地区

	//以下代码实现网页解析
	
	CharString urlFile = "./input/url.csv";
	ifstream in; in.open(urlFile.data());//打开存储网页url的文件
	if(!in){
		cout << "error in open url.csv" <<endl;
		exit(-1);
	}
	CharString resultFile = "./output/result.csv";//打开提取信息存储的文件
	ofstream out; out.open(resultFile.data());
	if(!out){
		cout << "error in open result.csv" <<endl;
		exit(-1);
	}
	WebsiteProcessor websiteProcessor;//网页信息处理类
	websiteProcessor.process(in, out);//进行处理
	in.close(); out.close();//关闭打开的文件
	
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
	return 0;
}

