#include "mydata.hpp"

class myArr {

private:
	int cap;
	int numOfElem;
	myData *arr;

public:

	myArr();
	~myArr();

	int getNumElm();

	void initialize(int from);

	void expand(void);

	myData getAt(int index);

	void modAt(string name, int points);

	void add(string name, int points);

	void popBack(void);

	void printProf(void);

	void saveProf(void);

	bool searchFor(string& name, int& points);

	void updateScore(string name, int points);

	//void savepoints(string& name, int& points);
};