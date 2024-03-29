#include "Process.hpp"
#include "ProcessManager.hpp"
#include <list>
#include <iostream>

<<<<<<< HEAD
//int PCB::processCounter = 0;
extern int pidCounter;
=======
int PCB::processCounter = 0;
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> parent of e1b1b34... ło
=======
>>>>>>> parent of e1b1b34... ło
=======
>>>>>>> parent of e1b1b34... ło

PCB::PCB() {
	AX = BX = CX = DX = Flag = instructionPointer = 0;
	//this->PID = ++processCounter;
}
PCB::PCB(std::string processName, std::string filename, int staticpriority) : PCB()
{
	this->processName = processName;
	this->fileName = filename + ".txt";
	this->state = processState::ready;
	this->staticPriority = staticpriority;
	this->dynamicPriority = staticPriority;
	//this->processCounter = pidCounter;
	this->PID = pidCounter;
	loadProgramFromFile(fileName); //odczyt programu z pliku
}

int PCB::getPID()
{
	return PID;
}

void PCB::displayProcess()
{
	std::string sState;
	switch (state)
	{
	case processState::active:
		sState = "Active";
		break;
	case processState::waiting:
		sState = "Waiting";
		break;
	case processState::ready:
		sState = "Ready";
		break;
	case processState::terminated:
		sState = "Terminated";
		break;
	}

	std::cout << "PID: " << PID << " | Process name: " << processName << " | File name: " << fileName << " | State: " << sState << " | Static priority: " << staticPriority << " | Dynamic priority: " << dynamicPriority << "\n";
}

std::string PCB::getProcessName()
{
	return processName;
}


void PCB::displayChildren(unsigned int PID)
{
	for (auto child : children)
	{
		child->displayProcess();
	}
}


processState PCB::getProcessState()
{
	return state;
}


processState PCB::setProcessState(processState newState)
{
	state = newState;
	return state;
}