#include "stdafx.h"
#include "WebsiteProcessor.h"
using namespace std;
#include <fstream>
#include <string>
#include "Stack.h"

//---------------����curl----------------
#include <Windows.h>      
#include "curl/curl.h"      
#pragma comment(lib, "libcurl.lib")       
#pragma comment(lib, "wldap32.lib")       
#pragma comment(lib, "ws2_32.lib")       
#pragma comment(lib, "winmm.lib")       
 //---------------����curl----------------
 
WebsiteProcessor::WebsiteProcessor(void)
{
}


WebsiteProcessor::~WebsiteProcessor(void)
{
}

NodePosi WebsiteProcessor::readOnePairOfBracket(const CharString& string, int i){
	//���ַ���string�ĵ�i��λ�ÿ�ʼ��ȡһ��ƥ������ţ�
	//���������������ɵĽڵ�
	return NULL;
}
int WebsiteProcessor::getFirstLeftBracket(const CharString& string, int i){
	//����ַ���string�ӵ�i��λ�����һ�������ŵ�λ��
	return 0;
}

size_t write_data(char *buffer,size_t size, size_t nitems,void *outstream)//��buffer�е�����д��outstream�� 
{    
    int written = fwrite(buffer, size, nitems, (FILE*)outstream);    
    return written;    
}    

void WebsiteProcessor::downloadWebsite(const CharString& url, CharString& filename){ //����url��ҳ�������ļ��������ļ���
	filename = "temp.txt";//�ļ����ַ���
	unique_ptr<char> fileData( filename.data() );//�ļ�����Ӧ���ַ�����

	CURL *pCurl;//����һ��curl��      
	FILE* pFile = fopen( fileData.get(), "wb" );//�½����ص�һ���ļ�
    pCurl = curl_easy_init();//��ʼ��curl

	//-----------------������ͷ�����ַ���ΪUTF-8�����������������------------------------------------
    struct curl_slist *head = NULL;  
    head = curl_slist_append(head, "Content-Type:application/x-www-form-urlencoded;charset=utf-8");  
	curl_easy_setopt(pCurl, CURLOPT_HTTPHEADER, head);
	//-----------------������ͷ�����ַ���ΪUTF-8�����������������------------------------------------

    curl_easy_setopt(pCurl, CURLOPT_WRITEDATA, (void*)pFile);//����curl��дλ��
    curl_easy_setopt(pCurl, CURLOPT_WRITEFUNCTION, write_data);//����curl��д����

	unique_ptr<char> urlData(url.data());//url��Ӧ���ַ�����
	curl_easy_setopt(pCurl, CURLOPT_URL, urlData);//����curl���ص���ҳ��url
    
	curl_easy_perform(pCurl);//ִ��curl����ҳ����
    fclose(pFile);//�ر��ļ�
	
	curl_slist_free_all(head);//�ͷ�����ͷ

    curl_easy_cleanup( pCurl );//����curl        
}

void WebsiteProcessor::processHtml(const CharString& htmlText, std::ofstream& out){
	//�������ļ�htmlText��������������out�� 	
	
	ifstream outfile; //�ļ������
	unique_ptr<char> data( htmlText.data() );//�ַ���htmlText��Ӧ���ַ�����
	outfile.open(data.get());//�򿪱����ļ�htmlText
	if(!outfile){
		cout << "�ļ���ʧ��"<< data.get()<<endl;
	}else{
		string temp( (istreambuf_iterator<char>(outfile)), istreambuf_iterator<char>() );
		//���ļ���ȡ���ݵ�stl�ַ���temp
		CharString string(temp);//Ȼ����ת����CharString

		//-----------------���������ַ���string���д���----------------------------------
		/*
		Stack<CharString> divClassStack;//�洢��ǰλ����������div��class
		Stack<NodePosi> nodeStack;//�洢�Ѿ����нڵ�����Ϊ���Ľڵ㣬������Щ�ڵ��Ӧ���ҽ綼��û��ɨ�赽
		for(int i=0; i<string.size(); ){
			i = getFirstLeftBracket(string, i);//�ҵ���һ��������
			NodePosi node = readOnePairOfBracket(string, i);//����һ��ƥ������������ɵĽڵ�
			switch (node->matchingType)//���ݽڵ������,����ǰ�ڵ���
			{
			case SelfMatched://��ƥ�䣬��������
				break;
			case Left://���
				if(node->m_tag == "div"){//���ڵ�ı�ǩ��"div"
					divClassStack.push(node->m_class);//���¼�ڵ��class
					nodeStack.push(node);//�����ڵ�ѹջ
				}
				break;
			case Right://�ҽ�
				if(node->m_tag == "a"){//���ڵ�ı�ǩ��"a"

				}else if(node->m_tag == "p"){

				}else if(node->m_tag == "enum"){

				}else if(node->m_tag == "div"){
					divClassStack.pop();
				}
				nodeStack.pop();//�ڵ��ջ
			default:
				break;
			}
		}
		*/
		cout << string;
	}
}
