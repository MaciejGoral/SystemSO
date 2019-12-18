#pragma once
#include<map>
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include "CommandScript/AssemblerCommandFactory.hpp"
=======
=======
>>>>>>> parent of e1b1b34... ło
=======
>>>>>>> parent of 879d2e6... dodatkowe funkcje w swoim module plus zmienne w pcb
#include"PCB.hpp"
#include"CommandScript/AssemblerCommandFactory.hpp"
>>>>>>> parent of e1b1b34... ło

class Interpreter
{
protected:
	std::map<std::string, std::unique_ptr<AssembleCommandInterface>> functionList;
public:
	std::shared_ptr<PCB> pcb;
	std::unique_ptr<AssemblerCommandFactory> commandFactory;

	Interpreter();
	Interpreter(std::shared_ptr<PCB>& pcb_ptr);
	~Interpreter();

	int step(int instructionPosition);
	int stepWithDebug(int instructionPosition);

	std::shared_ptr<PCB>& getPCB();
};

