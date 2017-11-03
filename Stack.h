#pragma once

#define minStackSize 10//��ʼ��ʱ�����ݹ�ģ

template <typename T>
class Stack//ջ�ṹ
{
private:
	T* _elem;//������
	int _size;//��ģ
	int _capacity;//����

public:
	Stack(void);
	~Stack(void);
	void push(T const& e);//ѹջ
	void pop();//��ջ
	T& top();//��ȡջ��Ԫ��
	bool empty();//�ж�ջ���Ƿ�Ϊ��
	void expand();//ջ�ռ䲻��ʱ����

	void print();//��ӡջ�е�����Ԫ��
};

#include <iostream>

template <typename T>
Stack<T>::Stack(void){
	_capacity = minStackSize;
	_elem = new T[_capacity];
	_size = 0;//��ʼʱ��ģΪ0
};

template <typename T>
Stack<T>::~Stack(void){
	if(_elem){
		delete [] _elem; _elem = NULL;
	}
}

template <typename T>
void Stack<T>::expand(){//ջ�ռ䲻��ʱ����
	if(_size < _capacity) return;//��δ��Աʱ��������
	_capacity <<= 1;//�����ӱ�
	T* oldElem = _elem;//����һ���µĿռ�
	_elem = new T[_capacity];
	for(int i=0; i<_size; i++){
		_elem[i] = oldElem[i];//��������Ԫ��
	}
	delete [] oldElem; oldElem = NULL;//ɾ��ԭ���Ŀռ�
}

template <typename T>
void Stack<T>::push(T const& e){
	expand();
	_elem[_size++] = e;
}

template <typename T>
void Stack<T>::pop(){
	_size--;
}

template <typename T>
T& Stack<T>::top(){
	return _elem[_size-1];
}

template <typename T>
bool Stack<T>::empty(){
	return _size<=0;
}


template <typename T>
void Stack<T>::print(){
	for(int i=0; i<_size; i++){
		std::cout << _elem[i] << endl;
	}
}

