// Project.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;
#include "CharString.h"
#include "WebsiteProcessor.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "chs");//设置为中文地区

	//以下代码实现网页解析
	CharString urlFile = "./input/url.csv";//打开存储网页url的文件
	CharString resultFile = "./output/result.csv";//打开提取信息存储的文件

	WebsiteProcessor websiteProcessor;//网页信息处理类
	websiteProcessor.initDictionary();//初始化词典
	websiteProcessor.extractInfo(urlFile, resultFile, true);//浏览整个网页，去除无用词
	
	return 0;
}

