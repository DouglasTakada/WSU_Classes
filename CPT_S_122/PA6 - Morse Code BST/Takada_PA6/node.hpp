#pragma once

#include "data.hpp"

template <class T1, class T2>
class Node {
public:
	//Constructor
	Node(T1 &newChar, T2 &newCode);
	//Destructor
	~Node();
	//Getters
	Node<T1, T2>* getLPtr()const;
	Node<T1, T2>* getRPtr()const;
	Data<T1, T2>* getData()const;
	//Setters
	void setLPtr(Node<T1, T2>* newPtr);
	void setRPtr(Node<T1, T2>* newPtr);
	void setData(Data<T1, T2>* newptr);

private:
	Node<T1, T2>* lPtr;
	Node<T1, T2>* rPtr;
	Data<T1, T2>* data;
};

//Constructor
template <class T1, class T2>
Node<T1, T2>::Node(T1 &newChar, T2 &newCode) {//Allocate space for Data
	Data<T1, T2>* dat = new Data<T1, T2>(newChar, newCode);
	this->data = dat;
	this->lPtr = nullptr;
	this->rPtr = nullptr;
}
//Destructor
template <class T1, class T2>
Node<T1, T2>::~Node() {

}
//Getters
template <class T1, class T2>
Node<T1, T2>* Node<T1, T2>::getLPtr()const {
	return this->lPtr;
}
template <class T1, class T2>
Node<T1, T2>* Node<T1, T2>::getRPtr()const {
	return this->rPtr;
}
template <class T1, class T2>
Data<T1, T2>* Node<T1, T2>::getData()const {
	return this->data;
}
//Setters
template <class T1, class T2>
void Node<T1, T2>::setLPtr(Node<T1, T2>* newPtr) {
	this->lPtr = newPtr;
}
template <class T1, class T2>
void Node<T1, T2>::setRPtr(Node<T1, T2>* newPtr) {
	this->rPtr = newPtr;
}
template <class T1, class T2>
void Node<T1, T2>::setData(Data<T1, T2>* newPtr) {
	this->data = newPtr;
}