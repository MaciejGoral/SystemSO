#include <iostream>
#include <string>
#include "Process.hpp"
#include "ProcessManager.hpp"
#include "Shell.h"
//za��czcie tu swoje klasy

ProcessManager* processManager;
PCB* runningProcess;
int pidCounter = 1;


int main()
{
	Shell shell;
	std::string komenda;//zmienna pomocnicza do uzyskania linii z konsoli
	while (shell.on_off) //p�tla g��wna systemu
	{
		std::getline(std::cin, komenda);
		shell.wybierz_metode(komenda);
	}
	return 0;
}