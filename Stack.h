#pragma once

#define minStackSize 10//初始化时的数据规模

template <typename T>
class Stack//栈结构
{
private:
	T* _elem;//数据区
	int _size;//规模
	int _capacity;//容量

public:
	Stack(void);
	~Stack(void);
	void push(T const& e);//压栈
	void pop();//退栈
	T& top();//获取栈顶元素
	bool empty();//判断栈顶是否为空
	void expand();//栈空间不足时扩容

	void print();//打印栈中的所有元素
};

#include <iostream>

template <typename T>
Stack<T>::Stack(void){
	_capacity = minStackSize;
	_elem = new T[_capacity];
	_size = 0;//初始时规模为0
};

template <typename T>
Stack<T>::~Stack(void){
	delete [] _elem;
}

template <typename T>
void Stack<T>::expand(){//栈空间不足时扩容
	if(_size < _capacity) return;//尚未满员时不必扩容
	_capacity <<= 1;//容量加倍
	T* oldElem = _elem;//开辟一个新的空间
	_elem = new T[_capacity];
	for(int i=0; i<_size; i++){
		_elem[i] = oldElem[i];//复制数据元素
	}
	delete [] oldElem;//删除原来的空间
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

