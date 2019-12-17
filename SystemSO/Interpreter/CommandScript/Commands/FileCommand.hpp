#pragma once
#include"../AssemblerTranslator.hpp"

namespace command {
	class OpenFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class CloseFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class AppendCharToFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class AppendStringFromRamToFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class AppendStringProgramCodeToFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
	class GetPositionInFile : public AssemblerTranslator {
	public:
		virtual char doCommand(std::shared_ptr<PCB>& pcb, char startArgs = 0);
	};
}