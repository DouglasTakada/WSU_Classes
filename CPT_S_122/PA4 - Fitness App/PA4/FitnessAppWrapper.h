///////////////////////////////////////////////////////////////////////////////
/// \file         
/// \author       AO
/// \date         
/// \brief   You are to write a basic fitness application, in C++, 
///          that allows the user of the application to manually edit 
///          “diet” and “exercise” plans.For this application you will 
///          need to create three classes : DietPlan, ExercisePlan, and FitnessAppWrapper.     
///           
///       
/// REVISION HISTORY:
/// \date  
///            
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cstdlib> // to use system("cls");

#include "DietPlan.h"
#include "ExercisePlan.h"

class FitnessAppWrapper
{
public:
	FitnessAppWrapper(); // default constructor
	~FitnessAppWrapper(); // destructor

	void runApp(); // will drive the application
	void performUserSelection(const int &option);

	void loadWeeklyDietPlan(); // this will call the private loadWeeklyPlan() function
	void displayWeeklyDietPlan(); // this will call the private displayWeeklyPlan() function
	void storeWeeklyDietPlan(); // this will call the private storeWeeklyPlan() function
	bool editDietPlan(); // will prompt the user for the name of the plan to edit

	void loadWeeklyExercisePlan(); // this will call the private loadWeeklyPlan() function
	void displayWeeklyExercisePlan(); // this will call the private displayWeeklyPlan() function
	void storeWeeklyExercisePlan(); // this will call the private storeWeeklyPlan() function
	bool editExercisePlan(); // will prompt the user for the name of the plan to edit

private:
	DietPlan mDPList[7];// will store the weekly list of DietPlan objects - 1 week = 7 days
	ExercisePlan mEPList[7];

	fstream mFstrDP;    // stream object for input/output to dietPlans.txt
	fstream mFstrEP;

	// private helper/utility functions
	void loadDailyPlan(fstream &fileStream, DietPlan &plan);
	void loadWeeklyPlan(fstream &fileStream, DietPlan weeklyPlan[]);
	void displayDailyPlan(const DietPlan &plan);
	void displayWeeklyPlan(const DietPlan weeklyPlan[]);
	void storeDailyPlan(fstream &fileStream, const DietPlan &plan);
	void storeWeeklyPlan(fstream &fileStream, const DietPlan weeklyPlan[]);

	void loadDailyPlan(fstream& fileStream, ExercisePlan& plan);
	void loadWeeklyPlan(fstream& fileStream, ExercisePlan weeklyPlan[]);
	void displayDailyPlan(const ExercisePlan& plan);
	void displayWeeklyPlan(const ExercisePlan weeklyPlan[]);
	void storeDailyPlan(fstream& fileStream, const ExercisePlan& plan);
	void storeWeeklyPlan(fstream& fileStream, const ExercisePlan weeklyPlan[]);

	void displayMenu();
};