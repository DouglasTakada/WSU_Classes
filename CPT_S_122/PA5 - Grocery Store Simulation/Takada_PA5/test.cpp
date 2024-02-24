#include "test.hpp"
#include "simulation.hpp"

//Tests inserting node into a empty queue
void testEnqueueEmpty() {
	Queue empty;

	empty.enqueue(Data(1, 1, 1));

	// expecting 1 as output to screen
	cout << "Empty Enqueue Test: " << empty.getPHead()->getPData()->getCustomerNumber() << endl;
	if (empty.getPHead()->getPData()->getCustomerNumber() == 1) {
		cout << "Test for enqueue into a empty queue was successful!";
	}
	else {
		cout << "Test for inserting node inot empty queue failed";
	}
}

//Tests inserting two nodes into empty queue
void testEnqueueOne() {
	Queue one;
	cout << "One enqueue Test: " << endl;
	if (one.enqueue(Data(1, 3, 3))) {
		cout << "Successfully enqueued a node into empty queue" << endl;
	}
	if (one.enqueue(Data(2, 2, 5))) {
		cout << "Successfully enqueued a node on top of a existing node within the queue" << endl;
	}
	one.printQueue();
}

//Tests deque for a single node
void testDequeueOne() {
	Queue one;

	one.enqueue(Data(1, 0, 1));
	cout << "One deque Test: " << endl;
	cout << "Value before dequeue: " << one.getPHead()->getPData()->getCustomerNumber() << endl;
	cout << "Dequeueing..." << endl;
	one.dequeue();
	if (one.isEmpty()) {
		cout << "The queue is now empty" << endl;
	}
	else {
		cout << "Test failed. Was not able to dequeue one node in the queue";
	}
}
//Tests deque for two nodes in the same queue
void testDequeueTwo() {
	Queue two;

	two.enqueue(Data(1, 0, 1));
	two.enqueue(Data(2, 0, 1));

	cout << "Two dequeue Test: " << endl;
	cout << "Values before dequeue: " << two.getPHead()->getPData()->getCustomerNumber() << endl;
	cout << two.getPTail()->getPData()->getCustomerNumber() << endl;
	cout << "Dequeueing..." << endl;
	two.dequeue();
	two.dequeue();
	if (two.getPHead() == two.getPTail() && two.isEmpty()) {
		cout << "Successfully dequeued two nodes" << endl;
	}
	else {
		cout << "Test failed. Was not able to dequeue two nodes in the queue";
	}
}

//Runs simulation for 24 hours 1440 minutes
void testDaySimulation() {
	Simulation twentyfourhrSim;
	twentyfourhrSim.run(1440);	// run sim for 24hrs
}