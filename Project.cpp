// Project.cpp : �������̨Ӧ�ó������ڵ㡣
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
	
	CharString string; string = "http://bbs.cehome.com/thread-614565-1-1.html";

	WebsiteProcessor websiteProcessor;
	CharString filename;
	//websiteProcessor.downloadWebsite(string, filename);
	filename = "temp.txt";
	ofstream out("save.txt");
	websiteProcessor.processHtml(filename, out);
	return 0;
}

