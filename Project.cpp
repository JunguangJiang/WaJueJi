// Project.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;
#include "CharString.h"
#include "WebsiteProcessor.h"

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "chs");//����Ϊ���ĵ���

	//���´���ʵ����ҳ����
	CharString urlFile = "./input/url.csv";//�򿪴洢��ҳurl���ļ�
	CharString resultFile = "./output/result.csv";//����ȡ��Ϣ�洢���ļ�

	WebsiteProcessor websiteProcessor;//��ҳ��Ϣ������
	websiteProcessor.initDictionary();//��ʼ���ʵ�
	websiteProcessor.extractInfo(urlFile, resultFile, true);//���������ҳ��ȥ�����ô�
	
	return 0;
}

