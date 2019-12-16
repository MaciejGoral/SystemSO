#pragma once
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <regex>
#include <fstream>
#include <vector>
#include <string>

#define ArraySize 32 //tymczasowy ram


enum processState
{ 
	active = 0, waiting = 1, ready = 2, terminated = 3
};


class PCB
{
private:
	int PID;
	processState state;
	std::string processName;
	std::string fileName;
	char AX, BX, CX, DX;

public:
	PCB();
	PCB(std::string processName, std::string fileName);
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

	bool status = true;
	std::shared_ptr<std::vector<std::string>> program;
	

	static std::shared_ptr<PCB> loadProgramFromFile(std::string fileName) 
	{
		std::shared_ptr<PCB> result = std::make_shared<PCB>();
		std::string bufor;
		std::ifstream input(fileName);
		if (input.good() == true)
		{
			while (input >> bufor)
			{
				result->program->push_back(bufor);
			}
			input.close();
			return result;
		}
		else
		{
			std::cout << "Nie znaleziono wskazanego pliku lub plik jest uszkodzony.";
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

	char getAX() { return memory[0]; }
	char getBX() { return memory[1]; }
	char getCX() { return memory[2]; }
	char getDX() { return memory[3]; }

	void setAX(char value) { memory[0] = value; } //ustawia wartosc value w danym rejestrze
	void setBX(char value) { memory[1] = value; }
	void setCX(char value) { memory[2] = value; }
	void setDX(char value) { memory[3] = value; }

	void printMemory()
	{
		for (int i = 0; i < ArraySize; ++i) { std::cout << static_cast<int>(memory[i]) << "|"; }
	}
};