#pragma once
#include "CharString.h"
#include "CharStringLink.h"
#include "Dictionary.h"
#include <iostream>
#include <memory>

enum MatchingType{//括号匹配的类型
	SelfMatched, //自我匹配，形如<**/>
	Left,//左界，形如<**>
	Right//右界，形如</**>
};

struct Node{//html文本中的节点
	CharString m_tag;//标签类型,比如"a","div"
	CharString m_class;//类,比如 <a class="z"> 中"z"就是类
	int left;//左括号在文本中的位置
	int right;//右括号在文本中的位置
	MatchingType matchingType;//括号匹配的类型
	Node(){m_tag=""; m_class="";}
};

typedef std::shared_ptr<Node> NodePosi;//节点位置

class Record{//为每一个网页生成的一条记录
public:
	CharString url;//网页
	CharString category;//发帖大类
	CharString subclass;//发帖小类
	CharString title;//发帖标题
	CharString content;//发帖内容
	CharString userName;//发帖人
	CharString date;//发帖日期
	CharString type;//发帖类型
	friend std::ostream& operator<<(std::ostream& out, const Record& record);
};

class WebsiteProcessor//网页处理类
{
private:
	std::shared_ptr<Dictionary> dictionary;//词典指针

	NodePosi readOnePairOfBracket(const CharString& string, int& i);
	//从字符串string的第i个位置开始读取一对匹配的括号，并返回这对括号组成的节点

	int getFirstLeftBracket(const CharString& string, int i);
	//获得字符串string从第i个位置起第一个左括号的位置
	
	void downloadWebsite(const CharString& url, CharString& filename); 
	//下载url网页到本地文件filename
	
	void processHtml(const CharString& htmlText, std::ofstream& out, bool readWholeWebsite, bool removeUselessWords);
	//处理本地文件htmlText，并将结果输出到out中 

	void readURL(std::ifstream& in, CharString& url);
	//读入输入流in中的网页，得到网页的url


public:
	WebsiteProcessor(void);
	~WebsiteProcessor(void);

	void process(std::ifstream& in, std::ofstream& out, bool readWholeWebsite, bool removeUselessWords);
	//处理输入流in中的所有网页，并将结果输出到输出流out中
	//如果readWholeWebsite为true，则会读完整个网页，但是效率会比较低；如果为false，则只要得到所需的信息后，就返回，效率较高
	//如果removeUselessWords为true，则分词结果就会删除无用词；为false，则保留无用词

	void extractInfo(CharString& inputFile, CharString& outputFile, bool readWholeWebsite, bool removeUselessWords);
	//处理inputFile中的所有网页，将结果存储到outputFile中，失败的话返回false
	
	void initDictionary();//初始化词库

	CharStringLink divideWords(const CharString& sentence, bool removeUselessWords);//对句子进行分词
	//如果removeUselessWords为true，则分词结果就会删除无用词；为false，则保留无用词

};

