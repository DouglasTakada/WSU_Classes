#include "stack.hpp"

stack::stack() {

}

stack::~stack() {

}

void stack::push(string &newDate) {
	dates.push_back(newDate);
}

void stack::pop() {
	dates.pop_back();
}

string stack::peak() {
	string date = "";
	if (!this->dates.empty()) {
		date = dates.back();
	}
	return date;
}

bool stack::isEmpty() {
	return this->dates.empty();
}