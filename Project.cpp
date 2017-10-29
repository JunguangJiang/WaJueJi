// Project.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

#include "Stack.h"
#include "CharString.h"
#include "WebsiteProcessor.h"
#include <fstream>

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	CharString string; string = "http://bbs.cehome.com/thread-614006-1-1.html";

	WebsiteProcessor websiteProcessor;
	CharString filename;
	filename = "./input/temp.txt";
	websiteProcessor.downloadWebsite(string, filename);
	ofstream out("./input/save.txt");
	websiteProcessor.processHtml(filename, out);
	*/
	CharString urlFile = "./input/url.csv";
	ifstream in; in.open(urlFile.data());
	if(!in){
		cout << "error in open url.csv" <<endl;
		exit(-1);
	}
	CharString resultFile = "./output/result.csv";
	ofstream out; out.open(resultFile.data());
	if(!out){
		cout << "error in open result.csv" <<endl;
		exit(-1);
	}
	WebsiteProcessor websiteProcessor;
	websiteProcessor.process(in, out);
	return 0;
}

