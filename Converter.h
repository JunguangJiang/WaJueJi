#ifndef _CONVERT_H
#define _CONVERT_H

#include <codecvt>
#include "CharString.h"

int inline stringToValue(const CharString& string);//���һ���ַ�������ֵ��С

CharString UnicodeToChinese(const CharString& sentence);//��Unicode����ת��Ϊ����

#endif