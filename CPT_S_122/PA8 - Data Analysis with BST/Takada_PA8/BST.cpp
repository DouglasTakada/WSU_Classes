#include "BST.hpp"
//Constructor
BST::BST() {
	this->RootPtr = nullptr;
	//cout << "Inside BST Constructor" << endl;
}
//Destructor
BST::~BST() {
	destroyTree(this->RootPtr);
	//cout << "Inside BST Destructor" << endl;
}
//Getter
Node* BST::getRootPtr(void) {
	return this->RootPtr;
}
//Setter
void BST::setRootPtr(Node* newPtr) {
	this->RootPtr = newPtr;
}
//Calls private insert function; passes in rootptr
void BST::insert(string newItem, int newUnit) {
	insert(newItem, newUnit, this->RootPtr);
}
//Calls private inOrderTraversal function; passes rootptr
void BST::inOrderTraversal() {
	this->inOrderTraversal(this->RootPtr);
}
//Gets to the very far left of the tree to find the smallest number of units
TransactionNode& BST::findSmallest() {
	Node* temp = this->RootPtr;
	while (temp->getLPtr()!= nullptr) {
		temp = temp->getLPtr();
	}
	TransactionNode* transPtr = dynamic_cast<TransactionNode*>(temp);
	return *transPtr;
}
//Gets to the very far left of the tree to find the smallest number of units
TransactionNode& BST::findLargest() {
	Node* temp = this->RootPtr;
	while (temp->getRPtr() != nullptr) {
		temp = temp->getRPtr();
	}
	TransactionNode* transPtr = dynamic_cast<TransactionNode*>(temp);
	return *transPtr;
}
//Does a recursive post order traversal and deletes all the given nodes inside
//the given tree from the bottom up
void BST::destroyTree(Node* PRoot) {
	if (PRoot != nullptr) {
		destroyTree(PRoot->getLPtr());
		destroyTree(PRoot->getRPtr());
		delete PRoot;
	}
}
//Inserts a new data by creating a new transaction node instance
// and put it into the proper place for a BST
//Needed to use dynamic casting to be able to access the number of
//units sold or bought in each node
//Recursive function
void BST::insert(string newItem, int newUnit, Node*& rootPtr) {	
	if (rootPtr == nullptr) {//
		Node* newNode = new TransactionNode(newItem, newUnit);
		rootPtr = newNode;
	}
	else {
		if (newUnit == dynamic_cast<TransactionNode*>(rootPtr)->getUnits()) {
			cout << "Duplicate!" << endl;
		}
		else if (newUnit < dynamic_cast<TransactionNode*>(rootPtr)->getUnits()) {
			insert(newItem, newUnit, rootPtr->getLPtr());
		}
		else if (newUnit > dynamic_cast<TransactionNode*>(rootPtr)->getUnits()) {
			insert(newItem, newUnit, rootPtr->getRPtr());
		}
	}
}
//A recursive in order traversal function that prints the product name and the number of units
void BST::inOrderTraversal(Node* newPRoot) {
	if (newPRoot != nullptr) {
		inOrderTraversal(newPRoot->getLPtr());
		newPRoot->printData();//Product Name
		cout << dynamic_cast<TransactionNode*>(newPRoot)->getUnits() << endl; //Number of units
		inOrderTraversal(newPRoot->getRPtr());
	}
}