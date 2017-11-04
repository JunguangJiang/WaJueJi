#include "stdafx.h"
#include "WebsiteProcessor.h"
using namespace std;
#include <fstream>
#include <string>
#include "Stack.h"
#include <vector>

//---------------����curl----------------
#include <Windows.h>      
#include "curl/curl.h"      
#pragma comment(lib, "libcurl.lib")       
#pragma comment(lib, "wldap32.lib")       
#pragma comment(lib, "ws2_32.lib")       
#pragma comment(lib, "winmm.lib")       
 //---------------����curl----------------
 

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

NodePosi WebsiteProcessor::readOnePairOfBracket(const CharString& string, int& i){
	//���ַ���string�ĵ�i��λ�ÿ�ʼ��ȡһ��ƥ������ţ�
	//���������������ɵĽڵ�
	NodePosi node(new Node());
	node->left = i; //�����ŵ�λ��
	node->right = string.indexOf(">", i+1);//��i+1��λ�ÿ�ʼ��">"���ҵ���λ�ü�Ϊ�����ŵ�λ��
	i = node->right;//�˺�������ŵ��ұ߿�ʼ����

	CharString sub = string.subString(node->left, node->right+1);//��ȡԭ���ַ����������������ż���Ӵ�
	if(sub[1] == '/'){
		node->matchingType = Right;
	}else if(sub[sub.size()-2] == '/' || sub[1] == '!'){
		node->matchingType = SelfMatched;
	}else{
		node->matchingType = Left;
		int j = sub.indexOf(" ", 1);//jָʾ�Ӵ��е�һ�γ��ֿո��λ��
		if(j < 0){//����ո񲻴��ڣ�
			node->m_tag = sub.subString(1, sub.size()-1);//����������֮��ֻ�б�ǩ������
		}else{//����������ţ�
			int k1 = sub.indexOf("class=", j+1);//k1ָʾ��class��λ��
			if(k1 >= 0){//�������֮������࣬
				k1 = sub.indexOf("\"", k1+1);//k1ָʾ�����ŵ�λ��
				int k2 = sub.indexOf("\"", k1+1);//k2ָʾ�����ŵ�λ��
				node->m_class = sub.subString(k1+1, k2);//[k1+1, k2)���������е�����
			}
			node->m_tag = sub.subString(1, j);//��������ո�֮���Ϊ��ǩ������
		}
	}
	return node;
}
int WebsiteProcessor::getFirstLeftBracket(const CharString& string, int i){
	//����ַ���string�ӵ�i��λ�����һ�������ŵ�λ��
	return string.indexOf("<", i);
}

void WebsiteProcessor::processHtml(const CharString& htmlText, std::ofstream& out, bool removeUselessWords){
	//�������ļ�htmlText��������������out�� 	
	
	ifstream outfile; //�ļ������
	unique_ptr<char> data( htmlText.data() );//�ַ���htmlText��Ӧ���ַ�����
	outfile.open(data.get());//�򿪱����ļ�htmlText
	if(!outfile){
		cout << "�ļ���ʧ��"<< data.get()<<endl;
	}else{
		string temp( (istreambuf_iterator<char>(outfile)), istreambuf_iterator<char>() );
		//���ļ���ȡ���ݵ�stl�ַ���temp
		CharString string;//Ȼ����ת����CharString

		//-----------------���������ַ���string���д���----------------------------------
		
		Stack<CharString> divClassStack;//�洢��ǰλ����������div��class
		divClassStack.push(CharString(""));//��ջ�׼�һ���ڱ�

		Stack<NodePosi> nodeStack;//�洢�Ѿ����нڵ�����Ϊ���Ľڵ㣬������Щ�ڵ��Ӧ���ҽ綼��û��ɨ�赽

		vector<shared_ptr<CharString>> z_a;//�������࣬����С�ࡢ��������
		vector<shared_ptr<CharString>> tfsz_p;//����
		vector<shared_ptr<CharString>> authi_a;//������
		vector<shared_ptr<CharString>> authi_em;//��������
		vector<shared_ptr<CharString>> tszh1_a;//�������ࡢ��������
		
		Record record;//һ����¼
		record.url = htmlText;//�޸ļ�¼��url

		for(int i=0; i<string.size(); ){
			i = getFirstLeftBracket(string, i);//�ҵ���һ��������
			if(i<0)//�����ʱ�Ѿ��Ҳ�������������ˣ�
				break;//��ֹͣ����
			
			NodePosi node = readOnePairOfBracket(string, i);
			//����һ��ƥ������������ɵĽڵ�,����i���Զ����µ��������ұߵ�λ��
			
			switch (node->matchingType)//���ݽڵ������,����ǰ�ڵ���
			{
			case SelfMatched://��ƥ�䣬��������
				break;
			case Left://���
				if(node->m_tag == "div"){//���ڵ�ı�ǩ��"div"
					divClassStack.push(node->m_class);//���¼�ڵ��class
				}
				nodeStack.push(node);//�����ڵ�ѹջ
				break;
			case Right://�ҽ�
				if(nodeStack.empty()){//����ջ��û�нڵ�,˵����������
					std::cout << "error in  match"<<endl;
					break;
				}else if(nodeStack.top()->m_tag == "a"){//���ڵ�ı�ǩ��"a"
					if(divClassStack.top() == "z"){//�������ڵ�divΪz����
						shared_ptr<CharString> content(new CharString);//��Ӧ�������ࡢ����С�ࡢ��������
						*content = string.subString(nodeStack.top()->right+1, node->left);//ȡ���ı�����
						z_a.push_back(content);//����洢��z_a��
					}else if(divClassStack.top() == "ts z h1"){//�������ڵ�divΪts z h1,��
						shared_ptr<CharString> content(new CharString);//��Ӧ�������ࡢ��������
						*content = string.subString(nodeStack.top()->right+2, node->left-1);//�˴�������"[" "]"һ��ȥ����,�õ��ı�����
						tszh1_a.push_back(content);//����洢��tszh1_a��
					}else if(divClassStack.top() == "authi"){//�������ڵ�divΪauthi����
						shared_ptr<CharString> content(new CharString);//��Ӧ������
						*content = string.subString(nodeStack.top()->right+1, node->left);//ȡ���ı�����
						authi_a.push_back(content);//����洢��authi_a��
					}
				}else if(nodeStack.top()->m_tag == "p"){//����Ǳ�ǩΪp
					if(divClassStack.top() == "t_fsz"){//�������ڵ�divΪt_fsz,��
						shared_ptr<CharString> content(new CharString);//��Ӧ��������
						*content = string.subString(nodeStack.top()->right+1, node->left);//���������ݴ���
						tfsz_p.push_back(content);//tfsz_p��
					}
				}else if(nodeStack.top()->m_tag == "em"){//�����ǩ��em
					if(divClassStack.top() == "authi"){//�������ڵ�divΪauthi����
						shared_ptr<CharString> content(new CharString);//��Ӧ��������
						*content = string.subString(nodeStack.top()->right+7, node->left-9);//��ȡ���ڶ�
						authi_em.push_back(content);//�������authi_em��
					}
				}else if(nodeStack.top()->m_tag == "div"){//�����ǩ��div
					divClassStack.pop();//�����ڲ��div����
				}
				nodeStack.pop();//�ڵ��ջ
				break;
			default:
				break;
			}
		}

		if(z_a.size()<5 || tszh1_a.empty() || authi_a.empty() || authi_em.empty()//�����޷���ȡ��Ϣ�����
			|| tfsz_p.empty()//��������
				){
				out << endl;
				return;
		}
		record.category = *z_a[2];//����
		record.subclass = *z_a[3];//С��
		record.title = *z_a[4];//����
		record.type = *tszh1_a[0];//����
		record.userName = *authi_a[0];//������
		record.date = *authi_em[0];//��������
		record.content = UnicodeToChinese(*tfsz_p[0]);//��������
		
		//���������������
		out << record.category << "," << record.subclass << "," << record.title << ","
			<< record.content << "," << record.userName << "," << record.date << "," 
			<< record.type << "," 
			<< divideWords(record.title, removeUselessWords) << divideWords(record.content, removeUselessWords)//����ִʽ��
			<< endl;

		outfile.close();//�ر��ļ�
	}
}


