#pragma once

#include <iostream>
#include <fstream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::ostream;
using std::fstream;
using std::ofstream;

class ExercisePlan
{
public:
	
	ExercisePlan(const string& newPlanName = "", const string& newDate = "", const int& newGoalSteps = 0);
	ExercisePlan(const ExercisePlan& copy);
	~ExercisePlan();
	ExercisePlan& operator= (const ExercisePlan& rhs);

	string getPlanName() const;
	string getDate() const;
	int getGoalSteps() const;

	void setPlanName(const string& newPlanName);
	void setDate(const string& newDate);
	void setStepGoal(const int& newSteps);

	void editGoal();
		
private:
	string mPlanName;
	string mDate;
	int mGoalSteps;
};

// nonmember functions
ostream& operator<< (ostream& lhs, const ExercisePlan& rhs); // will allow cout << ExercisePlan object1 << ExercisePlan object2...
// write a complete ExercisePlan to a file
fstream& operator<< (fstream& lhs, const ExercisePlan& rhs); // will allow fstr << ExercisePlan object1 << ExercisePlan object2... 
// read a complete ExercisePlan from a file
fstream& operator>> (fstream& lhs, ExercisePlan& rhs); // will allow fstr >> ExercisePlan object1 >> ExercisePlan object2...