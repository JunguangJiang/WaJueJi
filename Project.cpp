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

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_ALL, "chs");//����Ϊ���ĵ���

	//���´���ʵ����ҳ����
	
	CharString urlFile = "./input/url.csv";
	ifstream in; in.open(urlFile.data());//�򿪴洢��ҳurl���ļ�
	if(!in){
		cout << "error in open url.csv" <<endl;
		exit(-1);
	}
	CharString resultFile = "./output/result.csv";//����ȡ��Ϣ�洢���ļ�
	ofstream out; out.open(resultFile.data());
	if(!out){
		cout << "error in open result.csv" <<endl;
		exit(-1);
	}
	WebsiteProcessor websiteProcessor;//��ҳ��Ϣ������
	websiteProcessor.process(in, out);//���д���
	in.close(); out.close();//�رմ򿪵��ļ�
	
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
	return 0;
}

