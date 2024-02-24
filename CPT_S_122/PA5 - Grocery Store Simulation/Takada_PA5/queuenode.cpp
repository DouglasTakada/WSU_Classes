#include "queuenode.hpp"
#include "library.hpp"

//constructor
QueueNode::QueueNode(Data const& newData){
	Data* dat = new Data(newData);
	this->pData = dat;
	this->pNext = nullptr;
}

//destructor
QueueNode::~QueueNode() {
	//Gotta figure out what to do with destructors
}

//getters
QueueNode* QueueNode::getPNext() const{
	return this->pNext;
}

Data* QueueNode::getPData() const{
	return this->pData;
}

//setters
void QueueNode::setPNext(QueueNode* newPNext) {
	this->pNext = newPNext;
}
void QueueNode::setPData(Data* newPData) {
	this->pData = newPData;
}

//non-memeber function - overloading operator
ostream& operator << (ostream& out, QueueNode* node) {
	cout << "Customer Number: "
		<< (*node).getPData()->getCustomerNumber() << endl
		<< "Service Time Left: ";
		cout << (*node).getPData()->getServiceTime() << endl
		<< "Total time in Line: "
		<< (*node).getPData()->getTotalTime() << endl;
		
	return out;
}