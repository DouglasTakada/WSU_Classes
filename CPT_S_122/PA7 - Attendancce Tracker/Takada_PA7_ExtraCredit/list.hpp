#include "node.hpp"

template <class T>
class list {
public:
	list();
	~list();

	node<T>* getPHead();
	void setPHead(node<T>* newPtr);
	void insertFront(T& newData);
	bool isEmpty();

private:
	node<T>* pHead;
};

template <class T>
list<T>::list() {
	pHead = nullptr;
}

template <class T>
list<T>::~list() {

}

template <class T>
node<T>* list<T>::getPHead() {
	return pHead;
}

template <class T>
void list<T>::setPHead(node<T>* newPtr) {
	pHead = newPtr;
}

template <class T>
void list<T>::insertFront(T& newData) {
	node<T>* newNode = new node<T>(newData);
	if (pHead == nullptr) {
		pHead = newNode;
	}
	else {
		newNode->setNxtPtr(pHead);
		pHead = newNode;
	}
}

template <class T>
bool list<T>::isEmpty() {
	return (this->getPHead == nullptr);
}