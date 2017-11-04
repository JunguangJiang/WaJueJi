#pragma once

#include <codecvt>
#include "CharString.h"
typedef std::codecvt_byname<wchar_t, char, mbstate_t> WCHAR_GBK;

class UnicodeToChi//实现unicode编码到汉字的转化
{
private:
	//CharString decode(const CharString& word);//将一个词语进行解码
public:
	UnicodeToChi(void);
	~UnicodeToChi(void);
	CharString decode(const CharString& sentence);//将一个句子进行解码
};

