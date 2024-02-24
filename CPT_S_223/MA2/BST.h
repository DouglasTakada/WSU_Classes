#ifndef __BST_H
#define __BST_H

#include <iostream>
#include <limits>
using namespace std;


/*
 *  Data structure for a single tree node
 */
template <typename T>
struct Node {
public:
	T value;
	Node* left;
	Node* right;

	Node(T val) {
		this->value = val;
		this->left = nullptr;
		this->right = nullptr;
	}

	~Node()
	{
		this->value = 0;
		this->left = nullptr;
		this->right = nullptr;
	}
};

/*
 * Binary Search Tree (BST) class implementation
 */
template <typename T>
class BST {

protected:
	Node<T>* _root;         // Root of the tree nodes

	/* Add new T val to the tree */
	void addHelper(Node<T>* root, T val) {
		if (root->value > val) {
			if (!root->left) {
				root->left = new Node<T>(val);
			}
			else {
				addHelper(root->left, val);
			}
		}
		else {
			if (!root->right) {
				root->right = new Node<T>(val);
			}
			else {
				addHelper(root->right, val);
			}
		}
	}

	/* Print tree out in inorder (A + B) */
	void printInOrderHelper(Node<T>* root) {
		if (!root) return;
		printInOrderHelper(root->left);
		cout << root->value << ' ';
		printInOrderHelper(root->right);
	}

	/* Return number of nodes in tree */
	int nodesCountHelper(Node<T>* root) {
		if (!root) {
			return 0;
		}
		else {
			return 1 + nodesCountHelper(root->left) + nodesCountHelper(root->right);
		}
	}

	/* Return height of tree (root == nullptr -> 0) */
	int heightHelper(Node<T>* root) {
		if (!root) {
			return -1;
		}
		else {
			return 1 + max(heightHelper(root->left), heightHelper(root->right));
		}
	}

	/* Delete a given <T> value from tree */
	bool deleteValueHelper(Node<T>* parent, Node<T>* current, T value) {
		if (!current) return false;
		if (current->value == value) {
			if (current->left == nullptr || current->right == nullptr) {
				Node<T>* temp = current->left;
				if (current->right) temp = current->right;
				if (parent) {
					if (parent->left == current) {
						parent->left = temp;
					}
					else {
						parent->right = temp;
					}
				}
				else {
					this->_root = temp;
				}
			}
			else {
				Node<T>* validSubs = current->right;
				while (validSubs->left) {
					validSubs = validSubs->left;
				}
				T temp = current->value;
				current->value = validSubs->value;
				validSubs->value = temp;
				return deleteValueHelper(current, current->right, temp);
			}
			delete current;
			return true;
		}
		return deleteValueHelper(current, current->left, value) ||
			deleteValueHelper(current, current->right, value);
	}

	void destructor(Node<T>* root){/// Goes to the very bottom of the tree and deletes nodes from there so there is no memory leaks
		if (!root) return;
		destructor(root->left);
		destructor(root->right);
		delete root;
	}

	void printLevelOrderHelper(Node<T>* root, int level){///if the node is not nullptr and if the level is where we want then print the value otherwise go deeper in the tree and decrease our level by one until we get the level to be 1(Base case)

		if (root != nullptr){
			if (level == 1)
				cout<< root->value <<" ";
			else if (level > 1) {
				printLevelOrderHelper(root->left, level - 1);
				printLevelOrderHelper(root->right, level - 1);
			}
		}		
	}

	void printMaxPathHelper(Node<T>* root){///Print the node you are currently at, then if the right subtree of the node is bigger than the left then go to the right subtree and recursively call the function until the root is nullptr
		if(root != nullptr){
			cout<< root->value<<" ";
			if(heightHelper(root->left) < heightHelper(root->right)){
				printMaxPathHelper(root->right);
			} else{
				printMaxPathHelper(root->left);
			}
		}
	}

	int containsHelper(Node<T>* root,T value){///If the current node is not null and its value in the tree is greater than the value we are trying to find then go down the left subtree and call the function again, otherwise go right and call the function again. if the value is found then return 1 to set temp to 1 and return temp
		int temp = 0;
		if(root != nullptr){
			if(root->value == value){
				return 1;
			} else if(root->left != nullptr && root->value > value){
				temp = containsHelper(root->left, value);
			} else if(root->right != nullptr){
				temp = containsHelper(root->right, value);
			}
		}
		return temp;
	}

	/********************************* PUBLIC API *****************************/
public:

	BST() : _root(nullptr) { }               // Basic initialization constructor

	/**
	 * Destructor - Needs to free *all* nodes in the tree
	 * TODO: Implement Destructor
	 */
	~BST() {
	    destructor(this->_root);//Calls my recursive function
	}

	/* Public API */
	void add(T val) {
		if (this->_root) {
			this->addHelper(this->_root, val);
		}
		else {
			this->_root = new Node<T>(val);
		}
	}

	void print() {
		printInOrderHelper(this->_root);
	}

	/**
	 * Print the nodes level by level, starting from the root
	 * TODO: Implement printLevelOrder
	 */
	void printLevelOrder() {
		int level = heightHelper(this->_root);
		for(int i = 1; i <= level + 1;i++){
		printLevelOrderHelper(this->_root, i);//Calls my recursive function based on how big the height is
		cout<<endl;
		}
	}

	int nodesCount() {
		return nodesCountHelper(this->_root);
	}

	int height() {
		return heightHelper(this->_root);
	}

	/**
	 * Print the maximum path in this tree
	 * TODO: Implement printMaxPath
	 */
	void printMaxPath() {
		printMaxPathHelper(this->_root);//Calls my recursive function
	}

	bool deleteValue(T value) {
		return this->deleteValueHelper(nullptr, this->_root, value);
	}

	/**
	 * Find if the BST contains the value
	 * TODO: Implement contains
	 */
	bool contains(T value) {
	return containsHelper(this->_root, value);//Calls my recursive function
	}
};

#endif

