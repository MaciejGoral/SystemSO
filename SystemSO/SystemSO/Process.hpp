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
	std::string processName;
	std::string fileName;
	char AX, BX, CX, DX, Flag;

public:
	processState state;
	int instructionPointer;
	
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

	char getAX() const { return AX; }
	char getBX() const { return BX; }
	char getCX() const { return CX; }
	char getDX() const { return DX; }
	char getFlage() const{return Flag;}

	void setAX(char value) { AX = value; } //ustawia wartosc value w danym rejestrze
	void setBX(char value) { BX = value; }
	void setCX(char value) { CX = value; }
	void setDX(char value) { DX = value; }
	void setFlag(char value) {Flag = value;}

	void printMemory()
	{
		for (int i = 0; i < ArraySize; ++i) { std::cout << static_cast<int>(memory[i]) << "|"; }
	}
};
