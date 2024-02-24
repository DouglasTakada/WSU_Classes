#include "header.hpp"

class stack {
public:
	stack();
	~stack();

	void push(string& newDate);
	void pop();
	string peak();

	bool isEmpty();

private:
	vector <string> dates;
};