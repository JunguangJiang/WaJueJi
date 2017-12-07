#pragma once

#include "CharString.h"
#include "DocList.h"


class TermWord{//����
public:
	CharString Term;//����
	int TermID;//����ID
	DocList *docList;//�ĵ�����ָ��
	int DF()const{return docList->Size();}//���ʳ����ڶ���ƪ������
	int Occur()const{return docList->Times();}//���ʵ��ܳ��ִ���
	TermWord(const CharString& Term, int TermID = -1);
	~TermWord();
};

#define BinNodePosi BinNode*//���ʵ�ָ��

class BinNode: public TermWord{//�����������ڵ�,�̳��Ե�����
public:
	BinNodePosi lc; BinNodePosi rc; BinNodePosi parent;//���Һ��ӡ����ڵ�
	int height;//�ڵ����
	BinNode(const CharString& Term, int TermID = -1, BinNodePosi parent = NULL, int height = 1);
	BinNodePosi attachAsLChild(const CharString& Term, int TermID = -1);//��Ϊ��ǰ�ڵ������
	BinNodePosi attachAsRChild(const CharString& Term, int TermID = -1);//��Ϊ��ǰ�ڵ���Һ���
};

class BBST//ƽ�����������
{
	BinNodePosi m_root;//���ڵ�
	BinNodePosi m_hot;//�ȵ㣬��¼��������ĸ��ڵ�
	int m_size;//ƽ������������Ĺ�ģ
	BinNodePosi& searchIn(BinNodePosi& r, const CharString& termWord);//����rΪ���������������Ƿ��е���termWord
	void updateHeight(BinNodePosi v);//���½ڵ�v������,assert:v��Ȼ�ǿ�
	int inline height(BinNodePosi v) const{return v?v->height:0;}
	//�սڵ������Ϊ0��Ҷ�ڵ������Ϊ1������ڵ������Ϊmax{�������ߣ��Һ�������}+1
	int inline AVLFac(BinNodePosi v)const {return height(v->lc)-height(v->rc);}//�ڵ�v��AVLƽ��ϵ��,assert:v�ǿ�
	bool inline AVLBalanced(BinNodePosi v) const{return abs(AVLFac(v)) < 2;}
	//�ж�ĳ���ڵ��Ƿ�����AVL����ƽ������,assert:v��Ȼ�ǿ�
	bool inline IsValid(BinNodePosi v) const {return v?true:false;}//�жϽڵ�v�Ƿ����
	bool inline IsRoot(BinNodePosi v)const {return IsValid(v) && v->parent == NULL;}//�ж��Ƿ�Ϊ����
	bool inline IsLeaf(BinNodePosi v) const{return IsValid(v) && !v->lc && !v->rc;}//�жϽڵ�v�Ƿ�ΪҶ�ӽڵ�
	bool inline IsLChild(BinNodePosi v) const {return IsValid(v) && !IsRoot(v) && ( v->parent->lc == v ); }//�ж��Ƿ�Ϊ����
	bool inline IsRChild(BinNodePosi v) const {return IsValid(v) && !IsRoot(v) && ( v->parent->rc == v ); }//�ж��Ƿ�Ϊ�Һ��� 
	bool inline HasLChild(BinNodePosi v) const {return IsValid(v) && v->lc;}//�ж��Ƿ�����
	bool inline HasRChild(BinNodePosi v) const {return IsValid(v) && v->rc;}//�ж��Ƿ����Һ���
	void connect34(BinNodePosi a, BinNodePosi b, BinNodePosi c, 
		BinNodePosi t1, BinNodePosi t2, BinNodePosi t3, BinNodePosi t4);
	//3+4�ع������ڽڵ����ת���� assert:a,b,c�ǿ�
	inline BinNodePosi tallerChild(BinNodePosi p)const{return AVLFac(p)<0?p->rc:p->lc;}//�ҵ��ڵ�p�ϸߵĺ��� assert:p�ǿ�
	void removeSubTree(BinNodePosi v);//ɾ���Խڵ�vΪ����������
	BinNodePosi succ(BinNodePosi v);//Ѱ�ҽڵ�v�ĺ��
public:
	BBST(void);
	~BBST(void);
	BinNodePosi& Search(const CharString& termWord);//���ҽڵ�,���ز��ҵ�λ�ã�ʧ�ܷ��ؿ�
	BinNodePosi Insert(const CharString& termWord);//����ڵ㣬���ؽڵ�ĵ��ʱ�Ȼ��termWord
	BinNodePosi Adjust(BinNodePosi p);//�Խڵ�g������ת����,���ص�������������ڵ� Note:�ϲ�ڵ㵽�����������ɵ��������
	bool Remove(const CharString& termWord);//ɾ������ΪtermWord�Ľڵ㣬����false�����������в����ڸõ���
	//Edit,�༭ĳ�ڵ�����й��ܶ�����Search������ɣ����û�б�Ҫʵ��
	int size()const{return m_size;}//��ģ
	BinNodePosi root() const{return m_root;}//����
	bool isEmpty()const{return !m_root;}//�ж����Ƿ�Ϊ��
	void debug(BinNodePosi p);//���Դ�ӡ����ڵ�p����Ϣ
};

