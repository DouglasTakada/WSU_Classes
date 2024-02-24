#include "header.hpp"

template<class T1,class T2>
class node
{
public:
    node();

    node(T1 &cmd, T2 &def);

    ~node();

    node<T1,T2>* nextPtr();
    void setnextPtr(node<T1,T2>* newPtr);
    T1 getcmd();
    T2 getdef();

private:
    T1 cmd;
    T2 def;
    node<T1,T2> *next;
};


template <class T1, class T2>
void node<T1, T2>::setnextPtr(node<T1, T2>* newPtr) {
    this->next = newPtr;
}

template <class T1, class T2>
node<T1,T2>::node() {

}

template <class T1, class T2>
node<T1, T2>::node(T1& cmd, T2& def) {
    this->cmd = cmd;
    this->def = def;
    this->next = nullptr;
}


template <class T1, class T2>
node<T1, T2>::~node() {

}

template <class T1, class T2>
node<T1,T2>* node<T1, T2>::nextPtr(){
    return this->next;
}

template <class T1, class T2>
T1 node<T1, T2>::getcmd() {//Use pointer if you want to copy but to return the instance
    return this->cmd;
}

template <class T1, class T2>
T2 node<T1, T2>::getdef() {
    return this->def;
}