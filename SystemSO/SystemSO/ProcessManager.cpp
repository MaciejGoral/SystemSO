#include <iostream>
#include <string>
#include <list>
#include "ProcessManager.hpp"
#include "Process.hpp"


extern PCB* runningProcess;

ProcessManager::ProcessManager()
{
	createInitProcess();
}


void ProcessManager::createInitProcess()
{
	PCB* newProcess = new PCB("init","init", 139);
	newProcess->parent = nullptr;
	allProcesses.push_back(newProcess);
	readyProcesses.push_back(newProcess);
	runningProcess = newProcess;
}


void ProcessManager::createProcess(std::string processName, std::string fileName, int staticPriority)
{
	PCB *newProcess = new PCB(processName, fileName, staticPriority);
	newProcess->parent = findProcess("init");
	newProcess->parent->children.push_back(newProcess);
	allProcesses.push_back(newProcess);
	readyProcesses.push_back(newProcess);
	runningProcess = newProcess;
}


void ProcessManager::displayAllProcesses()
{
	if (allProcesses.empty() == true)
	{
		std::cout << "Lista jest pusta.\n";
	}
	else
	{
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::displayReadyProcesses()
{
	if (readyProcesses.empty() == true)
	{
		std::cout << "Lista procesow gotowych jest pusta\n";
	}
	else
	{
		for (auto it = readyProcesses.begin(); it != readyProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::displayWaitingProcesses()
{
	if (waitingProcesses.empty() == true)
	{
		std::cout << "Lista procesow oczekujacych jest pusta\n";
	}
	else
	{
		for (auto it = waitingProcesses.begin(); it != waitingProcesses.end(); it++)
		{
			(*it)->displayProcess();
		}
	}
}


void ProcessManager::removeProcessByName(std::string processName)
{
	if (processName == "init")
	{
		std::cout << "Nie mozna usunac procesu 'init'\n";
	}
	else if (ifProcessExists(processName) == false)
	{
		std::cout << "Nie znaleziono wskazanego procesu.\n";
	}
	else
	{
		PCB* process = findProcess(processName);
		
		if (process == runningProcess)
		{
			runningProcess = findProcess("init");
		}
		if (process->getProcessState() == processState::waiting)
		{
			std::cout << "Nie mozna usunac procesu ze statusem 'waiting'\n";
		}
		else if (process->children.empty() == true)
		{
			removeProcessFromReady(process->getProcessName()); //usuwanie z gotowych
			process->parent->children.remove(process); //usuwanie z listy dzieci rodzica
			allProcesses.remove(process);
			// tutaj metoda zwalniajaca przydzielony RAM procesowi, zwalnianie ramu
			delete process;
		}
		else if (process->children.empty() == false)
		{
			for (auto child : process->children)
			{
				process->parent->children.push_back(child);
				process->children.remove(child);
			}
			removeProcessFromReady(process->getProcessName());
			process->parent->children.remove(process);
			allProcesses.remove(process);
			// tutaj metoda zwalniajaca przydzielony RAM procesowi, zwalnianie ramu
			delete process;
		}
	}
}


PCB* ProcessManager::findProcess(std::string processName)
{
	for (auto it : allProcesses)
	{
		if (it->getProcessName() == processName)
		{
			return it;
			break;
		}
	}
}


bool ProcessManager::ifProcessExists(std::string processName)
{
	for (auto it = allProcesses.begin(); it != allProcesses.end(); it++)
	{
		if ((*it)->getProcessName() == processName)
		{
			return true;
			break;
		}
	}
	return false;
}


void ProcessManager::removeProcessFromReady(std::string processName)
{
	PCB* process = findProcess(processName);
	readyProcesses.remove(process);
}


void ProcessManager::removeProcessFromWaiting(std::string processName)
{
	PCB* process = findProcess(processName);
	waitingProcesses.remove(process);
}


void ProcessManager::setWaitingStatusToProcess(std::string processName)
{
	PCB* process = findProcess(processName);

	for (auto it = readyProcesses.begin(); it != readyProcesses.end(); it++)
	{
		if ((*it)->getProcessName() == processName)
		{
			readyProcesses.remove(process);
			break;
		}
	}
	process->setProcessState(processState::waiting);
	waitingProcesses.push_back(process);
}


void ProcessManager::setReadyStatusToProcess(std::string processName)
{
	PCB* process = findProcess(processName);

	for (auto it = waitingProcesses.begin(); it != waitingProcesses.end(); it++)
	{
		if ((*it)->getProcessName() == processName)
		{
			waitingProcesses.remove(process);
			break;
		}
	}
	process->setProcessState(processState::ready);
	readyProcesses.push_back(process);
}
