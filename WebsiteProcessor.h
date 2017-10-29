#pragma once
#include "CharString.h"
#include <iostream>
#include <memory>

enum MatchingType{//����ƥ�������
	SelfMatched, //����ƥ�䣬����<**/>
	Left,//��磬����<**>
	Right//�ҽ磬����</**>
};

struct Node{//html�ı��еĽڵ�
	CharString m_tag;//��ǩ����,����"a","div"
	CharString m_class;//��,���� <a class="z"> ��"z"������
	int left;//���������ı��е�λ��
	int right;//���������ı��е�λ��
	MatchingType matchingType;//����ƥ�������
	Node(){m_tag=""; m_class="";}
};

typedef std::shared_ptr<Node> NodePosi;//�ڵ�λ��

class Record{//Ϊÿһ����ҳ���ɵ�һ����¼
public:
	CharString url;//��ҳ
	CharString category;//��������
	CharString subclass;//����С��
	CharString title;//��������
	CharString content;//��������
	CharString userName;//������
	CharString date;//��������
	CharString type;//��������
	friend std::ostream& operator<<(std::ostream& out, const Record& record);
};

class WebsiteProcessor//��ҳ������
{
private:
	NodePosi readOnePairOfBracket(const CharString& string, int& i);
	//���ַ���string�ĵ�i��λ�ÿ�ʼ��ȡһ��ƥ������ţ����������������ɵĽڵ�

	int getFirstLeftBracket(const CharString& string, int i);
	//����ַ���string�ӵ�i��λ�����һ�������ŵ�λ��
	
	void downloadWebsite(const CharString& url, CharString& filename); 
	//����url��ҳ�������ļ�filename
	
	void processHtml(const CharString& htmlText, std::ofstream& out);
	//�������ļ�htmlText��������������out�� 

	void readURL(std::ifstream& in, CharString& url);
	//����������in�е���ҳ���õ���ҳ��url

public:
	WebsiteProcessor(void);
	~WebsiteProcessor(void);

	void process(std::ifstream& in, std::ofstream& out);
	//����������in�е�������ҳ�������������������out��
};

