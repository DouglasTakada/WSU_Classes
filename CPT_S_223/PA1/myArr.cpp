#include "myArr.hpp"

myArr::myArr(){
	cap = 10;
	numOfElem = 0;
	arr = new myData[cap];
}

myArr::~myArr(){
	delete[] arr;
}

void myArr::initialize(int from){
	for (size_t i = from; i < cap; i++) {
		arr[i].initializedata("",0);
	}
}

void myArr::expand(void){
	cap *= 2;

	myData* temp = new myData[cap];

	for (size_t i = 0; i < numOfElem; i++){
		temp[i].initializedata(arr[i].name, arr[i].points);
	}
	delete[] arr;
	arr = temp;
	initialize(numOfElem);
}

myData myArr::getAt(int index){
	if (index < 0 || index >= numOfElem) {
		throw ("Out of bounds exception!");
	}
		return arr[index];
}

void myArr::popBack(void){
	if (numOfElem > 0) {
		arr[--numOfElem].name = "";
		arr[numOfElem].points = 0;
	}
	else {
		cout << "Array Empty" << endl;
	}
}

void myArr::add(string name, int points){
	if (numOfElem >= cap) {
		expand();
	}
	myData temp1, temp2;
	for (int i = getNumElm(); i >= 1; i--)
		arr[i] = arr[i - 1];

	this->arr[0].initializedata(name, points);
	numOfElem++;
}

void myArr::printProf(void) {
	for (int i = 0; i < numOfElem;i++) {
		cout<< this->getAt(i).name<< "," << this->getAt(i).points;
	}
}

void myArr::saveProf() {
	ofstream output;
	output.open("profiles.csv");
	if (output.is_open()) {
		output << "name,points" << endl;
		for (int i = 0; i < this->numOfElem; i++) {
			output << this->getAt(i).name << "," << this->getAt(i).points;
			if (i != numOfElem -1) {
				output << endl;
			}
		}
	}
	output.close();//closes file
}

bool myArr::searchFor(string &name, int &points) {
	char p1[100];
	char p2[100];
	strcpy(p1, name.c_str());
	for (int i = 0; i < this->numOfElem; i++) {
		strcpy(p2, this->getAt(i).name.c_str());
		if (strcmp(p1, p2) == 0) {
			points = this->getAt(i).points;
			return true;
		}
	}
	return false;
}

//void myArr::savepoints(string& name, int& points) {
//	char p1[100];
//	char p2[100];
//	strcpy(p1, name.c_str());
//	for (int i = 0; i < this->numOfElem; i++) {
//		strcpy(p2, this->getAt(i).name.c_str());
//		if (strcmp(p1, p2) == 0) {
//			this->getAt(i).points = points;
//		}
//	}
//}

void myArr::updateScore(string name, int points) {
	char p1[100];
	char p2[100];
	strcpy(p1, name.c_str());
	for (int i = 0; i < this->numOfElem; i++) {
		strcpy(p2, this->getAt(i).name.c_str());
		if (strcmp(p1, p2) == 0) {
			this->arr[i].setpoint(points);
		}
	}
}

void myArr:: modAt(string name, int points){
	char p1[100];
	char p2[100];
	strcpy(p1, name.c_str());
	for (int i = 0; i < this->numOfElem; i++) {
		strcpy(p2, this->getAt(i).name.c_str());
		if (strcmp(p1, p2) == 0) {
			this->arr[i].setpoint(points);
		}
	}
}

int myArr::getNumElm() {
	return this->numOfElem;
}