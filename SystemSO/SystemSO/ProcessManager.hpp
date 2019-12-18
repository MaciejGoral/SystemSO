#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Process.hpp"
<<<<<<< HEAD
=======
#include "..\Interpreter\Interpreter.hpp"
>>>>>>> parent of 879d2e6... dodatkowe funkcje w swoim module plus zmienne w pcb



class ProcessManager
{
public:
	std::list<PCB*> allProcesses;
	std::list<PCB*> readyProcesses;
	std::list<PCB*> waitingProcesses;
	ProcessManager();

	void createProcess(std::string processName, std::string fileName, int staticPriority);
	void createInitProcess();
	void displayAllProcesses();
	void displayReadyProcesses();
	void displayWaitingProcesses();
	void removeProcessByName(std::string processName);
	bool ifProcessExists(std::string processName);
	PCB* findProcess(std::string processName);
	void removeProcessFromWaiting(std::string processName);
	void removeProcessFromReady(std::string processName);
	void setWaitingStatusToProcess(std::string processName);
	void setReadyStatusToProcess(std::string processName);
};
