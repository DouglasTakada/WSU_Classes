#include "header.h"

template<class T>
class AVLNode {
public:
    //constructors and destructors
    AVLNode();
    AVLNode(T newData);
    ~AVLNode();

    //getters
    T getData(void);
    int getHeight(void);
    int findHeight(AVLNode<T>* &root);//------
    AVLNode<T>* & getLPtr(void);
    AVLNode<T>* & getRPtr(void);


    //setters
    void setData(T newData);
    void setHeight(int newHeight);
    void setLPtr(AVLNode<T>* newPtr);
    void setRPtr(AVLNode<T>* newPtr);

private:
    T data;
    int height;
    AVLNode<T>* LPtr;
    AVLNode<T>* RPtr;
};

template<class T>
int AVLNode<T>::findHeight(AVLNode<T>* &root){/////////////////////
    if (root == nullptr) {
        return -1;
    }
    else {
        return 1 + max(findHeight(root->getLPtr()), findHeight(root->getRPtr()));
    }
}

template <class T>
AVLNode<T>::AVLNode() {//////////////////
    this->data = 0;
    this->height = 0;
    this->LPtr = nullptr;
    this->RPtr = nullptr;
}

template <class T>
AVLNode<T>::AVLNode(T newData) {/////////////////
    this->data = newData;
    this->height = 0;
    this->LPtr = nullptr;
    this->RPtr = nullptr;
}

template <class T>
AVLNode<T>::~AVLNode() {////////////////////
    this->data = -1;
    this->height = -1;
    this->LPtr = nullptr;
    this->RPtr = nullptr;
}

template <class T>
T AVLNode<T>::getData(void) {/////////////
    return this->data;
}

template <class T>
int AVLNode<T>::getHeight(void) {//////////////////
    return this->height;
}

template <class T>
AVLNode<T>* & AVLNode<T>::getLPtr(void) {///////////////////
    return this->LPtr;
}

template <class T>
AVLNode<T>* & AVLNode<T>::getRPtr(void) {//////////////
    return this->RPtr;
}

template <class T>
void AVLNode<T>::setData(T newData) {/////////////////////
    this->data = newData;
}

template <class T>
void AVLNode<T>::setHeight(int newHeight) {////////////////////////
    this->height = newHeight;
}

template <class T>
void AVLNode<T>::setLPtr(AVLNode<T>* newPtr) {////////////////
    this->LPtr = newPtr;
}

template <class T>
void AVLNode<T>::setRPtr(AVLNode<T>* newPtr) {///////////////////
    this->RPtr = newPtr;
}