void WebsiteProcessor::readURL(std::ifstream& in, CharString& url)//����������in�е���ҳ���õ���ҳ��url
{
	string temp;
	getline(in, temp);//�����ļ��е�һ��
	CharString line(temp);//����ת��ΪCharString
	int left = line.indexOf("\"",0);//�ҵ������ŵ�λ��
	int right = line.indexOf("\"", left+1);//�ҵ������ŵ�λ��
	line.subString(left+1, right, url);//��ȡ����֮������ݴ浽url��
}

void WebsiteProcessor::process(std::ifstream& in, std::ofstream& out, bool removeUselessWords){
	//����������in�е�������ҳ�������������������out��
	//���removeUselessWordsΪtrue����ִʽ���ͻ�ɾ�����ôʣ�Ϊfalse���������ô�

	string temp;
	getline(in, temp);//����ĵ�һ�е���������
	//�����һ������
	out << "\"���\",\"��ַ\",\"��������\",\"����С��\",\"��������\"," ;
	out << "\"��������\",\"������\",\"��������\",\"��������\",\"�ִʽ��\"";
	out << endl;
	int id = 1;
	while(!in.eof()){//һֱ���뵽�ļ�ĩβ
		CharString url;
		readURL(in, url);//������ҳ��url
		if(in.eof()) break;
		CharString filename;//�����ļ�
		cout << "downloading "<< url<<endl;
		downloadWebsite(url, filename);//����ҳ���ص������ļ�filename
		out << id++ << "," << url << "," ;//�������ź���ҳurl
		cout << "processing "<< url<<endl;
		processHtml(filename, out, removeUselessWords);//Ȼ�������ļ�filename������������Ϣ����������
		cout << "finishing "<< url<<endl;
	}
}

void WebsiteProcessor::extractInfo(CharString& inputFile, CharString& outputFile, bool removeUselessWords){
	//����inputFile�е�������ҳ��������洢��outputFile�У�ʧ�ܵĻ�����false
	//���removeUselessWordsΪtrue����ִʽ���ͻ�ɾ�����ôʣ�Ϊfalse���������ô�
	ifstream in; in.open(inputFile.data());//�򿪴洢��ҳurl���ļ�
	if(!in){
		cout << "error in open " << inputFile <<endl;
		exit(-1);
	}
	ofstream out; out.open(outputFile.data());//����ȡ��Ϣ�洢���ļ�
	if(!out){
		cout << "error in open " << outputFile <<endl;
		exit(-1);
	}
	process(in, out, removeUselessWords);//���д���
	in.close(); out.close();//�رմ򿪵��ļ�
}

void WebsiteProcessor::initDictionary(){//��ʼ���ʿ�
	dictionary = make_shared<Dictionary>();//�½�һ���ʿ�
	dictionary->init();//�ʿ��ʼ��
}

CharStringLink WebsiteProcessor::divideWords(const CharString& sentence, bool removeUselessWords){//�Ծ��ӽ��зִ�
	//���removeUselessWordsΪtrue����ִʽ���ͻ�ɾ�����ôʣ�Ϊfalse���������ô�
	if(!dictionary){
		exit(-1);
	}
	return *dictionary->divideSentence(sentence, removeUselessWords);
}
