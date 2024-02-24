/*
* Programmer: Douglas R. Takada
* Class: Cpts; lab section ...
* Programmming Assignment: PA 1
* Date: 1/14/2022
* Douglas Takada
*/

#include "functions.h"

int main(void) {
	FitbitData minute[1440] = { "","",0.0,0.0,0,0,0,0 };
	double totCal = 0, totDist = 0;
	int totFloor = 0, aveHeart = 0, totStep = 0, maxStep = 0, poorSleep = 0, linenum = 0, range = 0, sum = 0, maxSum = 0;
	linenum = getData(minute);// cleans and parses data
	char steptime[10] = "", maxStart[20] = "", maxEnd[20] = "";

	computedata(linenum, minute, &totCal, &totDist, &totFloor, &totStep, &maxStep, &aveHeart, steptime);// Computes total distance, calories burned, distance, number of floors, number of steps
																										//Max number of steps in one minute, average heartrate, and time of most steps taken
	computePoorSleep(minute, &maxSum, maxStart, maxEnd, linenum);

	//Prints output to file and terminal
	for (int i = 0; i < linenum; i++) {
		printf("Patient: %s, Minute: %s, Calories: %.2f, Distance: %.2f, Floors: %d, HeartRate: %d Steps: %d Sleep Level: %d\n",
			minute[i].patient,
			minute[i].minute,
			minute[i].calories,
			minute[i].distance,
			minute[i].floors,
			minute[i].heartRate,
			minute[i].steps,
			minute[i].sleepLevel);
	}
	printf("Number of lins: %d\nTotal Calories: %lf\nTotal Distance: %lf\nTotal Floors: %d\nTotal Step: %d\nAverage Heart Rate: %d\nHighest step time:",
		linenum, totCal, totDist, totFloor, totStep, aveHeart);
	puts(steptime);
	printf("Highest number of steps: %d", maxStep);
	printf("\nworst sleep range is from %s to %s w/ sum of %d\n", maxStart, maxEnd, maxSum);
	FILE* outfile = fopen("Results.csv", "w");
	fprintf(outfile, "Number of lins: %d\nTotal Calories: %lf\nTotal Distance: %lf\nTotal Floors: %d\nTotal Step: %d\nAverage Heart Rate: %d\nHighest step time:",
		linenum, totCal, totDist, totFloor, totStep, aveHeart);
	fprintf(outfile, "Highest number of steps: %d", maxStep);
	fprintf(outfile, "\nworst sleep range is from %s to %s w/ sum of %d\n", maxStart, maxEnd, maxSum);
	fclose(outfile);
	return 0;
}