#include "stdafx.h"
#include "BBST.h"

TermWord::TermWord(CharString Term, int TermID):
	Term(Term), TermID(TermID){
		docList = new DocList(TermID);//创建一个新的文档链表
}

BBST::BBST(void)
{
}


BBST::~BBST(void)
{
}
