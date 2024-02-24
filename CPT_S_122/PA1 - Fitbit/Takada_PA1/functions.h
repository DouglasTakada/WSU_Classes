#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum sleep {
    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;


typedef struct fitbit{
    char patient[10];
    char minute[9];
    double calories;
    double distance;
    unsigned int floors;
    unsigned int heartRate;
    unsigned int steps;
    Sleep sleepLevel;
} FitbitData;

/*
* Function: getData(FitbitData* minute)
* Date Created: 1/27/2022
* Date Last Modified: 1/27/2022
* Description:This function opens the file and reads in all of the data
*              and cleans and parses it line by line
* Input Parameter:FitbitData* minute
* Returns: The number of lines it read from the file
* Preconditions: The function must be called and the fitbit struct must be properly defined
* Postconditions: All of the dat is stored into the stuct and the file is closed
*/
int getData(FitbitData* minute);

/*
* Function: input_invaid(char line[], int index)
* Date Created: 1/27/2022
* Date Last Modified: 1/27/2022
* Description:This function moves each chracter in the array to the right and
*             allows a invalid charcter be placed in between the delimiters that
*             have nothing in between the commas
* Input Parameter: char line[], int index
* Returns: A new array of chracters that is modified is returned
* Preconditions: The function must be called and the proper index and line must be in the parameter
* Postconditions: The line that preiviously had commas next to each other no longer do
*/
char* input_invaid(char line[], int index);

/*
* Function: computedata(int linenum, FitbitData* minute, double* totCal, double* totDist,
    int* totFloor, int* totStep, int* maxSteps, int* aveHeart, char steptime[])
* Date Created: 1/27/2022
* Date Last Modified: 1/27/2022
* Description:This function Computes almost all of the computations except the longest range of poor sleep
* Input Parameter: (int linenum, FitbitData* minute, double* totCal, double* totDist,
    int* totFloor, int* totStep, int* maxSteps, int* aveHeart, char steptime[]);
* Returns: nothing is returned directly but indirectly the the total calories burned, total distance, total floors, total steps
*        max number of steps in one minute, average heart rate and the time in which there was a max number of st is returned
* Preconditions: The function must be called
* Postconditions: The the total calories burned, total distance, total floors, total steps
*        max number of steps in one minute, average heart rate and the time in which there was a max number of step is caclualted
*/
void computedata(int linenum, FitbitData* minute, double* totCal, double* totDist,
    int* totFloor, int* totStep, int* maxSteps, int* aveHeart, char steptime[]);

/*
* Function: computePoorSleep(FitbitData* minute, int* maxSum, char maxStart[], char maxEnd[], int linenum)
* Date Created: 1/27/2022
* Date Last Modified: 1/27/2022
* Description:This function Computes  the longest range of poor sleep
* Input Parameter: FitbitData* minute, int* maxSum, char maxStart[], char maxEnd[], int linenum
* Returns: nothing is returned directly but indirectly the duration from start to finish of the poor sleep, and the sum of poor sleep is returned
* Preconditions: The function must be called
* Postconditions: The  duration from start to finish of the poor sleep, and the sum of poor sleep is caclualted
*/
void computePoorSleep(FitbitData* minute, int* maxSum, char maxStart[], char maxEnd[], int linenum);

#endif