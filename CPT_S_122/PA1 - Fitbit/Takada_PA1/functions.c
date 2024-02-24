#include "functions.h"

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
int getData(FitbitData* minute) {//minute,calories,distance,floors,heart,steps,sleep_level
	int linenum = 0, counter = 0;
	char temp[100] = "", line[100] = "", dupeline[100] = "";
	char* field = "";
	FILE* infile = fopen("fitbitData.csv", "r");
	if (infile != NULL) {
		for (int i = 0; i < 2; i++) {//make sure it does not record the data in the begginning 
			fgets(temp, 100, infile);
		}
		while (fgets(temp, 100, infile) != NULL) {//cleaning Data
			counter = 0;
			while (temp[counter] != '\n') {
				// keep moving through line until we reach very end
				counter++;
				if (temp[counter] == ',' && temp[counter + 1] == ',') {
					// empty field found
					strcpy(temp, input_invaid(temp, counter + 1));
				}
				else if (temp[counter] == ',' && temp[counter + 1] == '\n') {
					strcpy(temp, input_invaid(temp, counter + 1));
				}
			}
			strcpy(line, temp);
			if (strcmp(strtok(line, ","), "12cx7") == 0) {//Parsing and putting into correct fields
				strcpy(minute[linenum].patient, "12cx7");
				field = strtok(NULL, ",");
				if (strcmp(field, "-") == 0) {
					strcpy(minute[linenum].minute, "-1");
				}
				else {
					strcpy(minute[linenum].minute, field);
				}
				field = strtok(NULL, ",");
				if (strcmp(field, "-") == 0) {
					minute[linenum].calories = -1;
				}
				else {
					minute[linenum].calories = atof(field);
				}
				field = strtok(NULL, ",");
				if (strcmp(field, "-") == 0) {
					minute[linenum].distance = -1;
				}
				else {
					minute[linenum].distance = atof(field);
				}
				field = strtok(NULL, ",");
				if (strcmp(field, "-") == 0) {
					minute[linenum].floors = -1;
				}
				else {
					minute[linenum].floors = atof(field);
				}
				field = strtok(NULL, ",");
				if (strcmp(field, "-") == 0) {
					minute[linenum].heartRate = -1;
				}
				else {
					minute[linenum].heartRate = atof(field);
				}
				field = strtok(NULL, ",");
				if (strcmp(field, "-") == 0) {
					minute[linenum].steps = -1;
				}
				else {
					minute[linenum].steps = atof(field);
				}
				field = strtok(NULL, "/n");
				if (strcmp(field, "-") == 0) {
					minute[linenum].sleepLevel = -1;
				}
				else {
					minute[linenum].sleepLevel = atof(field);
				}
				//Check for Dupes
				if (linenum != 0 && strcmp(minute[linenum - 1].minute, minute[linenum].minute) == 0) {//if times are identical then it means they are duplicates
									//thus the line will be overwritten with the next line
					linenum--;

				}
				linenum++;
			}
		}
		fclose(infile);
	}
	return linenum - 2;// Discard two first lines
}

char* input_invaid(char line[], int index) {
	char newline[100] = "";
	int length = strlen(line), i = 0;

	while (length - i >= index) {
		//move chars until getting to insert position	
		newline[length + 1 - i] = line[length - i];
		i++;
	}
	newline[length + 1 - i] = '-';	// insert invalid value in position

	while (length - i >= 0) {
		newline[length - i] = line[length - i];
		i++;
	}
	return newline;
}


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
	int* totFloor, int* totStep, int* maxSteps, int* aveHeart, char steptime[]) {
	int numHeart = 0, totHeart = 0;
	for (int i = 0; i < linenum - 1; i++) {
		if (minute[i].calories > 0) {
			*totCal += minute[i].calories;
		}
		if (minute[i].distance > 0) {
			*totDist += minute[i].distance;
		}
		if (minute[i].floors > 0) {
			*totFloor += minute[i].floors;
		}
		if (minute[i].steps > 0) {
			*totStep += minute[i].steps;
		}
		if (minute[i].steps > *maxSteps) {
			*maxSteps = minute[i].steps;
			strcpy(steptime, minute[i].minute);
		}
		if (minute[i].heartRate != 0 && minute[i].heartRate != -1) {
			numHeart++;
			totHeart += minute[i].heartRate;
		}
	}
	*aveHeart = totHeart / numHeart;
}


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
void computePoorSleep(FitbitData* minute, int* maxSum, char maxStart[], char maxEnd[], int linenum) {
	int range = 0, sum = 0;
	for (int i = 0; i < linenum; i++) {
		if (minute[i].sleepLevel > 1) {//Must be above 1 to have poor sleep
			if (sum > *maxSum) {
				*maxSum = sum;
				strcpy(maxEnd, minute[i - 1].minute);
				strcpy(maxStart, minute[i - range].minute);
			}
			sum = 0;
			range = 0;
		}
		else {
			range++;
			sum += minute[i].sleepLevel;
		}
	}
}