#include "stack.hpp"

class data {
public:
	data(int newRec = 0, int newID = 0, string newFirst = "",
		string newLast = "", string newEmail = "",
		string newUnits = "", string newProg = "",
		int newNumAbs = 0);
	~data();

	int getRecNum();
	int getIDNum();
	string getFirst();
	string getLast();
	string getEmail();
	string getUnits();
	string getProgram();
	string getLevel();
	int getNumAbscences();
	stack* getDateOfAbsenses();

	void setRecNum(int newRec);
	void setIDNum(int newID);
	void setFirst(string newStr);
	void setLast(string newStr);
	void setEmail(string newStr);
	void setUnits(string newStr);
	void setProgram(string newStr);
	void setLevel(string newStr);
	void incrementAbscences();
	void decrementAbscences();
	
private:
	/*-record number (max 3 digits)
	-ID number (max 9 digits)
	-name (last, first)
	-email
	-units (number of credits for class or AU for audit)
	-program (major)
	-level (freshman, sophomore, junior, senior, graduate)*/

	int recordNum;
	int IDNum;
	string first;
	string last;
	string email;
	string units;
	string program;
	string level;
	int numAbscences;
	stack dateOfAbsenses;
};

//Can't use references so uses pointers so it
//doesn't copy all the data
ostream& operator << (ostream& lhs, data* rhs);
ofstream& operator << (ofstream& lhs, data* rhs);