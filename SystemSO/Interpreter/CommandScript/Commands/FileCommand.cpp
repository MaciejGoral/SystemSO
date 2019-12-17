#include"FileCommand.hpp"
#include"../../../SystemSO/filesystemv2.h"

char command::OpenFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	char argv = 1;
	std::vector<ArgumentType> args = this->loadArgs(argv, startArgs, pcb);
	if (args.size() != argv) { throw std::exception("Failed loading arguments"); }


	return startArgs+argv;
}

char command::CloseFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}

char command::GetPositionInFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}

char command::AppendStringFromRamToFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}

char command::AppendCharToFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}

char command::AppendStringProgramCodeToFile::doCommand(std::shared_ptr<PCB>& pcb, char startArgs)
{
	return 0;
}
