#include "stdafx.h"
#include "WebsiteProcessor.h"
using namespace std;
#include <fstream>
#include <string>
#include "Stack.h"

//---------------用于curl----------------
#include <Windows.h>      
#include "curl/curl.h"      
#pragma comment(lib, "libcurl.lib")       
#pragma comment(lib, "wldap32.lib")       
#pragma comment(lib, "ws2_32.lib")       
#pragma comment(lib, "winmm.lib")       
 //---------------用于curl----------------
 
WebsiteProcessor::WebsiteProcessor(void)
{
}


WebsiteProcessor::~WebsiteProcessor(void)
{
}

NodePosi WebsiteProcessor::readOnePairOfBracket(const CharString& string, int i){
	//从字符串string的第i个位置开始读取一对匹配的括号，
	//并返回这对括号组成的节点
	return NULL;
}
int WebsiteProcessor::getFirstLeftBracket(const CharString& string, int i){
	//获得字符串string从第i个位置起第一个左括号的位置
	return 0;
}

size_t write_data(char *buffer,size_t size, size_t nitems,void *outstream)//将buffer中的内容写到outstream中 
{    
    int written = fwrite(buffer, size, nitems, (FILE*)outstream);    
    return written;    
}    

void WebsiteProcessor::downloadWebsite(const CharString& url, CharString& filename){ //下载url网页到本地文件，返回文件名
	filename = "temp.txt";//文件名字符串
	unique_ptr<char> fileData( filename.data() );//文件名对应的字符数组

	CURL *pCurl;//创建一个curl类      
	FILE* pFile = fopen( fileData.get(), "wb" );//新建本地的一个文件
    pCurl = curl_easy_init();//初始化curl

	//-----------------在数据头设置字符集为UTF-8，解决中文乱码问题------------------------------------
    struct curl_slist *head = NULL;  
    head = curl_slist_append(head, "Content-Type:application/x-www-form-urlencoded;charset=utf-8");  
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, head);
	//-----------------在数据头设置字符集为UTF-8，解决中文乱码问题------------------------------------

    curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)pFile);//设置curl的写位置
    curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, write_data);//设置curl的写方法

	unique_ptr<char> urlData(url.data());//url对应的字符数组
	curl_easy_setopt(pCurl, CURLOPT_URL, urlData);//设置curl下载的网页的url
    
	curl_easy_perform(pCurl);//执行curl的网页下载
    fclose(pFile);//关闭文件
	
	curl_slist_free_all(head);//释放数据头

    curl_easy_cleanup( pCurl );//析构curl        
}

void WebsiteProcessor::processHtml(const CharString& htmlText, std::ofstream& out){
	//处理本地文件htmlText，并将结果输出到out中 	
	
	ifstream outfile; //文件输出流
	unique_ptr<char> data( htmlText.data() );//字符串htmlText对应的字符数组
	outfile.open(data.get());//打开本地文件htmlText
	if(!outfile){
		cout << "文件打开失败"<< data.get()<<endl;
	}else{
		string temp( (istreambuf_iterator<char>(outfile)), istreambuf_iterator<char>() );
		//从文件读取数据到stl字符串temp
		CharString string(temp);//然后将其转化成CharString

		//-----------------接下来对字符串string进行处理----------------------------------
		/*
		Stack<CharString> divClassStack;//存储当前位置外层的所有div的class
		Stack<NodePosi> nodeStack;//存储已经所有节点类型为左界的节点，并且这些节点对应的右界都还没有扫描到
		for(int i=0; i<string.size(); ){
			i = getFirstLeftBracket(string, i);//找到第一个左括号
			NodePosi node = readOnePairOfBracket(string, i);//读入一对匹配的括号所构成的节点
			switch (node->matchingType)//根据节点的类型,若当前节点是
			{
			case SelfMatched://自匹配，不做处理
				break;
			case Left://左界
				if(node->m_tag == "div"){//若节点的标签是"div"
					divClassStack.push(node->m_class);//则记录节点的class
					nodeStack.push(node);//并将节点压栈
				}
				break;
			case Right://右界
				if(node->m_tag == "a"){//若节点的标签是"a"

				}else if(node->m_tag == "p"){

				}else if(node->m_tag == "enum"){

				}else if(node->m_tag == "div"){
					divClassStack.pop();
				}
				nodeStack.pop();//节点出栈
			default:
				break;
			}
		}
		*/
		cout << string;
	}
}
