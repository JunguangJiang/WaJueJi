#include "stdafx.h"
#include "DocList.h"
#include <limits>
#include <iostream>

DocNode::DocNode(int DocID, int Times, DocNodePosi prev, DocNodePosi succ):
	DocID(DocID), Times(Times), prev(prev), succ(succ), n(1){}

int DocNode::totalWeight(){
	if(Times == INT_MAX) return INT_MAX;
	else if(Times == INT_MIN) return INT_MIN;
	else return weight * n + Times; 
}//������Ȩ�أ��ĵ����������Ȩ�ؽ�������


DocNodePosi DocNode::insertAsNext(int DocID, int Times){
	DocNodePosi p = new DocNode(DocID, Times, this, this->succ);//����һ���½ڵ㣬���뵽��ǰ�ڵ�ĺ��
	if(succ) succ->prev = p; succ = p;
	return p;//�����´����Ľڵ�
}

DocNodePosi DocNode::insertAsPred(int DocID, int Times){
	DocNodePosi p = new DocNode(DocID, Times, this->prev, this);//����һ���½ڵ㣬���뵽��ǰ�ڵ��ǰ��
	if(prev) prev->succ = p; prev = p;
	return p;//�����´����Ľڵ�
}


DocList::DocList(int TermID):TermID(TermID), m_times(0), m_size(0){
	header = new DocNode(-1, INT_MAX);//ͷ����DocIDΪ-1,���ʳ��ִ���Ϊ�������ڵ㶼ֻ����ͷ���֮�����
	trailer = new DocNode(-1, INT_MIN);//β�ڵ��DocIDΪ-1�����ʳ��ֵĴ���Ϊ����С
	header->succ = trailer; trailer->prev = header;
}


DocList::~DocList(void){
	DocNodePosi p = header->succ;//������ͷ���ĺ��
	while(p != trailer){
		p->prev->succ = p->succ; p->succ->prev = p->prev;//��������ժ��
		p->succ = p->prev = NULL;
		delete p;//Ȼ��ɾ��
		p = header->succ;
	}//ֱ����ֻʣ��ͷβ�ڵ�
	header->prev = trailer->succ = NULL;
	delete header; delete trailer;//ɾ��ͷβ�ڵ�
}

void DocList::swap(DocNodePosi p1, DocNodePosi p2){
	std::swap(p1->DocID, p2->DocID);
	std::swap(p1->Times, p2->Times);
	std::swap(p1->n, p2->n);
}

/*
DocNodePosi DocList::Add(int DocID){//����ĵ�
	DocNodePosi p = NULL;
	for(p = header->succ; p != trailer && p->DocID != DocID; p = p->succ){//������������
	}
	this->m_times++;//�޸��ĵ�����ĵ����ܴ���
	if(p == trailer){//���ԭ�Ȳ������ĵ�DocID
		this->m_size ++;//�ĵ���������
		return trailer->insertAsPred(DocID, 1);//��DocID��Ϊ���һ���ڵ��������
	}else{//���ԭ�ȴ����ĵ�
		p->Times++;//���������
		DocNodePosi curr = p->prev;
		while(curr->totalWeight() < p->totalWeight()){//ֻҪcurr�ĵ��ʳ��ִ���С��p
			curr = curr->prev;//�ͼ�����ǰ��
		}//��ֹʱ��Ȼ��curr->Times >= p->Times �� curr->succ->Times<p->Times
		swap(curr->succ, p); //ֻ��Ҫ���������������ɻָ�����
		return curr->succ;//���ش�ʱ�ĵ�λ��
	}
}
*/

DocNodePosi DocList::Add(int DocID, int Times){//����ĵ�
	DocNodePosi p = NULL;
	for(p = header->succ; p != trailer && p->DocID != DocID; p = p->succ){//������������
	}
	this->m_times++;//�޸��ĵ�����ĵ����ܴ���
	if(p == trailer){//���ԭ�Ȳ������ĵ�DocID
		this->m_size ++;//�ĵ���������
		p = trailer->insertAsPred(DocID, Times);//��DocID��Ϊ���һ���ڵ��������
	}else{//���ԭ�ȴ����ĵ�
		p->Times+=Times;//���������		
	}
	return adjust(p);//���ص���������λ��
}


