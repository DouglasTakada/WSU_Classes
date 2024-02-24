#include "header.hpp"
struct myData {
	string name;
	int points;

	myData() : name(""), points(0) {
		
	}

	void initializedata(string name, int points) {
		this->name = name;
		this->points = points;
	}

	void setpoint(int points) {
		this->points = points;
	}
};