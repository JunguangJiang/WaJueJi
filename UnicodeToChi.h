#pragma once

#include <codecvt>
#include "CharString.h"
typedef std::codecvt_byname<wchar_t, char, mbstate_t> WCHAR_GBK;

class UnicodeToChi//ʵ��unicode���뵽���ֵ�ת��
{
private:
	//CharString decode(const CharString& word);//��һ��������н���
public:
	UnicodeToChi(void);
	~UnicodeToChi(void);
	CharString decode(const CharString& sentence);//��һ�����ӽ��н���
};

