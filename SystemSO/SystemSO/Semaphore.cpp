#include "Semaphore.h"
#include "filesystemv2.h"

extern PCB* runningProcess;

Semaphore::Semaphore(int value_) : Value(value_), Waiting_Queue(nullptr)
{
}

void Semaphore::wait(bool Mutex)
{
	Value--;
	if (Value < 0)
	{
		runningProcess->setProcessState(processState::waiting);
		Waiting_Queue->push(runningProcess, Mutex);
	}
}

void Semaphore::signal()
{
	Value+= pop();
}

int Semaphore::get_value()
{
	return Value;
}

void Semaphore::push(PCB* PCB_, bool writing_)
{
	if (Waiting_Queue == nullptr) Waiting_Queue = new PCB_queue(PCB_, writing_);
	else Waiting_Queue->push(PCB_, writing_);
}

int Semaphore::pop()
{
	int waked = 0;
	if (Waiting_Queue != nullptr)
	{
		while (!Waiting_Queue->Waiting_PCB.empty())
		{
			waked++;
			Waiting_Queue->Waiting_PCB.front()->setProcessState(processState::ready);
			Waiting_Queue->Waiting_PCB.pop();
		}
		PCB_queue* temp = Waiting_Queue;
		Waiting_Queue = Waiting_Queue->Next;
		delete temp;
	}
	return waked;
}

PCB_queue::PCB_queue(PCB* PCB_, bool writing_) : Next(nullptr), Writing(writing_)
{
	Waiting_PCB.push(PCB_);
};

void PCB_queue::push(PCB* PCB_, bool writing_)
{
	if (!writing_ && !Writing) Waiting_PCB.push(PCB_);
	else if (Next == nullptr) Next = new PCB_queue(PCB_, writing_);
	else Next->push(PCB_, writing_);
}
