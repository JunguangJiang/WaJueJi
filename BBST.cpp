#include "stdafx.h"
#include "BBST.h"

TermWord::TermWord(const CharString& Term, int TermID):
	Term(Term), TermID(TermID){
		docList = new DocList(TermID);//����һ���µ��ĵ�����
}

TermWord::~TermWord(){
	delete docList;//ɾ�����ʶ�Ӧ���ĵ�����
}

BinNode::BinNode(const CharString& Term, int TermID, BinNodePosi parent, int height):
	TermWord(Term, TermID),
	parent(parent), lc(NULL), rc(NULL), height(height){}

BinNodePosi BinNode::attachAsLChild(const CharString& Term, int TermID){
	BinNodePosi p = new BinNode(Term, TermID, this);//�Ե�ǰ�ڵ�Ϊ���½�һ���ڵ�
	this->lc = p;//���½ڵ��Ϊ��ǰ�ڵ������
	return p;
}

BinNodePosi BinNode::attachAsRChild(const CharString& Term, int TermID){
	BinNodePosi p = new BinNode(Term, TermID, this);//�Ե�ǰ�ڵ�Ϊ���½�һ���ڵ�
	this->rc = p;//���½ڵ��Ϊ��ǰ�ڵ���Һ���
	return p;
}


BBST::BBST(void):
	m_root(NULL), m_hot(NULL), m_size(0)
{
}


BBST::~BBST(void)
{
	removeSubTree(m_root);//ɾ��ȫ��
}

BinNodePosi& BBST::Search(const CharString& termWord){//�����ڵ�
	m_hot = NULL;
	return searchIn(m_root, termWord);//������ȫ�����������
}

BinNodePosi& BBST::searchIn(BinNodePosi& r, const CharString& termWord){
	if( r == NULL || r->Term == termWord ){//����ڵ�ǰ�ڵ�(���߼���Ŀսڵ�)����
		return r;//��ֱ�ӷ��ص�ǰ�ڵ�
	}else{//����
		m_hot = r;//��¼�ȵ㣬Ȼ����ݽڵ�r�ĵ��ʴ�С����
		return r->Term > termWord ? searchIn(r->lc, termWord) : searchIn(r->rc, termWord);//������������Ѱ��
	}
}


inline int max(int a, int b){//�������������ֵ
	return (a<b)?b:a;
}

void BBST::updateHeight(BinNodePosi v){//���½ڵ�v������
	v->height = max( height(v->lc), height(v->rc) ) + 1;//
}

BinNodePosi BBST::Insert(const CharString& termWord){//����ڵ�
	BinNodePosi& v = Search(termWord); 
	if(v) return v;//�Ȳ�ѯԭ�����Ƿ����е���termWord,ȷ��ԭ���ʲ�����
	BinNodePosi x = v = new BinNode(termWord, -1, m_hot);//�½�һ���ڵ㣬����ΪtermWord,TermID=-1,���ڵ�Ϊm_hot
	m_size++;
	for(BinNodePosi g = m_hot; g; g=g->parent){//�ӵ�ǰ�ڵ�ĸ��ڵ�m_hot����,����׷Ѱ
		if(!AVLBalanced(g)){//�����ǰ�ڵ�g AVLʧ�⣬��
			if(IsRoot(g)){//���gԭ���Ǹ��ڵ�
				m_root = Adjust(g);//��������������ӵ�����
			}else{
				BinNodePosi gg = g->parent;
				if(IsLChild(g)){//���gԭ��������
					gg->lc = Adjust(g);//��������������ӵ�gԭ�ȸ��ڵ������
				}else{//���gԭ�����Һ���
					gg->rc = Adjust(g);//��������������ӵ���ԭ�ȸ��ڵ���Һ���
				}
			}
			//�˺�ֲ������ĸ߶ȱ�Ȼ��ԭ
			break;
		}else{//�����ǰ�ڵ�gû��ʧ��
			updateHeight(g);//���Ǹ߶�Ҳ�п��ܷ����ı�
		}
	}
	return x;//��ʱv->Term==termWord��Ȼ����������AVLƽ������Ҳ�õ�������
}

void BBST::connect34(BinNodePosi a, BinNodePosi b, BinNodePosi c, 
		BinNodePosi t1, BinNodePosi t2, BinNodePosi t3, BinNodePosi t4){
	//3+4�ع������ڽڵ����ת���� assert:a,b,c�ǿ�
			a->lc = t1; if(t1) t1->parent = a;
			a->rc = t2; if(t2) t2->parent = a;
			updateHeight(a);
			c->lc = t3; if(t3) t3->parent = c;
			c->rc = t4; if(t4) t4->parent = c;
			updateHeight(c);
			b->lc = a; a->parent = b;
			b->rc = c; c->parent = b;
			updateHeight(b);
			//�ڵ�b�͸��ڵ�����ӽ��ɵ������������
}

