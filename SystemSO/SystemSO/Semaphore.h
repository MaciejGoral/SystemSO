#pragma once
#include <queue>
#include "Process.hpp"

class Semaphore
{
public:
	static std::shared_ptr<PCB> runningProcess;

	Semaphore(int value_);


	void wait();
	void signal();

	int get_value();
	
private:
	int Value;
	std::queue<std::shared_ptr<PCB>> Waiting_Processes;
};

