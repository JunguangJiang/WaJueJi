#pragma once

#define DocNodePosi DocNode*//文档节点指针

class DocNode{//文档链表节点
public:
	int DocID;//出现该单词的文档ID
	int Times;//单词的出现次数
	DocNodePosi prev; DocNodePosi succ;//前驱和后继
	DocNode(int DocID=-1, int Times=0, DocNodePosi prev = NULL, DocNodePosi succ = NULL);//创建一个节点
	DocNodePosi insertAsNext(int DocID, int Times);//作为当前节点的后继节点插入一个新的节点
};

class DocList//文档链表
{
	int TermID;//单词ID
	DocNodePosi header; DocNodePosi trailer;//链表头结点、尾节点
	int m_size;//链表的大小
	int m_times;//单词的总次数
public:
	DocList(int TermID = -1);
	~DocList(void);
	DocNodePosi Add(int DocID, int Times);//添加文档,返回插入的文档节点位置
	DocNodePosi Search(int DocID);//查询文档，返回文档节点位置
	DocNodePosi Edit(int DocID, int Times);//修改文档，如果原先存在文档，则返回修改后的文档节点位置；如果原先不存在文档，则返回空
	int Remove(int DocID);//删除文档,返回文档中单词出现次数
	void print();//打印所有的节点，用于调试
	int Times()const{return m_times;}//返回文档链表的单词总次数
	int Size() const{return m_size;}//返回文档链表的规模
};

