#include "ExercisePlan.h"

ExercisePlan::ExercisePlan(const string &newPlanName, const string &newDate, const int &newGoalSteps)
{
	this->mPlanName = newPlanName;
	this->mDate = newDate;
	this->mGoalSteps = newGoalSteps;
	cout << "Inside DietPlan's constructor!" << endl;
}

ExercisePlan::ExercisePlan(const ExercisePlan&copy)
{
	this->mPlanName = copy.mPlanName;  // this is copy a std::string to another one; std::string is an object, 
	                             // so the overloaded assignment for one is called here!
	this->mDate = copy.mDate;  // calls std::string overloaded assignment operator!
	this->mGoalSteps = copy.mGoalSteps;  // simple assignment between integers
}

ExercisePlan::~ExercisePlan()
{
	// the DietPlan objects will be stored in an array in the 
	// fitnessAppWrapper class
	cout << "Inside of ExercisePlan's destructor!" << endl;
}

ExercisePlan& ExercisePlan::operator= (const ExercisePlan&rhs)
{
	// check for self assignment
	if (this != &rhs) // the & here is the "address of" operator
	{
		// we are not peforming self-assignment if inside here
		this->mPlanName = rhs.mPlanName;  // this is copy a std::string to another one; std::string is an object, 
									 // so the overloaded assignment (=) for one is called here!
		this->mDate = rhs.mDate;  // calls std::string overloaded assignment (=) operator!
		this->mGoalSteps = rhs.mGoalSteps;  // simple assignment between integers
	}

	return (*this);
}

// getters - allows us to return a copy of the private data members to outside the object
string ExercisePlan::getPlanName() const // const member function - should not modify data in object - if try to, compiler will provide error!
{
	return this->mPlanName;
}

string ExercisePlan::getDate() const
{
	return this->mDate;
}

int ExercisePlan::getGoalSteps() const
{
	return this->mGoalSteps;
}

// setters - allows us to modify the private data members with values from outside the object
void ExercisePlan::setPlanName(const string &newPlanName)
{
	this->mPlanName = newPlanName; // calls std::string overloaded assignment (=) operator
}

void ExercisePlan::setDate(const string &newDate)
{
	this->mDate = newDate; // calls std::string overloaded assignment (=) operator
}

void ExercisePlan::setStepGoal(const int &newGoalSteps)
{
	this->mGoalSteps = newGoalSteps;
}

void ExercisePlan::editGoal()
{
	cout << "Please enter a new calories goal: ";
	cin >> this->mGoalSteps;

	cout << (*this) << endl;
}



///////////////////////// nonmember functions /////////////////////////////////////

// format: Plan Name
//         Goal Steps
//         Date

ostream & operator<< (ostream &lhs, const ExercisePlan&rhs)  // will allow cout << DietPlan object1 << DietPlan object2...
{
	lhs << rhs.getPlanName() << endl << rhs.getGoalSteps() << endl << rhs.getDate();

	return lhs; // allows for chaining of stream insertions cout << DietPlan object1 << DietPlan object2...
}

// format: Plan Name
//         Goal Steps
//         Date

fstream & operator<< (fstream &lhs, const ExercisePlan&rhs) // will allow fstr << DietPlan object1 << DietPlan object2... 
{
	// cast lhs to ofstream so can easily output std::string (plan name)
	((ofstream &) (lhs)) << rhs.getPlanName() << endl << rhs.getGoalSteps() << endl << rhs.getDate();

	return lhs;
}

// format: Plan Name
//         Goal Steps
//         Date

fstream & operator>> (fstream &lhs, ExercisePlan &rhs)
{
	char tempString[100] = "";
	lhs.getline (tempString, 100);
	rhs.setPlanName(tempString); 
	int goalSteps = 0;
	lhs.getline(tempString, 100);  
	goalSteps = atoi(tempString); 
	rhs.setStepGoal(goalSteps);
	lhs.getline(tempString, 100);
	rhs.setDate(tempString);

	return lhs;
}