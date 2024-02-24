#include "queue.hpp"
#include "queuenode.hpp"
#include "library.hpp"

//Constructor
Queue::Queue(QueueNode* newPHead, QueueNode* newPTail){
	this->pHead = newPHead;
	this->pTail = newPTail;
}

//Destructor
Queue::~Queue() {
	QueueNode* curNode = nullptr;
	Data* curData = nullptr;
	while (pHead != nullptr) {
		curNode = this->pHead;
		curData = this->pHead->getPData();
		this->pHead = this->pHead->getPNext();
		delete curData;
		delete curNode;
	}
}

//getters
QueueNode* Queue::getPHead() const{
	return this->pHead;
}

QueueNode* Queue::getPTail() const{
	return this->pTail;
}

//setters
void Queue::setPHead(QueueNode* newPHead) {
	this->pHead = newPHead;
}

void Queue::setPTail(QueueNode* newPTail) {
	this->pTail = newPTail;
}

// checks if the queue is empty or not
bool Queue::isEmpty() const{
	return (this->pHead == nullptr);
}

//Adds node to queue - returns bool based on if it was successful or not
bool Queue::enqueue(Data const &newData) {
	bool state = false;
	QueueNode* newNode = new QueueNode(newData);
	if (newNode != nullptr) {
		if (this->pHead == nullptr) {
			this->pHead = this->pTail = newNode;
			state = true;
		}
		else {
			this->pTail->setPNext(newNode);
			this->pTail = newNode;

			state = true;
		}
	}
	return state;
}


//Rempves node from queue from the head Node
int Queue::dequeue() {//int because return customer ID
	QueueNode* pTemp = this->pHead;
	int custNum = pTemp->getPData()->getCustomerNumber();
	if (this->pHead == this->pTail) {//Delete the node and set everything to nullptr
		this->pHead = this->pTail =nullptr;
	}
	else {
		this->pHead = this->pHead->getPNext();
	}
	delete pTemp;
	return custNum;
}

//Prints all nodes existing inside the given queue
void Queue::printQueue() {
	QueueNode* curNode = this->getPHead();
	if (curNode == nullptr) {
		cout << "Empy Line" <<endl;
	}
	while (curNode != nullptr) {
		cout << curNode; // or cout << *(curNode); ??
		curNode = curNode->getPNext();
	}
}

//Caclulates the time that is left for given customer based on wait time
int Queue::findTotalTime(int& serviceTime) {
	int totalTimeInLine = serviceTime;
	QueueNode* curNode = this->getPHead();
	if (curNode == nullptr) {//very first customer
		//totalTimeInLine = serviceTime;
	}
	else{
		while (curNode != nullptr) {
			totalTimeInLine += curNode->getPData()->getServiceTime();
			curNode = curNode->getPNext();
		}
	}
	return totalTimeInLine;
}