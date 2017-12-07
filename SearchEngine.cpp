#include "stdafx.h"
#include "SearchEngine.h"
#include "DocList.h"
#include <fstream>
using namespace std;
SearchEngine::SearchEngine(void)
{
	bbst = new BBST();
}


SearchEngine::~SearchEngine(void)
{
}

void SearchEngine::buildInvertedFile(const CharString& infile, const CharString& outfile){//�ӱ����ļ���ȡ��Ϣ�����������ĵ�
	ifstream in;
	in.open(infile.data());
	if(!in){
		cout << "error in open inverted file "<< infile << endl;
		exit(-1);
	}
	ofstream out;
	out.open(outfile.data());
	if(!out){
		cout << "error in open inverted file "<< outfile << endl;
		exit(-1);
	}
	string line; getline(in, line);//����ĵ�һ����������
	int DocID = 0;//�ĵ����
	vector<CharString> content;//�洢���еķ�������
	while(!in.eof()){//һֱ���뵽�ļ���ĩβ
		getline(in, line);CharString string(line); //���ļ��ж���һ��
		DocID++;//�ĵ���ŵ���
		vector<CharString> v = string.split(CharString("||"));//��һ�е��ַ����зֳɶ���Ӵ�
		if(v.size()<9) continue;//���������Ϣ������������������
		content.push_back(v[5]);//�õ���������
		vector<CharString> dividedWordList = v[9].split(CharString(" "));//�õ��ִʽ��
		for(int i=0; i<dividedWordList.size(); i++){//�������еķִʽ��
			CharString word = dividedWordList[i];//��i���ִ�
			if(word.size() == 0) continue;//�������пմ�
			BinNodePosi p = bbst->Insert(word);//���۲����Ƿ�ɹ������صĽڵ�p��Ӧ�ĵ��ʶ���word
			/*
			if(p) 
				cout << " Debug p : " << p->Term;
			else
				cout << "Debug : " << "Fail to insert "<<word ;
			cout << endl;
			*/
			p->docList->Add(DocID);//�򵥴ʵ��ĵ������м��뵱ǰ�ĵ��ı��
			/*
			cout << "----------------------"<<endl;
			cout << "Inserting " << word << endl;
			bbst->debug(bbst->root());//��ӡ������
			cout << "----------------------"<<endl;
			*/
		}
	}
	out << DocID << endl;//����ĵ�������
	for(int i = 0; i<content.size(); i++){
		out << content[i] << endl;//������еķ�������
	}
	bbst->debug(bbst->root());//��ӡ������
}

void SearchEngine::searchWordList(vector<CharString> wordList, ostream& out){
	DocList list;
	for(int i=0; i<wordList.size(); i++){
		
	}
}