#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <vector>
#include <string>
#include"filesystemv2.h"

#define ArraySize 32 //tymczasowy ram


enum class processState : char
{ 
	active = 0, waiting = 1, ready = 2, terminated = 3
};


class PCB
{
private:
	int PID;
	std::string processName;
	std::string fileName;
	int staticPriority;
	int dynamicPriority;
	int processCounter;
	char AX, BX, CX, DX, Flag;

	//static int processCounter;
public:
	processState state;
	int instructionPointer;
	file_system files;
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
=======

	int staticPriority;
	int dynamicPriority;
	int average_sleep_time;
=======
>>>>>>> parent of 879d2e6... dodatkowe funkcje w swoim module plus zmienne w pcb
=======
>>>>>>> parent of 879d2e6... dodatkowe funkcje w swoim module plus zmienne w pcb
	int whenStartWaiting, whenStartRunning;
	int static_process_priorety, dynamic_process_priorety;
	int average_sleep_time;

	
>>>>>>> parent of 3efabb1... elele
	
	PCB();
	PCB(std::string processName, std::string fileName, int staticPriority);
	PCB* parent;
	std::list<PCB*> children;
	int getPID();
	void displayProcess();
	std::string getProcessName();
	processState getProcessState();
	processState setProcessState(processState newState);
	void displayChildren(unsigned int PID); //pomocnicza metoda, do usuniecia potem
	
	//metody i zmienne potrzebne Interpreterowi
	
	char memory[ArraySize]; //tymczasowy ram
	int startIndex = 4;

	bool isOutRange(char adrr) 
	{ 
		return adrr >= 0 && adrr < ArraySize; 
	}

	std::shared_ptr<std::vector<std::string>> program;
	

	bool loadProgramFromFile(std::string fileName) 
	{
		std::string bufor;
		std::ifstream input(fileName);
		if (input.good() == true)
		{
			while (input >> bufor)
			{
				this->program->push_back(bufor);
			}
			input.close();
			return true;
		}
		else
		{
			std::cout << "Nie znaleziono wskazanego pliku lub plik jest uszkodzony.";
			return false;
		}
	}

	void writeInMemory(int adrr, char value) 
	{
		adrr += startIndex;
		this->memory[adrr] = value;
	}
	char readFromMemory(char adrr) 
	{
		adrr += startIndex;
		return memory[adrr];
	}

	char getAX() const { return AX; }
	char getBX() const { return BX; }
	char getCX() const { return CX; }
	char getDX() const { return DX; }
	char getFlags() const{return Flag;}

	void setAX(char value) { AX = value; } //ustawia wartosc value w danym rejestrze
	void setBX(char value) { BX = value; }
	void setCX(char value) { CX = value; }
	void setDX(char value) { DX = value; }
	void setFlags(char value) {Flag = value;}

	void printMemory()
	{
		for (int i = 0; i < ArraySize; ++i) { std::cout << static_cast<int>(memory[i]) << "|"; }
	}
};
