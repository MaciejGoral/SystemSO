#pragma once
#include <queue>
#include "Process.hpp"

class Semaphore
{
public:
	Semaphore(int value_);


	void wait();
	void signal();

	int get_value();
	
private:
	int Value;
	std::queue<PCB*> Waiting_Processes;
};