/*
DocNodePosi DocList::Add(int DocID, int Times){//����ĵ�
	DocNodePosi p = NULL;
	for(p = header; p->Times>= Times; p = p->succ){
		if(p->DocID == DocID) return NULL;//�������ԭ���Ѿ�������ͬDocID���ĵ����򷵻ؿգ����ʧ��
	}
	//����header->Times > Times > tailer->Times,���ѭ����Ȼ��(header, tailer]����ֹ
	this->m_times += Times;//�޸��ĵ�����ĵ����ܴ���
	this->m_size ++;
	return p->prev->insertAsNext(DocID, Times);//��ʱp->prev�Ǵ������ڵ���Times����С�ߣ����������ĵ�
}
*/

DocNodePosi DocList::Search(int DocID){//��ѯ�ĵ�
	DocNodePosi p = NULL;
	for(p = header; p != trailer; p = p->succ){//���������ĵ���ͷβ�ڵ�ز�ƥ�䣩
		if(p->DocID == DocID) break; //����ڵ�ǰ�ĵ����У����˳�ѭ��
	}
	return (p->DocID == DocID) ? p : NULL;//���û���ҵ��ĵ����򷵻ؿ�
}

DocNodePosi DocList::Edit(int DocID, int Times){//�޸��ĵ�
	DocNodePosi p = Search(DocID); 
	if(!p){//���û���������ĵ�
		return Add(DocID, Times);//ת��ֱ�Ӽ������ĵ�
	}else{//����������ĵ�
		p->Times = Times;//�����޸�
		return adjust(p);//���ص������λ��
	}
}

/*
DocNodePosi DocList::Edit(int DocID, int Times){//�޸��ĵ�
	DocNodePosi p = NULL; 
	int oldTimes = Remove(DocID);//���ȳ���ɾ���ĵ�
	if(oldTimes > 0){//����ĵ�����
		p = Add(DocID, Times);//�������һ���µ��ĵ�
	}
	return p;//������ͨ��p�Ƿ���ڣ��ж��޸��Ƿ�ɹ�
}
*/

int DocList::Remove(int DocID){//ɾ���ĵ�
	DocNodePosi p = Search(DocID);//���Ȳ�ѯ�ĵ�
	int oldTimes = 0;//ɾ��ǰ�ĵ��е��ʳ��ִ���
	if(p){//����ĵ�����
		oldTimes = p->Times;
		p->prev->succ = p->succ; p->succ->prev = p->prev;//�����������ժ��
		p->succ = p->prev = NULL;
		this->m_times -= oldTimes;//�޸��ĵ�����ĵ����ܴ���
		this->m_size--;
		delete p;
	}
	return oldTimes;//������ͨ���жϱ�ɾ���ĵ��Ĵ����Ƿ����0���ж�ɾ���Ƿ�ɹ�
}

void DocList::debug() const{
	DocNodePosi p = NULL;
	for(p = header->succ; p != trailer; p = p->succ){//���������ĵ���ͷβ�ڵ�ز�ƥ�䣩
		std::cout << "(" << p->DocID << ", " << p->Times<<")  " ; 
	}
}

DocNodePosi DocList::adjust(DocNodePosi p){
	//�����ڵ�pʹ������ assert:�޷�����p->prev<p ��p>p->succ�����������������һ��ʧ��
	//assert��pΪ��ͷβ�ڵ�
	if(p->prev->totalWeight() < p->totalWeight()){
		DocNodePosi prev = p->prev;
		while(prev->totalWeight() < p->totalWeight()){//ֻ�е�ǰ��С��pʱ����������
			swap(p, prev);//�������ߵ�������
			p = prev;//��ʱ��Ҫ���prev�Ƿ�����
			prev = p->prev;
		}//��prev=headerʱ����Ȼ��ֹ
	}else if(p->succ->totalWeight() > p->totalWeight()){
		DocNodePosi succ = p->succ;
		while(succ->totalWeight() > p->totalWeight()){//ֻ�е���̴���pʱ����������
			swap(p, succ);//�������ߵ�������
			p = succ;//��ʱ��Ҫ���prev�Ƿ�����
			succ = p->succ;
		}//��succ = trailerʱ����Ȼ��ֹ
	}
	//�����������p->prev >= p >= p->succ,�Ѿ�����
	return p;//���ص������λ��
}
