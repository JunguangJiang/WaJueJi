#include "stdafx.h"
#include "WebsiteProcessor.h"
using namespace std;
#include <fstream>
#include <string>
#include "Stack.h"
#include <vector>

//---------------用于curl----------------
#include <Windows.h>      
#include "curl/curl.h"      
#pragma comment(lib, "libcurl.lib")       
#pragma comment(lib, "wldap32.lib")       
#pragma comment(lib, "ws2_32.lib")       
#pragma comment(lib, "winmm.lib")       
 //---------------用于curl----------------
 

ostream& operator<<(ostream& out, const Record& record){
		out << "url "<< record.url << endl;
		out << "category " << record.category<<endl;
		out << "subclass "<<record.subclass <<endl;
		out << "title " << record.title <<endl;
		//out << "content "<< record.content<<endl;
		out << "userName "<< record.userName << endl;
		out << "date " << record.date << endl;
		out << "type " << record.type << endl;
		return out;
}

WebsiteProcessor::WebsiteProcessor(void)
{
}


WebsiteProcessor::~WebsiteProcessor(void)
{
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

NodePosi WebsiteProcessor::readOnePairOfBracket(const CharString& string, int& i){
	//从字符串string的第i个位置开始读取一对匹配的括号，
	//并返回这对括号组成的节点
	NodePosi node(new Node());
	node->left = i; //左括号的位置
	node->right = string.indexOf(">", i+1);//从i+1的位置开始找">"，找到的位置即为右括号的位置
	i = node->right;//此后从右括号的右边开始找起

	CharString sub;
	string.subString(node->left, node->right+1, sub);//求取原来字符串在上述左右括号间的子串
	//cout << sub << endl;
	if(sub[1] == '/'){
		node->matchingType = Right;
	}else if(sub[sub.size()-2] == '/' || sub[1] == '!'){
		node->matchingType = SelfMatched;
	}else{
		node->matchingType = Left;
		int j = sub.indexOf(" ", 1);//j指示子串中第一次出现空格的位置
		if(j < 0){//如果空格不存在，
			sub.subString(1, sub.size()-1, node->m_tag);//则两个括号之间只有标签的内容
		}else{//如果存在括号，
			int k1 = sub.indexOf("class=", j+1);//k1指示类class的位置
			if(k1 >= 0){//如果括号之间存在类，
				k1 = sub.indexOf("\"", k1+1);//k1指示左引号的位置
				int k2 = sub.indexOf("\"", k1+1);//k2指示右引号的位置
				sub.subString(k1+1, k2, node->m_class);//[k1+1, k2)就是引号中的内容
			}
			sub.subString(1, j, node->m_tag);//左括号与空格之间的为标签的内容
		}
	}
	return node;
}
int WebsiteProcessor::getFirstLeftBracket(const CharString& string, int i){
	//获得字符串string从第i个位置起第一个左括号的位置
	return string.indexOf("<", i);
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
		
		Stack<CharString> divClassStack;//存储当前位置外层的所有div的class
		divClassStack.push(CharString(""));//在栈底加一个哨兵

		Stack<NodePosi> nodeStack;//存储已经所有节点类型为左界的节点，并且这些节点对应的右界都还没有扫描到

		vector<shared_ptr<CharString>> z_a;//发帖大类，发帖小类、发帖标题
		vector<shared_ptr<CharString>> tfsz_p;//正文
		vector<shared_ptr<CharString>> authi_a;//发帖人
		vector<shared_ptr<CharString>> authi_em;//发帖日期
		vector<shared_ptr<CharString>> tszh1_a;//发帖分类、发帖标题
		
		Record record;//一条记录
		record.url = htmlText;//修改记录的url

		for(int i=0; i<string.size(); ){
			i = getFirstLeftBracket(string, i);//找到第一个左括号
			if(i<0)//如果此时已经找不到多余的括号了，
				break;//则停止查找
			
			NodePosi node = readOnePairOfBracket(string, i);
			//读入一对匹配的括号所构成的节点,并且i被自动更新到右括号右边的位置
			
			switch (node->matchingType)//根据节点的类型,若当前节点是
			{
			case SelfMatched://自匹配，不做处理
				break;
			case Left://左界
				if(node->m_tag == "div"){//若节点的标签是"div"
					divClassStack.push(node->m_class);//则记录节点的class
				}
				nodeStack.push(node);//并将节点压栈
				break;
			case Right://右界
				if(nodeStack.empty()){//假如栈中没有节点,说明出现问题
					std::cout << "error in  match"<<endl;
					break;
				}else if(nodeStack.top()->m_tag == "a"){//若节点的标签是"a"
					if(divClassStack.top() == "z"){//并且所在的div为z，则
						shared_ptr<CharString> content(new CharString);//对应发帖大类、发帖小类、发帖标题
						string.subString(nodeStack.top()->right+1, node->left, *content);//取得文本内容
						z_a.push_back(content);//将其存储在z_a中
						//std::cout << "z " << *(content)<<endl;
					}else if(divClassStack.top() == "ts z h1"){//并且所在的div为ts z h1,则
						shared_ptr<CharString> content(new CharString);//对应发帖分类、发帖标题
						string.subString(nodeStack.top()->right+2, node->left-1, *content);//此处将外侧的"[" "]"一并去除了,得到文本内容
						tszh1_a.push_back(content);//将其存储在tszh1_a中
						//std::cout << "ts z h1 " << *(content)<<endl;
					}else if(divClassStack.top() == "authi"){//并且所在的div为authi，则
						shared_ptr<CharString> content(new CharString);//对应发帖人
						string.subString(nodeStack.top()->right+1, node->left, *content);//取得文本内容
						authi_a.push_back(content);//将其存储在authi_a中
						//std::cout << "authi a " << *(content)<<endl;
					}
				}else if(nodeStack.top()->m_tag == "p"){//如果是标签为p
					if(divClassStack.top() == "t_fsz"){//并且所在的div为t_fsz,则
						shared_ptr<CharString> content(new CharString);//对应发帖内容
						string.subString(nodeStack.top()->right+1, node->left, *content);//将发帖内容存在
						//tfsz_p.push_back(content);//tfsz_p中，Note：此处p内文本未能解码！！！
						//std::cout << "tfsz p " << *(content)<<endl;
					}
				}else if(nodeStack.top()->m_tag == "em"){//如果标签是em
					if(divClassStack.top() == "authi"){//并且所在的div为authi，则
						shared_ptr<CharString> content(new CharString);//对应发帖日期
						string.subString(nodeStack.top()->right+7, node->left-9, *content);//截取日期段
						authi_em.push_back(content);//将其存在authi_em中
						//std::cout << "authi em " << *(content)<<endl;
					}
				}else if(nodeStack.top()->m_tag == "div"){//如果标签是div
					divClassStack.pop();//则最内层的div结束
				}
				nodeStack.pop();//节点出栈
				break;
			default:
				break;
			}
		}
		if(z_a.size()<5 || tszh1_a.empty() || authi_a.empty() || authi_em.empty()//对于无法获取信息的情况
			//|| tfsz_p.empty()//发帖内容，编码问题尚未解决
				){
				out << endl;
				return;
		}
		record.category = *z_a[2];//大类
		record.subclass = *z_a[3];//小类
		record.title = *z_a[4];//标题
		record.type = *tszh1_a[0];//类型
		record.userName = *authi_a[0];//发帖人
		record.date = *authi_em[0];//发帖日期
		//record.content = *tfsz_p[0];//发帖内容，编码问题尚未解决

		//cout << record;//输出record到屏幕上，用作调试
		
		//将结果输出到输出流
		out << record.category << "," << record.subclass << "," << record.title << ","
			/*<< record.content << "," 编码问题尚未解决*/ << record.userName << "," << record.date << "," 
			<< record.type //Note:此处之后加入分词结果！！！
			<< endl;

		outfile.close();//关闭文件
	}
}


