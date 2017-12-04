#pragma once

#define DocNodePosi DocNode*//�ĵ��ڵ�ָ��

class DocNode{//�ĵ�����ڵ�
public:
	int DocID;//���ָõ��ʵ��ĵ�ID
	int Times;//���ʵĳ��ִ���
	DocNodePosi prev; DocNodePosi succ;//ǰ���ͺ��
	DocNode(int DocID=-1, int Times=0, DocNodePosi prev = NULL, DocNodePosi succ = NULL);//����һ���ڵ�
	DocNodePosi insertAsNext(int DocID, int Times);//��Ϊ��ǰ�ڵ�ĺ�̽ڵ����һ���µĽڵ�
};

class DocList//�ĵ�����
{
	int TermID;//����ID
	DocNodePosi header; DocNodePosi trailer;//����ͷ��㡢β�ڵ�
	int m_size;//����Ĵ�С
	int m_times;//���ʵ��ܴ���
public:
	DocList(int TermID = -1);
	~DocList(void);
	DocNodePosi Add(int DocID, int Times);//����ĵ�,���ز�����ĵ��ڵ�λ��
	DocNodePosi Search(int DocID);//��ѯ�ĵ��������ĵ��ڵ�λ��
	DocNodePosi Edit(int DocID, int Times);//�޸��ĵ������ԭ�ȴ����ĵ����򷵻��޸ĺ���ĵ��ڵ�λ�ã����ԭ�Ȳ������ĵ����򷵻ؿ�
	int Remove(int DocID);//ɾ���ĵ�,�����ĵ��е��ʳ��ִ���
	void print();//��ӡ���еĽڵ㣬���ڵ���
	int Times()const{return m_times;}//�����ĵ�����ĵ����ܴ���
	int Size() const{return m_size;}//�����ĵ�����Ĺ�ģ
};

