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

void SearchEngine::buildInvertedFile(const CharString& infile, const CharString& outfile){//从本地文件读取信息，构建倒排文档
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
	string line; getline(in, line);//读入的第一行内容无用
	int DocID = 0;//文档编号
	vector<CharString> content;//存储所有的发帖内容
	while(!in.eof()){//一直输入到文件的末尾
		getline(in, line);CharString string(line); //从文件中读入一行
		DocID++;//文档编号递增
		vector<CharString> v = string.split(CharString("||"));//将一行的字符串切分成多个子串
		if(v.size()<9) continue;//如果该行信息不完整，则跳过该行
		content.push_back(v[5]);//得到发帖内容
		vector<CharString> dividedWordList = v[9].split(CharString(" "));//得到分词结果
		for(int i=0; i<dividedWordList.size(); i++){//遍历所有的分词结果
			CharString word = dividedWordList[i];//第i个分词
			if(word.size() == 0) continue;//跳过所有空词
			BinNodePosi p = bbst->Insert(word);//无论插入是否成功，返回的节点p对应的单词都是word
			/*
			if(p) 
				cout << " Debug p : " << p->Term;
			else
				cout << "Debug : " << "Fail to insert "<<word ;
			cout << endl;
			*/
			p->docList->Add(DocID);//向单词的文档链表中加入当前文档的编号
			/*
			cout << "----------------------"<<endl;
			cout << "Inserting " << word << endl;
			bbst->debug(bbst->root());//打印整颗树
			cout << "----------------------"<<endl;
			*/
		}
	}
	out << DocID << endl;//输出文档的总数
	for(int i = 0; i<content.size(); i++){
		out << content[i] << endl;//输出所有的发帖内容
	}
	bbst->debug(bbst->root());//打印整颗树
}

void SearchEngine::searchWordList(vector<CharString> wordList, ostream& out){
	DocList list;
	for(int i=0; i<wordList.size(); i++){
		
	}
}