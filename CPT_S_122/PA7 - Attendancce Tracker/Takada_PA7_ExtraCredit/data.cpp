#include "data.hpp"

data::data(int newRec, int newID, string newFirst,
	string newLast, string newEmail,string newUnits,
	string newProg, int newNumAbs) {
	recordNum = newRec;
	IDNum = newID;
	first = newFirst;
	last = newLast;
	email = newEmail;
	units = newUnits;
	program = newProg;
	numAbscences = newNumAbs;
}

data::~data() {

}

int data::getRecNum() {
	return recordNum;
}
int data::getIDNum() {
	return IDNum;
}
string data::getFirst() {
	return first;
}
string data::getLast() {
	return last;
}
string data::getEmail() {
	return email;
}
string data::getUnits(){
	return units;
}

string data::getProgram(){
	return program;
}

string data::getLevel(){
	return level;
}

int data::getNumAbscences(){
	return numAbscences;
}

stack* data::getDateOfAbsenses(){
	return &dateOfAbsenses;
}

void data::setRecNum(int newRec){
	recordNum = newRec;
}

void data::setIDNum(int newID){
	IDNum = newID;
}

void data::setFirst(string newStr){
	first = newStr;
}

void data::setLast(string newStr){
	last = newStr;
}

void data::setEmail(string newStr){
	email = newStr;
}

void data::setUnits(string newStr){
	units = newStr;
}

void data::setProgram(string newStr){
	program = newStr;
}

void data::setLevel(string newStr){
	level = newStr;
}

void data::incrementAbscences(){
	this->numAbscences++;
	string newDate = "";
	time_t t = time(0);   // get time now

	struct tm* now = localtime(&t);
	cout << (now->tm_year + 1900) << '-'
		<< (now->tm_mon + 1) << '-'
		<< now->tm_mday
		<< endl;
	newDate = to_string((now->tm_year + 1900)) + '-'
		+ to_string((now->tm_mon + 1)) + '-'
		+ to_string(now->tm_mday);
	this->getDateOfAbsenses()->push(newDate);
}

void data::decrementAbscences(){
	numAbscences--;
}

ostream& operator << (ostream& lhs, data* rhs) {
	lhs << "\n\tRecord Number: "<<rhs->getRecNum() << "\n\tID Number: " << rhs->getIDNum() <<
		"\n\tName: " << rhs->getLast()<< ", " << rhs->getFirst() << "\n\tEmail: " << rhs->getEmail() <<
		"\n\tUnits: " << rhs->getUnits()<< "\n\tMajor: " << rhs->getProgram() << "\n\tGrade: "
		<< rhs->getLevel() << endl;
	return lhs;
}

ofstream& operator << (ofstream& lhs, data* rhs) {
	lhs << to_string(rhs->getRecNum()) << "," << to_string(rhs->getIDNum()) << "," << rhs->getLast()
		<< "," << rhs->getFirst() << "," << rhs->getEmail() << "," << rhs->getUnits()
		<< "," << rhs->getProgram() << "," << rhs->getLevel() << endl;
	return lhs;
}