#include "stdafx.h"
#include "Dictionary.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
#include "Stack.h"
using namespace std;

static size_t hashCode(const char* string){//�����ַ�����ѭ����λɢ����
	unsigned int h = 0;//ɢ����
	for(size_t n = strlen(string), i = 0; i < n; i++){
		h = ( h << 5 ) | ( h >> 27 ); 
		h += (unsigned int)string[i];//ɢ����ѭ������5λ�����ۼӵ�ǰ�ַ�
	}
	return (size_t) h ;
}

static size_t hashCode(const CharString& string){
	return hashCode(string.data());
}

bool inline isASCII(char c){//�ж�ĳ���ַ��Ƿ���ASCII��:Ŀǰ����ĸ�����֡�Ӣ�ĵı����Ŷ��������У������ǻ��з���
	int d = (int)c;
	return (d<127)&&(d>31);//ASCII���е�һЩ�ַ�
}

bool inline isEnglishLetter(char c){//�ж�ĳ���ַ��Ƿ���Ӣ����ĸ
	int d = (int) c;
	return ( ( ( d>=65 ) && ( d <= 90 ) ) || ( ( d>=97 ) && ( d<=122 ) ) );
}

bool inline isNumber(int c){//�ж�ĳ���ַ��Ƿ�������
	int d = (int) c;
	return ( (c>=48) && (c<=57) );
}

Dictionary::Dictionary(int c)
{
	M = c; N = 0;//��ʼ����Ϊc����ģΪ0
	ht = new CharStringLink*[M];//����Ͱ����
	for(int i=0; i<M; i++)
		ht[i] = new CharStringLink();
}


Dictionary::~Dictionary(void)
{
	for(int i=0; i<M; i++){
		delete ht[i]; ht[i] = NULL;
	}
	delete [] ht; ht = NULL;
}

void Dictionary::put(const CharString& word){//�������
	put(word.data());
}

bool Dictionary::search(const CharString& word){//��ѯĳ�����Ƿ��ڴʵ���
	return search(word.data());
}

void Dictionary::put(const char* word){//�������
	size_t  h = hashCode(word) % M;//�õ����ַ�����hash��
	ht[h]->add(word);//��hash���Ӧ���ַ�������ĩβ�������
	N++;//��ģ��һ
}

bool Dictionary::search(const char* word){//��ѯĳ�����Ƿ��ڴʵ���
	size_t h =hashCode(word) % M;//�õ����ַ�����hash��
	return (ht[h]->search(word) >= 0);//�����hash���Ӧ���ַ����������ҵ��˴���word,�򷵻�true�����򷵻�false
}

string UTF8ToGB(const char* str)//��utf8ת��ΪGB���룬��Դ������ http://blog.csdn.net/zhancf/article/details/49930969
{
	 string result;
	 WCHAR *strSrc;
	 LPSTR szRes;

	 //�����ʱ�����Ĵ�С
	 int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	 strSrc = new WCHAR[i+1];
	 MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	 //�����ʱ�����Ĵ�С
	 i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	 szRes = new CHAR[i+1];
	 WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	 result = szRes;
	 delete []strSrc; strSrc = NULL;
	 delete []szRes; szRes = NULL;

	 return result;
}

void Dictionary::download(const char* vocabularyFile, bool isUTF8){//���ر��ص�һ���ʻ��ļ�
	ifstream in; 
	in.open(vocabularyFile, ios::binary);
	if(!in){
		cout << "error in open dictionary " << vocabularyFile <<endl;
		exit(-1);
	}
	if(isUTF8){//��Ӧutf8�ļ�
		while(!in.eof()){//�����ļ��е�
			char temp[50];//ÿ������
			in >> temp;
			put(UTF8ToGB(temp).c_str());//���������ʵ���
		}
	}else{//��Ӧgb�ļ�
		while(!in.eof()){//�����ļ��е�
			string temp;//ÿ������
			in >> temp;
			put(temp.c_str());//���������ʵ���
		}
	}
	in.close();
}

