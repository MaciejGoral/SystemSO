#pragma once
#include <queue>
#include "Process.hpp"

struct PCB_queue
{
	PCB_queue(PCB* PCB_, bool writing_);

	void push(PCB* PCB_, bool writing_);

	PCB_queue* Next;
	bool Writing;
	std::queue<PCB*> Waiting_PCB;

};

class Semaphore
{
public:
	Semaphore(int value_);


	void wait(bool Mutex);
	void signal();

	int get_value();
	
private:
	void push(PCB* PCB_, bool writing_);
	int pop();

	int Value;
	PCB_queue* Waiting_Queue;
};

