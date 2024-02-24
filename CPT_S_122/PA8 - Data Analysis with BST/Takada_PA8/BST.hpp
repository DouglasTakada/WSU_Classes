#pragma once
#include "TransactionNode.hpp"

class BST {
public:
	BST();
	~BST();

	Node* getRootPtr(void);

	void setRootPtr(Node* newPtr);

	void insert(string newItem, int newUnit);

	void inOrderTraversal();

	TransactionNode& findSmallest();
	TransactionNode& findLargest();

private:
	void destroyTree(Node* PRoot);
	void insert(string newItem, int newUnit, Node*& rootPtr);
	void inOrderTraversal(Node* PRoot);
	Node* RootPtr;

};