void Dictionary::init(){//�ʵ�ĳ�ʼ��
	download("./Dictionary/dictionary.dic", true);
	download("./Dictionary/professionalTerms.dic", false);
	initStopLetterLink();//��ʼ��ͣ�ñ���������
	initUselessWordLink();//��ʼ�����ô�����
}

int Dictionary::getMaxHtSize(){//������Ͱ�Ĺ�ģ���������ܵķ���
	int max=0;
	for(int i=0; i<M; i++){
		if(ht[i]->size() > max)
			max = ht[i]->size();
	}
	return max;
}

void Dictionary::print(){//��ӡ���е�Ͱ���������ܷ���
	for(int i=0; i<M;i++){
		cout << "chap "<< i;
		ht[i]->print(cout);
	}
}

CharStringLinkPosi Dictionary::divideSentence(const CharString& sentence, bool removeUselessWord){
	//��һ�����ӽ��зִʣ��������г��ֱ����š����֡�Ӣ���ַ���������ȡ�����Ĺؼ���
	//�������еı����š����֡�Ӣ���ַ�
	CharStringLinkPosi link(new CharStringLink());//�½�һ���ַ�������,�洢���ӵķִʽ��
	Stack<CharString> S;//�洢���еĶ���

	int left =-1, right = 0;//left��ʾ��һ��
	while(right < sentence.size()){//������������
		if(isASCII(sentence[right])){//�����ǰ�ַ���ASCII�ַ�
			if( (left+1) < right ){//���[left+1,right)֮�����GB�ַ�(���
				CharString string = sentence.subString(left+1, right);//����ȡ��
				S.push(string);//������ջ��
			}
			left = right;//left�����һ���ҵ���ͣ�ô�λ��
			right++;//�鿴��һ���ַ�
		}else if( (right<sentence.size()-1) && ( isStopLetter(sentence.subString(right, right+2)) ) ){//����������ַ����������е�һ��ͣ�ô�
			if( (left+1) < right ){//���[left+1,right)֮�����GB�ַ�(���
				CharString string = sentence.subString(left+1, right);//����ȡ��
				S.push(string);//������ջ��
			}
			left = right+1;
			right = right+2;
		}else{//�������
			right += 2;//˵����ǰ�ַ���GB�룬�鿴����һ���ַ�
		}
	}
	if( (left+1) < right){//�������һ������
		CharString string; sentence.subString(left+1, right, string);
		S.push(string);
	}

	while(!S.empty()){//��ջ��ȡ�����еĶ���
		CharString string = S.top(); S.pop();
		CharStringLinkPosi tempLink = dividePhrase(string, removeUselessWord);//����ִʣ����ֲ��ִʽ������tempLink
		if(tempLink->size()>0)
			link->add(tempLink);//���ֲ��ִʽ��tempLink�����ܵķִʽ��link��
	}
	return link;
}

