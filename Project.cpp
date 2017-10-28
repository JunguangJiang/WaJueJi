// Project.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
using namespace std;

#include "Stack.h"
#include "CharString.h"
#include "WebsiteProcessor.h"


int _tmain(int argc, _TCHAR* argv[])
{
	
	CharString string; string = "http://bbs.cehome.com/thread-614565-1-1.html";

	WebsiteProcessor websiteProcessor;
	CharString filename;
	websiteProcessor.downloadWebsite(string, filename);

	return 0;
}

