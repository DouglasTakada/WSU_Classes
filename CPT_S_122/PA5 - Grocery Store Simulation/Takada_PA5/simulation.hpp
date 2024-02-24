#pragma once
#include "queue.hpp"

class Simulation {
public:
	Simulation(int newMinutes = 0);
	~Simulation();

	void run(int numMins);

private:
	int minutes;
};