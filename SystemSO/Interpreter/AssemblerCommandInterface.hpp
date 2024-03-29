#pragma once
#include<string>
#include<vector>
#include<memory>
#include"Flags.hpp"
#include"../SystemSO/Process.hpp"
#include"Conversion.hpp"

class AssembleCommandInterface {
public:
	virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0) = 0;
};