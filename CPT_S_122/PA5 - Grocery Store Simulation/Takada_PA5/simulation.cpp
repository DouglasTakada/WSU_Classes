#include "library.hpp"
#include "simulation.hpp"
#include "queue.hpp"

//constructor
Simulation::Simulation(int newMinutes) {
	minutes = newMinutes;
}

//destructor
Simulation::~Simulation() {
	//I don't think this needs to do anything
}

//main driver of program
void Simulation::run(int numMins) {//Main driving force of program
	//What I need:
		/*
		* Queue for express and normal lane
		* Random number generator for arrival times
		* Random number generator for service times (Only after customer has arrived)
		* keep track of when the service time is up for customer so 
		*	I know when to dequeue them so the next customer will be at the
		*	pTail so they can get serviced
		* print out the simulated minutes and when each customer dequeues
		* 
		* I also need to keep track of customer ID
		*/
	Queue Express, Normal;

	//First we need to generate the first customers arrival times
	int normalArrival, expressArrival;
	normalArrival = rand() % 6 + 3;
	expressArrival = rand() % 5 + 1;

	//tracker of line time passed
	int normalTimePassed = 0, expressTimePassed = 0;
	int temp = 0;

	//tracker for service time passed for customer that is being serviced
	int normalServiceTimePassed = 0, expressServiceTimePassed = 0;

	int customerID = 1, custID = 1; //The second variable is just for printing

	//I need to keep track of total service times too
	int nLTotalTime = 0, eLTotalTime = 0;
	int nLServiceTime = 0, eLServiceTime = 0;

	for (int timePassed = 0; timePassed <= numMins; 
		timePassed++, normalTimePassed++, expressTimePassed++, normalServiceTimePassed++,
		expressServiceTimePassed++) {

		cout << "->Simulated Minutes Passed~>" << timePassed << endl;
		
		// Where the simuation
		//will happen!

		if (Normal.isEmpty() == false) {
			//Decrements by 1;
			temp = Normal.getPHead()->getPData()->getServiceTime() - 1;
			Normal.getPHead()->getPData()->setServiceTime(temp);
		}
		if (Express.isEmpty() == false) {
			//Decrements by 1;
			//not for first customer
			temp = Express.getPHead()->getPData()->getServiceTime() - 1;
			Express.getPHead()->getPData()->setServiceTime(temp);
		}

		//Here I need to check if the time passed is equal to the arrival time for
		//each lane 
		//Becausue resetting the time passed would put the outer for loop in a
		//infinate loop, I will create a secod variables that will help us keep track of
		// of just when enough time has passed to equal the arrival time
		if (normalTimePassed == normalArrival) { // If this is the case then generate service time							 
			// and add the customer to the queue
			nLServiceTime = rand() % 6 + 3;
			cout << "Customer has entered the Normal Line" << endl;
			Normal.enqueue(Data(customerID,nLServiceTime,Normal.findTotalTime(nLServiceTime)));
			cout << Normal.getPTail();
			cout << "Arrival Time: " << timePassed << endl;
			//New CustomerID for next customer
			customerID++;
			//Now I that the customer is in queue I need to generate a new arrival time
			//for the next customer
			normalArrival = rand() % 6 + 3;
			//reset the clock that keeps track of when customer arrives
			normalTimePassed = 0;
		}//Now do the same for the expressLane

		if (expressTimePassed == expressArrival) {
			eLServiceTime = rand() % 5 + 1;
			cout << "Customer has entered the Express Line" << endl;
			Express.enqueue(Data(customerID, eLServiceTime,Express.findTotalTime(eLServiceTime)));
			cout << Express.getPTail();
			cout << "Arrival Time: " << timePassed << endl;
			customerID++;
			//Now create new arrival time for next customer
			expressArrival = rand() % 5 + 1;
			//Reset clock so it works properly
			expressTimePassed = 0;
		}

		//Checking for the need to dequeue anything
		if (!Express.isEmpty()) {
			//Decrements by 1;
			//not for first customer
			//temp = Express.getPHead()->getPData()->getServiceTime() - 1;
			//Express.getPHead()->getPData()->setServiceTime(temp);
			//if service time is up then dequeue and print
			if (Express.getPHead()->getPData()->getServiceTime() == 0) {
				custID = Express.getPHead()->getPData()->getCustomerNumber();
				cout << "Customer has dequeued from the Express Line:" << endl;
				cout << Express.getPHead() << endl;
				Express.dequeue();
				//Gotta reset timer
				expressServiceTimePassed = 0;
			}
		}

		if (!Normal.isEmpty()) {
			//if service time is up then dequeue and print
			if (Normal.getPHead()->getPData()->getServiceTime() == 0) {
				custID = Normal.getPHead()->getPData()->getCustomerNumber();
				cout << "Customer has dequeued from the Normal Line:" << endl;
				cout << Normal.getPHead() << endl;
				Normal.dequeue();
				//Gotta reset timer
				normalServiceTimePassed = 0;
			}
		}
		if (timePassed % 10 == 0 && timePassed != 0) {
			cout << "Customers in the Normal Line: " << endl;
			Normal.printQueue();
			cout << "Customers in the Express Line: " << endl;
			Express.printQueue();
		}
	}
	cout << "\n~~Simulation Successfully Ended~~" << endl;
}