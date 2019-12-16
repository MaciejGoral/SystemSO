#include "Semaphore.h"
#include "filesystemv2.h"

extern PCB* runningProcess;

Semaphore::Semaphore(int value_) : Value(value_)
{
}

void Semaphore::wait()
{
	Value--;
	if (Value < 0)
	{
		Waiting_Processes.push(runningProcess);
		runningProcess->setProcessState(processState::waiting);
		return;
	}
	else return;
}

void Semaphore::signal()
{
	Value++;
	if (!Waiting_Processes.empty())
	{
		Waiting_Processes.front()->setProcessState(processState::ready);
		Waiting_Processes.pop();
		return;
	}
	else return;
}

int Semaphore::get_value()
{
	return Value;
}