CharStringLinkPosi Dictionary::dividePhrase(const CharString& phrase, bool removeUselessWord){
//��phrase���յ�ǰ���صĴʿ���зִʣ������ַ����������ʽ���ؽ��
//�����������ִ��㷨
	CharStringLinkPosi link(new CharStringLink());//�½�һ���ַ�������
	
	if(removeUselessWord){//���Ӧ��ɾ�����ô�
		int left, right = phrase.size();//left,right���Ӵ������ҽ�
		while(right > 0){//��������phrase
			left = max(right-MaxWordLength, 0);//�Ӵ������
			while(left < right){
				CharString subString = phrase.subString(left, right);//�Ӵ�
				//phrase.subString(left, right, subString);//subString = phrase[left, right)
				if( search( subString)  && !isUselessWord(subString)){//���subString��һ����,���Ҳ������ô�
					link->add(subString);//��subString�����ַ�������
					break;
				}else{//���subString����һ����
					left+=2;//����������ƶ�һ������
				}
			}

			if(left == right){
				//Note:�����ʱleft==right�����ڲ�ѭ����ʼ��û���ҵ�һ����,
				//����[left-2,right)������һ���ʵ��еĴʣ��˴���ʱ�������������
			
				CharString subString = phrase.subString(left-2, right);//�Ӵ�
				//phrase.subString(left-2, right, subString);//subString = string[left-2, right)
				if(!isUselessWord(subString))//����Ӵ��������ô�
					link->add(subString.data());
				//cout << subString << endl;
			
				right = left-2;
			}else{
				//Note:�����ʱleft!=right,���ҵ��˴�[left,right)
				right = left;
			}
		}
	}else{//�����Ӧ��ɾ�����ô�
		int left, right = phrase.size();//left,right���Ӵ������ҽ�
		while(right > 0){//��������phrase
			left = max(right-MaxWordLength, 0);//�Ӵ������
			while(left < right){
				CharString subString = phrase.subString(left, right);//�Ӵ�
				//phrase.subString(left, right, subString);//subString = phrase[left, right)
				if( search( subString)){//���subString��һ����
					link->add(subString);//��subString�����ַ�������
					break;
				}else{//���subString����һ����
					left+=2;//����������ƶ�һ������
				}
			}

			if(left == right){
				//Note:�����ʱleft==right�����ڲ�ѭ����ʼ��û���ҵ�һ����,
				//����[left-2,right)������һ���ʵ��еĴʣ��˴���ʱ�������������
			
				CharString subString = phrase.subString(left-2, right);//�Ӵ�
				//phrase.subString(left-2, right, subString);//subString = string[left-2, right)
				link->add(subString.data());
				//cout << subString << endl;
				right = left-2;
			}else{
				//Note:�����ʱleft!=right,���ҵ��˴�[left,right)
				right = left;
			}
		}
	}
	
	return link;
}

void Dictionary::initStopLetterLink(){//��ʼ��ͣ�ô�
	stopLetterLink = make_shared<CharStringLink>();
	const char* stopWordFile = "./Dictionary/stopLetter.dic";
	ifstream in; 
	in.open(stopWordFile, ios::binary);
	if(!in){
		cout << "error in open dictionary " << stopWordFile <<endl;
		exit(-1);
	}
	while(!in.eof()){//�����ļ��е�
		CharString temp;//ÿ��ͣ�ô�
		in >> temp;
		stopLetterLink->add(temp);
	}
	in.close();
}

bool Dictionary::isStopLetter(CharString word){
	return (stopLetterLink->search(word)!=-1);
}

void Dictionary::initUselessWordLink(){//��ʼ��ueslessWordLink
	uselessWordLink = new CharStringLinkPosi[uselessWordLinkSize];
	for(int i=0; i<uselessWordLinkSize; i++){
		uselessWordLink[i] = make_shared<CharStringLink>();
	}

	const char* uselessWordFile = "./Dictionary/uselessWord.dic";
	ifstream in; 
	in.open(uselessWordFile, ios::binary);
	if(!in){
		cout << "error in open dictionary " << uselessWordFile <<endl;
		exit(-1);
	}
	while(!in.eof()){//�����ļ��е�
		CharString word;//ÿ��ͣ�ô�
		in >> word;
		size_t  h = hashCode(word) % uselessWordLinkSize;//�õ����ַ�����hash��
		uselessWordLink[h]->add(word);//��hash���Ӧ���ַ�������ĩβ�������ô�
	}
	in.close();
}
bool Dictionary::isUselessWord(CharString word){//�ж�ĳ�����Ƿ�����
	size_t h = hashCode(word) % uselessWordLinkSize;//�õ��ôε�hash��
	return (uselessWordLink[h]->search(word) >= 0);//�����hash���Ӧ�����ô��������ҵ��˴���word,�򷵻�true�����򷵻�false
}