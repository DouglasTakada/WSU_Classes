#include "AVLNode.h"
template<class T>
class AVLTree {
public:
    //constructors and destructors
    AVLTree();//-----------
    ~AVLTree();//-----------

    
    int height(void);//------------
    void insert(T newValue);//---------
    bool contains(T value);//-----------
    bool validate(void);//-----------
    void printLevelOrder(void);//------
    void printInOrder(void);//--------
    
private:
    //Helper functions
    void AVLDelete(AVLNode<T>* root);//-----------
    bool validateHelper(AVLNode<T>* root);//---------
    void printInOrderHelper(AVLNode<T>* root);//-------
    int heightHelper(AVLNode<T>* root);//---------------
    void insertHelper(AVLNode<T>* &root, T newValue);
    bool containsHelper(AVLNode<T>* root, T value);//---------
    void printLevelOrderHelper(AVLNode<T>* root, int level);//-------
    void rotateWithLeftChild(AVLNode<T>* &root);//-------
    void doubleWithLeftChild(AVLNode<T>* &root);//--------
    void rotateWithRightChild(AVLNode<T>* &root);//--------
    void doubleWithRightChild(AVLNode<T>* &root);//--------

    //data memeber
    AVLNode<T>* root;
};

template<class T>
void AVLTree<T>::printInOrder(void) {
    printInOrderHelper(this->root);
}

template<class T>
void AVLTree<T>::printInOrderHelper(AVLNode<T>* root) {
    if (!root) return;
    printInOrderHelper(root->getLPtr());
    cout << root->getData() << ' ';
    printInOrderHelper(root->getRPtr());
}

template <class T>
void AVLTree<T>::rotateWithLeftChild(AVLNode<T>* &root) {
    AVLNode<T>* temp = root->getLPtr();
    root->setLPtr(temp->getRPtr());
    temp->setRPtr(root);
    root->setHeight(root->getHeight());
    temp->setHeight(temp->findHeight(temp));
    root->setHeight(root->findHeight(root));
    root = temp;
}
template <class T>
void AVLTree<T>::doubleWithLeftChild(AVLNode<T>* &root) {
    rotateWithRightChild(root->getLPtr());
    rotateWithLeftChild(root);
}
template <class T>
void AVLTree<T>::rotateWithRightChild(AVLNode<T>* &root) {
    AVLNode<T>* temp = root->getRPtr();
    root->setRPtr(temp->getLPtr());
    temp->setLPtr(root);
    root->setHeight(root->getHeight());
    temp->setHeight(temp->findHeight(temp));
    root->setHeight(root->findHeight(root));
    root = temp;
}
template <class T>
void AVLTree<T>::doubleWithRightChild(AVLNode<T>* &root) {
    rotateWithLeftChild(root->getRPtr());
    rotateWithRightChild(root);
}



template <class T>
void AVLTree<T>::printLevelOrder(void) {
    int level = root->findHeight(root);
    for (int i = 1; i <= level + 1; i++) {
        printLevelOrderHelper(this->root, i);//Calls my recursive function based on how big the height is
        cout << endl;
    }
}

template <class T>
void AVLTree<T>::printLevelOrderHelper(AVLNode<T>* root, int level) {
    if (root != nullptr) {
        if (level == 1)
            cout << root->getData() << " ";
        else if (level > 1) {
            printLevelOrderHelper(root->getLPtr(), level - 1);
            printLevelOrderHelper(root->getRPtr(), level - 1);
        }
    }
}

template<class T>
AVLTree<T>::AVLTree() {
    this->root = nullptr;
}

template<class T>
AVLTree<T>::~AVLTree() {
    AVLDelete(this->root);
}

template<class T>
void AVLTree<T>::AVLDelete(AVLNode<T>* root) {
    if (root != nullptr) {
        AVLDelete(root->getLPtr());
        AVLDelete(root->getRPtr());
        delete root;
    }
}

template<class T>
void AVLTree<T>::insert(T newValue) {//First insert as you would a normal BST
    if (this->root) {
        insertHelper(this->root, newValue);
    }
    else {
        this->root = new AVLNode<T>(newValue);
    }
}

template<class T>
void AVLTree<T>::insertHelper(AVLNode<T>*& root, T newValue) {
    int height1 = 0, height2 = 0;
    if (root->getData() > newValue) {
        if (root->getLPtr() == nullptr) {
            root->setLPtr(new AVLNode<T>(newValue));
        }
        else {
            insertHelper(root->getLPtr(), newValue);
            height1 = root->findHeight(root->getLPtr());
            height2 = root->findHeight(root->getRPtr());

            if (height1 - height2 == 2) {
                if (newValue < root->getLPtr()->getData()) {
                    rotateWithLeftChild(root);
                }
                else {
                    doubleWithLeftChild(root);
                }
            }
        }
    }
    else {
        if (root->getRPtr() == nullptr) {
            root->setRPtr(new AVLNode<T>(newValue));
        }
        else {
            insertHelper(root->getRPtr(), newValue);

            height1 = root->findHeight(root->getLPtr());
            height2 = root->findHeight(root->getRPtr());

            if (height2 - height1 == 2) {
                if (newValue > root->getRPtr()->getData()) {
                    rotateWithRightChild(root);
                }
                else {
                    doubleWithRightChild(root);
                }
            }
        }
    }
    root->setHeight(root->findHeight(root));
}

template<class T>
int AVLTree<T>::height(void) {
    return this->root->getHeight();
}

template<class T>
int AVLTree<T>::heightHelper(AVLNode<T>* root) {
    if (root == nullptr) {
        return -1;
    }
    else {
        return 1 + max(heightHelper(root->getLPtr()), heightHelper(root->getRPtr()));
    }
}

template<class T>
bool AVLTree<T>::contains(T newValue) {
    
    return containsHelper(this->root, newValue);
}

template<class T>
bool AVLTree<T>::containsHelper(AVLNode<T>* root, T newValue) {
    int temp = 0;
    if (root->getData() == newValue) {
        return 1;
    }
    else if (root->getLPtr() != nullptr && root->getData() > newValue) {
        temp = containsHelper(root->getLPtr(), newValue);
    }
    else if (root->getRPtr() != nullptr) {
        temp = containsHelper(root->getRPtr(), newValue);
    }
    return temp;
}

template<class T>
bool AVLTree<T>::validate(void) {
    return validateHelper(root);
}

template <class T>
bool AVLTree<T>::validateHelper(AVLNode<T>* root){

    if (root == nullptr) {
        return true;
    }
    if (abs(root->findHeight(root->getLPtr()) - root->findHeight(root->getRPtr())) <= 1 && validateHelper(root->getRPtr()) && validateHelper(root->getLPtr())) {
        return true;
    }
    return false;
}