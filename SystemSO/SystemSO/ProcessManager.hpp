#pragma once
#include <iostream>
#include <list>
#include <string>
#include "Process.hpp"
#include "..\Interpreter\Interpreter.hpp"



class ProcessManager
{
public:
	std::list<PCB*> allProcesses;
	std::list<PCB*> readyProcesses;
	std::list<PCB*> waitingProcesses;
	PCB* runningProcess;
	ProcessManager();

	void createProcess(std::string processName, std::string fileName);
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
