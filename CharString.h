#pragma once

#define minStringSize 20//�ַ�������С��ģ

#include <string>
#include <iostream>
#include <memory>

class CharString
{
private:
	char* _elem;//������
	int _size;//��ģ
	int _capacity;//����

	void expand();//����
public:
	CharString(int capacity = minStringSize);//�ַ����ĳ�ʼ��������ָ����ʼʱ������
	CharString(const std::string& s);//��stl::stringȥ��ʼ����ǰ�ַ���
	~CharString(void);//��������

	//---------------------------Ҫ��ʵ�ֵķ���----------------------------------------------------
	int indexOf(const CharString& subString, const int pos)const;
	//��Ŀ���ַ�����,��pos��λ�ÿ�ʼ�����Ӵ�,
	//�������Ӵ���һ�γ��ֵ�λ�á�����������Ӵ�,��ô����-1��
	int indexOf(const char* subString, const int pos)const;

	bool subString(int pos, int length, CharString& sub)const;
	//��ԭ�ַ���[left,right)���Ӵ��Ŀ�����sub��	
	
	void concat(const CharString& string);
	//������һ���ַ���string�ӵ���ǰ�ַ�����ĩβ
	
	CharString& operator=(const CharString& string);
	//��string��ֵ����ǰ�ַ���

	//---------------------------�ṩ�Ķ�̬����----------------------------------------------------
	void insert(char c);//���ַ���ĩβ�����ַ�c
	CharString& operator=(const std::string& s);//��stl�е�string������ǰ�ַ���
	bool operator==(const char* string);//�еȣ��жϵ�ǰ�ַ���������һ���ַ������Ƿ����
	char& operator[](int i){return _elem[i];}//���ص�i��Ԫ�ص�����

	friend std::ostream& operator<<(std::ostream& out, const CharString&);//���������
	
	//---------------------------�ṩ�ľ�̬����----------------------------------------------------
	char operator[](int i)const {return _elem[i];}//���ص�i��Ԫ�صĿ���
	int size()const{return _size;}//���ع�ģ
	char* data()const;//����Ԫ�ص�������
};

