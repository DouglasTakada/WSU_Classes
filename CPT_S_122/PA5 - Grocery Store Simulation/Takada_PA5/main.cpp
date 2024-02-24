#include "library.hpp"
#include "test.hpp"
#include "simulation.hpp"

int main(void) {//start of program
	int i = 0;
	cout << "run tests?\n1. Yes\n2. No" << endl;
	cin >> i;
	while (i != 1 && i != 2) {
		cout << "You have entered a invalid option\n"
			"Please try again\n";
			cout << "run tests?\n1. Yes\n2. No" << endl;
		cin >> i;
	}
	if (i == 1) {//Tests
		testDaySimulation();
		testEnqueueEmpty();
		testEnqueueOne();
		testDequeueOne();
		testDequeueTwo();
	}

	cout << "\tEnter the number of minutes you would like "
		"the Supermarket Simulation to run for: " << endl;
	int minutes = 0;
	cin >> minutes;
	while (minutes <0) {
		cout << "You have entered a invalid number of minutes\n"
			"Please try again\n"
			"\tEnter the number of simulation minutes you would like"
			"the Supermarket Simulation to run for: " << endl;
		cin >> minutes;
	}

	Simulation simulation1;//Simulation Wrapper instance
	simulation1.run(minutes);
	return 0;
}