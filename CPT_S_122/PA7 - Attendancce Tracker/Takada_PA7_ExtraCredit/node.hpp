#include "data.hpp"

template<class T>
class node {
public:
	node(T& newData);//Needs to be T not data type
	~node();

	node<T>* getNxtPtr();
	T* getData();

	void setNxtPtr(node<T>* newPtr);
	void setData(data& newData);

private:
	node<T>* nxtPtr;
	T Data;//needs to be type T instead of data
};

template <class T>
node<T>::node(T& newData) {
	Data = newData;
	nxtPtr = nullptr;
}

template <class T>
node<T>::~node() {

}

template <class T>
node<T>* node<T>::getNxtPtr() {
	return nxtPtr;
}

template <class T>
T* node<T>::getData() {
	return &this->Data;
	//need to use pointer arithmaticcso it doesnt just copy stuff
	//but actually changes the instance of the object
}

template <class T>
void node<T>::setNxtPtr(node<T>* newPtr) {
	nxtPtr = newPtr;
}

template <class T>
void node<T>::setData(data& newData) {
	Data = newData;
}