#pragma once
#include "node.hpp"

template <class T1, class T2>
class BST {
public:
	//Constructor
	//Default
	BST(Node<T1, T2>* newPRoot = nullptr);
	//Destructor
	~BST();

	void insert(Node<T1, T2>* pTree, T1& newChar, T2& newMorse);

	void print();

	T2 search(T1& target);

	void convertToMorse(ifstream& file);

private:
	//Private functions so they can be used recursivly
	//and also better coding practices
	void print(Node<T1, T2>* pTree);
	void destroyTree(Node<T1, T2>* pTree);
	T2 search(Node<T1, T2>* pTree, T1& target);
	//Private variable
	Node<T1, T2>* pRoot;
};

//Constructor
//Default
template <class T1, class T2>
BST<T1, T2>::BST(Node<T1, T2>* newPRoot) {
	this->pRoot = newPRoot;
	string newMorse = "";
	char newLet = NULL;
	int counter = 0;
	ifstream input;
	input.open("MorseTable.txt");
	if (input.is_open()) {
		while (input) {//While it is not at the end of file
			input.get(newLet);
			if (input.get() == ' ') { // this is what seperates the
				//character and the morse code
				getline(input, newMorse, '\n');
				//Testing
				//cout << newLet << " -> " << newMorse << endl;
				insert(this->pRoot, newLet, newMorse);
				counter++;
			}
		}
		if (counter != 39) {
			cout << "Check format of textfile" << endl;
		}
		input.close();
	}
	else {
		cout << "Could not open textfile" << endl;
	}
}

//Destructor
template <class T1, class T2>
BST<T1, T2>::~BST() {
	destroyTree(this->pRoot);
}

template <class T1, class T2>
void BST<T1, T2>::destroyTree(Node<T1, T2>* pTree) {
	if (pTree != nullptr) {//Goes as far down the tree as possible then deletes them
		destroyTree(pTree->getLPtr());
		destroyTree(pTree->getRPtr());
		delete pTree;
	}
}

template <class T1, class T2>
void BST<T1, T2>::insert(Node<T1, T2>* pTree, T1& newChar, T2& newMorse) {//Make node in here, pass data in here
	if (pTree == nullptr) {
		this->pRoot = new Node<T1, T2>(newChar, newMorse);
	}
	else {
		if (pTree->getData()->getLetter() > newChar) {
			if (pTree->getLPtr() == nullptr) {
				pTree->setLPtr(new Node<T1, T2>(newChar, newMorse));
			}
			else {
				insert(pTree->getLPtr(), newChar, newMorse);
			}
		}
		else if (pTree->getData()->getLetter() < newChar) {
			if (pTree->getRPtr() == nullptr) {
				pTree->setRPtr(new Node<T1, T2>(newChar, newMorse));
			}
			else {
				insert(pTree->getRPtr(), newChar, newMorse);
			}
		}
		else if (pTree->getData()->getLetter() == newChar) {
			cout << "There is a duplicate" << endl;
		}
	}
}

template <class T1, class T2>
void BST<T1, T2>::print() {
	print(this->pRoot);
}

template <class T1, class T2>
void BST<T1, T2>::print(Node<T1, T2>* pTree) {
	if (pTree != nullptr) {
		print(pTree->getLPtr());
		cout << pTree->getData()->getLetter() << " -=> "
			<< pTree->getData()->getMorseCode() << endl;
		print(pTree->getRPtr());
	}
}

template <class T1, class T2>
T2 BST<T1, T2>::search(T1& target) {
	return search(this->pRoot, target);
}

template <class T1, class T2>
T2 BST<T1, T2>::search(Node<T1, T2>* pTree, T1& target) {
	if (pTree != nullptr) {
		if (pTree->getData()->getLetter() == target) {
			return pTree->getData()->getMorseCode();

		}
		if (pTree->getData()->getLetter() > target) {
			if (pTree->getLPtr() != nullptr) {
				return search(pTree->getLPtr(), target);
			}
		}
		if (pTree->getData()->getLetter() < target) {
			if (pTree->getRPtr() != nullptr) {
				return search(pTree->getRPtr(), target);
			}
		}
	}
	else {
		return "\0";
	}
}

template <class T1, class T2>
void BST<T1, T2>::convertToMorse(ifstream& file) {
	char curChar = '\0';
	string curStr = "";
	while (file) {
		curChar = file.get();
		curChar = toupper(curChar);
		if (curChar == ' ') {
			cout << "   ";
		}
		else {
			cout << search(curChar) << " ";
		}
	}
}