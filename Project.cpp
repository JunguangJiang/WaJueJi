// Project.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;
#include "CharString.h"
#include "WebsiteProcessor.h"

#include "DocList.h"

int _tmain(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");//����Ϊ���ĵ���

	//���´���ʵ����ҳ����
	/*
	CharString urlFile = "input/url.csv";//�򿪴洢��ҳurl���ļ�
	CharString resultFile = "output/result.csv";//����ȡ��Ϣ�洢���ļ�
	WebsiteProcessor websiteProcessor;//��ҳ��Ϣ������
	websiteProcessor.initDictionary();//��ʼ���ʵ�
	websiteProcessor.extractInfo(urlFile, resultFile, true);//���������ҳ��ȥ�����ô�
	*/

	/*
	DocList list;
	list.Add(3,199);
	list.Add(4,34);
	list.Add(5,98);
	list.Add(6, 150);
	list.Add(3,199);
	list.Edit(6, 11);
	list.print();
	cout << "0";
	*/
	CharString s1 = "Hello"; CharString s2 = "Hello";
	cout << (s1 > s2) << endl;
	cout << "END";
	return 0;
}

