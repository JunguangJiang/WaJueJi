#include "stdafx.h"
#include "BBST.h"

TermWord::TermWord(CharString Term, int TermID):
	Term(Term), TermID(TermID){
		docList = new DocList(TermID);//����һ���µ��ĵ�����
}

BBST::BBST(void)
{
}


BBST::~BBST(void)
{
}
