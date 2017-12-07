#pragma once

#define DocNodePosi DocNode*//�ĵ��ڵ�ָ��
#define weight 10//������Ȩ��ʱ�Ĳ���

class DocNode{//�ĵ�����ڵ�
public:
	int DocID;//���ָõ��ʵ��ĵ�ID
	int Times;//���ʵĳ��ִ���
	int n;//���ĵ������˶��ٸ��ؼ���,�ں����ĵ�����ĺϲ�ʱʹ��
	int totalWeight();//������Ȩ�أ��ĵ����������Ȩ�ؽ�������
	DocNodePosi prev; DocNodePosi succ;//ǰ���ͺ��
	DocNode(int DocID=-1, int Times=0, DocNodePosi prev = NULL, DocNodePosi succ = NULL);//����һ���ڵ�
	DocNodePosi insertAsNext(int DocID, int Times);//��Ϊ��ǰ�ڵ�ĺ�̽ڵ����һ���µĽڵ�
	DocNodePosi insertAsPred(int DocID, int Times);//��Ϊ��ǰ�ڵ��ǰ���ڵ����һ���µĽڵ�
};

class DocList//�ĵ�����
{
	int TermID;//����ID
	DocNodePosi header; DocNodePosi trailer;//����ͷ��㡢β�ڵ�
	int m_size;//����Ĵ�С
	int m_times;//���ʵ��ܴ���
	void swap(DocNodePosi p1, DocNodePosi p2);//���������ĵ��ڵ�������������
	DocNodePosi adjust(DocNodePosi p);
	//�����ڵ�pʹ������ assert:�޷�����p->prev<p ��p>p->succ�����������������һ��ʧ��
	//assert��pΪ��ͷβ�ڵ�
public:
	DocList(int TermID = -1);
	~DocList(void);
	DocNodePosi Add(int DocID, int Times);//����ĵ�,���ز�����ĵ��ڵ�λ��.���ԭ�ȴ����ĵ������Ӧ�Ĵ�������Times
	DocNodePosi Add(int DocID){return Add(DocID, 1);}//����ĵ�(����Ϊ1�������ز�����ĵ��ڵ��λ��.���ԭ�ȴ����ĵ������Ӧ�Ĵ�������1
	DocNodePosi Search(int DocID);//��ѯ�ĵ��������ĵ��ڵ�λ��
	DocNodePosi Edit(int DocID, int Times);//�޸��ĵ������ԭ�ȴ����ĵ����򷵻��޸ĺ���ĵ��ڵ�λ�ã����ԭ�Ȳ������ĵ���������ĵ�
	int Remove(int DocID);//ɾ���ĵ�,�����ĵ��е��ʳ��ִ���
	int Times()const{return m_times;}//�����ĵ�����ĵ����ܴ���
	int Size() const{return m_size;}//�����ĵ�����Ĺ�ģ
	void debug()const;//��ӡ�ĵ��������Ϣ
};