BinNodePosi BBST::Adjust(BinNodePosi g){//��ʧ��ڵ�g������ת����,���ص���������������
	BinNodePosi p = tallerChild(g); BinNodePosi v = tallerChild(p);//�ҵ�ʧ��ڵ�ϸߵĶ��Ӻ�����
	BinNodePosi gg = g->parent;
	if(IsLChild(p)){//p������
		if(IsLChild(v)){//v������
			connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
			p->parent = gg;//�ڵ�p��Ϊ������������
			return p;
		}else{//��p�����ӣ�v���Һ���
			connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
			v->parent = gg;//�ڵ�v��Ϊ������������
			return v;
		}
	}else{//p���Һ���
		if(IsLChild(v)){//v������
			connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
			v->parent = gg;//�ڵ�v��Ϊ������������
			return v;
		}else{//��p���Һ��ӣ�v���Һ���
			connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
			p->parent = gg;//�ڵ�p��Ϊ������������
			return p;
		}
	}
	//Note:�ϲ�ڵ㵽�����������ɵ��������
}

void BBST::debug(BinNodePosi p){
	if(!p) return; 
	std::cout <<"Word:"<< p->Term<<" height:"<<p->height << " lc:";
	if(p->lc) 
		std::cout << p->lc->Term;
	else
		std::cout << "NULL";
	std::cout << " rc:";
	if(p->rc)
		std::cout << p->rc->Term;
	else
		std::cout << "NULL";
	std:: cout << " docList: "; p->docList->debug();
	std::cout<<std::endl;
	debug(p->lc);
	debug(p->rc);
}

void BBST::removeSubTree(BinNodePosi v){
	if(!v) return;//ȷ���ڵ�v�ǿ�
	removeSubTree(v->lc);v->lc = NULL;//��ɾ��������
	removeSubTree(v->rc);v->rc = NULL;//Ȼ��ɾ��������
	v->parent = NULL; //�жϸ��ڵ�ָ��
	delete v;
}

BinNodePosi BBST::succ(BinNodePosi v){//Ѱ�ҽڵ�v�ĺ��
	if(!IsValid(v)) return NULL;//����ڵ�v���Ϸ������ؿ�
	BinNodePosi x;
	if(HasRChild(v)){//����ڵ�v��������
		for(x = v->rc; HasLChild(x) ; x = x->lc){}//�ҵ��������������µĽڵ�x
		return x;
	}else{//����ڵ�v������Ϊ��
		for(x = v; IsRChild(x); x = x->parent){}//ֻҪx���Һ���,�ͼ�������Ѱ��
		//����xΪ�ջ���xΪ���ڵ����xΪ���ӣ����˳�ѭ��
		if(!IsLChild(x)) 
			return NULL;//����ڵ�xΪ��(��vΪ����������xΪ�����򷵻ؿ�
		else //����xΪ����
			return x->parent;//����x�ĸ��ڵ㼴�� 
	}
}

bool BBST::Remove(const CharString& termWord){//ɾ������ΪtermWord�Ľڵ㣬����false�����������в����ڸõ���
	BinNodePosi& v = Search(termWord); if(!v) return false;//ȷ�Ͻڵ����
	BinNodePosi w = v;//ʵ�ʱ�ɾ���Ľڵ�w����ֵͬv
	BinNodePosi s = NULL;//�ڵ�w�Ľ�����
	if(!HasLChild(v)){//����ڵ�vû��������
		s = v->rc;//��v�Ľ�����Ϊ������
	}else if(!HasRChild(v)){//����ڵ�vû��������
		s = v->lc;//��v�Ľ�������������
	}else{//����ڵ�vͬʱ����������
		w = succ(v);//��ʵ�ʱ�ɾ���ڵ�wΪ�ڵ�v�ĺ�̽ڵ㣨w�ض��ǿ��ұض�û����������
		std::swap(w->Term, v->Term); std::swap(w->TermID, v->TermID);//�����ߵ��������������˺�
		s = w->rc;//ת��ɾ���ڵ�w
		m_hot = w->parent;//���ı�ɾ���ڵ�ĸ��ڵ�
	}
	if(IsRoot(w)){//����ڵ�w�Ǹ�,��s��Ϊ�µĸ�
		m_root = s; 
	}else{
		if(IsLChild(w)){//����ڵ�w��������
			w->parent->lc = s;
		}else{//����ڵ�w��������
			w->parent->rc = s;
		}
	}
	if(s) s->parent = w->parent;//�����Ѿ���w����
	w->parent = w->lc = w->rc = NULL; delete w; w = NULL;//ɾ���ڵ�w

	//�˺�BBST���ܷ���ʧ��
	for(BinNodePosi g = m_hot; g; g = g->parent){//����׷��w�����Ƚڵ�
		if(!AVLBalanced(g)){//���������gʧ��
			if(IsRoot(g)){//���gԭ���Ǹ��ڵ�
				g =  m_root = Adjust(g);//��������������ӵ�����
			}else{
				BinNodePosi gg = g->parent;
				if(IsLChild(g)){//���gԭ��������
					g = gg->lc = Adjust(g);//��������������ӵ�gԭ�ȸ��ڵ������
				}else{//���gԭ�����Һ���
					g = gg->rc = Adjust(g);//��������������ӵ�gԭ�ȸ��ڵ���Һ���
				}
			}
		}
		updateHeight(g);//�˺�g�ĸ߶ȼ��٣��ϲ�ڵ���Ȼ����ʧ��
	}
	return true;
}