void WebsiteProcessor::readURL(std::ifstream& in, CharString& url)//读入输入流in中的网页，得到网页的url
{
	string temp;
	getline(in, temp);//输入文件中的一行
	CharString line(temp);//将其转化为CharString
	int left = line.indexOf("\"",0);//找到左引号的位置
	int right = line.indexOf("\"", left+1);//找到右引号的位置
	line.subString(left+1, right, url);//截取引号之间的内容存到url中
}

void WebsiteProcessor::process(std::ifstream& in, std::ofstream& out){
	//处理输入流in中的所有网页，并将结果输出到输出流out中
	string temp;
	getline(in, temp);//读入的第一行的内容无用
	//输出第一行内容
	out << "\"序号\",\"网址\",\"发帖大类\",\"发帖小类\",\"发帖标题\"," ;
	out << "\"发帖内容\",\"发帖人\",\"发帖日期\",\"发帖类型\",\"分词结果\"";
	out << endl;
	int id = 1;
	while(!in.eof()){//一直输入到文件末尾
		CharString url;
		readURL(in, url);//读入网页的url
		if(in.eof()) break;
		CharString filename;//本地文件
		downloadWebsite(url, filename);//将网页下载到本地文件filename
		out << id++ << "," << url << "," ;//先输出序号和网页url
		processHtml(filename, out);//然后处理本地文件filename，将处理后的信息输出到输出流
	}
}