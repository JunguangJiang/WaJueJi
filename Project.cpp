// Project.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
using namespace std;
#include "CharString.h"
#include "WebsiteProcessor.h"

#include "DocList.h"
#include "BBST.h"
#include "SearchEngine.h"
#include <vector>

#include "resource.h"

int _tmain(int argc, char* argv[])
{
	setlocale(LC_ALL, "chs");//����Ϊ���ĵ���

	//���´���ʵ����ҳ����
	
	//CharString urlFile = "input/url.csv";//�򿪴洢��ҳurl���ļ�
	/*
	CharString urlFile = "input/urlShort.csv";//�򿪴洢��ҳurl���ļ�
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
	
	CharString string = "||�ҵ�||���||֮��||";
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
	/*
	CharStringLink wordList;
	wordList.add(CharString("��"));
	wordList.add(CharString("����"));
	wordList.add(CharString("��"));
	wordList.add(CharString("���"));
	searchEngine.searchWordList(wordList, cout);
	*/
	/*
	CharString sentence = "����������һ̨";
	searchEngine.initDictionary();//��ʼ���ʵ�
	cout << searchEngine.divideWords(sentence, true) << endl;
	searchEngine.searchSentence(sentence, cout);
	cout << "0";
	*/
	CharString queryFile = "query.txt";
	CharString resultFile = "result.txt";
	searchEngine.initDictionary();//��ʼ���ʵ�
	searchEngine.query(queryFile, resultFile);

	
	return 0;
}

