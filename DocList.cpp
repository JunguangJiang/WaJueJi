#include "stdafx.h"
#include "DocList.h"
#include <limits>
#include <iostream>

DocNode::DocNode(int DocID, int Times, DocNodePosi prev, DocNodePosi succ):
	DocID(DocID), Times(Times), prev(prev), succ(succ){}

DocNodePosi DocNode::insertAsNext(int DocID, int Times){
	DocNodePosi p = new DocNode(DocID, Times, this, this->succ);//创建一个新节点，插入到当前节点的后继
	if(succ) succ->prev = p; succ = p;
	return p;//返回新创建的节点
}

DocList::DocList(int TermID):TermID(TermID), m_times(0), m_size(0){
	header = new DocNode(-1, INT_MAX);//头结点的DocID为-1,单词出现次数为无穷大，则节点都只能在头结点之后插入
	trailer = new DocNode(-1, INT_MIN);//尾节点的DocID为-1，单词出现的次数为无穷小
	header->succ = trailer; trailer->prev = header;
}


DocList::~DocList(void){
	DocNodePosi p = header->succ;//反复将头结点的后继
	while(p != trailer){
		p->prev->succ = p->succ; p->succ->prev = p->prev;//从链表中摘除
		p->succ = p->prev = NULL;
		delete p;//然后删除
		p = header->succ;
	}//直至，只剩下头尾节点
	header->prev = trailer->succ = NULL;
	delete header; delete trailer;//删除头尾节点
}

DocNodePosi DocList::Add(int DocID, int Times){//添加文档
	DocNodePosi p = NULL;
	for(p = header; p->Times>= Times; p = p->succ){
		if(p->DocID == DocID) return NULL;//如果发现原先已经存在相同DocID的文档，则返回空，添加失败
	}
	//由于header->Times > Times > tailer->Times,因此循环必然在(header, tailer]处终止
	this->m_times += Times;//修改文档链表的单词总次数
	this->m_size ++;
	return p->prev->insertAsNext(DocID, Times);//此时p->prev是次数大于等于Times中最小者，在其后添加文档
}

DocNodePosi DocList::Search(int DocID){//查询文档
	DocNodePosi p = NULL;
	for(p = header; p != trailer; p = p->succ){//遍历所有文档（头尾节点必不匹配）
		if(p->DocID == DocID) break; //如果在当前文档命中，则退出循环
	}
	return (p->DocID == DocID) ? p : NULL;//如果没有找到文档，则返回空
}

DocNodePosi DocList::Edit(int DocID, int Times){//修改文档
	DocNodePosi p = NULL; 
	int oldTimes = Remove(DocID);//首先尝试删除文档
	if(oldTimes > 0){//如果文档存在
		p = Add(DocID, Times);//重新添加一个新的文档
	}
	return p;//调用者通过p是否存在，判断修改是否成功
}

int DocList::Remove(int DocID){//删除文档
	DocNodePosi p = Search(DocID);//首先查询文档
	int oldTimes = 0;//删除前文档中单词出现次数
	if(p){//如果文档存在
		oldTimes = p->Times;
		p->prev->succ = p->succ; p->succ->prev = p->prev;//将其从链表中摘除
		p->succ = p->prev = NULL;
		this->m_times -= oldTimes;//修改文档链表的单词总次数
		this->m_size--;
		delete p;
	}
	return oldTimes;//调用者通过判断被删除文档的次数是否大于0，判断删除是否成功
}

void DocList::print(){
	DocNodePosi p = NULL;
	for(p = header->succ; p != trailer; p = p->succ){//遍历所有文档（头尾节点必不匹配）
		std::cout << "(" << p->DocID << ", " << p->Times<<")" << std::endl; 
	}
}




