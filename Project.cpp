// Project.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;
#include "CharString.h"
#include "WebsiteProcessor.h"

#include "DocList.h"
#include "BBST.h"
#include "SearchEngine.h"
#include <vector>
int _tmain(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");//设置为中文地区

	//以下代码实现网页解析
	
	//CharString urlFile = "input/url.csv";//打开存储网页url的文件
	/*
	CharString urlFile = "input/urlShort.csv";//打开存储网页url的文件
	CharString resultFile = "output/result.csv";//打开提取信息存储的文件
	WebsiteProcessor websiteProcessor;//网页信息处理类
	websiteProcessor.initDictionary();//初始化词典
	websiteProcessor.extractInfo(urlFile, resultFile, true);//浏览整个网页，去除无用词
	*/

	/*
	DocList list;
	list.Add(3,199);
	list.Add(4,34);
	list.Add(5,98);
	list.Add(6, 150);
	list.Add(3,199);
	list.Edit(6, 11);
	cout << list.Remove(4)<<endl;
	list.Add(9, 500);
	list.Edit(9, 90);
	list.debug();
	cout << list.Remove(3)<<endl;
	cout << "0";
	*/
	/*
	DocList list;
	list.Add(1);
	list.Add(3);
	list.Add(4);
	list.Add(5);
	list.Add(6);
	list.Add(3);
	list.Add(6);
	list.Add(3);
	//list.Edit(6, 11);
	
	CharString s[10] = {
		"Hello", "Hello", "Hi", "OK", "ON", "OOO",
		"ABC","DEF", "BTree", "BT"};
	
	CharString string = "||我的||天空||之城||";
	vector<CharString> v =  string.split(CharString("||"));
	for(int i=0; i<v.size(); i++){
		cout << v[i] <<endl;
	}
	*/
	/*
	BBST bbst;
	for(int i=0; i<10; i++){
		bbst.Insert(s[i]);
		cout << "--------------------" <<endl;
		cout << "inserting "<<s[i]<<endl;
		bbst.debug(bbst.root());
	}
	for(int i=0; i<10; i++){
		bbst.Remove(s[i]);
		cout << "--------------------" <<endl;
		cout << "removing "<<s[i]<<endl;
		bbst.debug(bbst.root());
	}
	*/
	
	SearchEngine searchEngine;
	searchEngine.buildInvertedFile(CharString("output/result.csv"), CharString("output/invertedFile.txt"));
	
	cout << "0";
	return 0;
}

