#include <iostream>
#include <vector>
#include <string>
#include "Shell.h"
#include "Process.hpp"
#include "ProcessManager.hpp"
#include <iterator>
#include <sstream>
#include <fstream>
#include "Memory.h"
#include "memory.cpp"
#include "filesystemv2.cpp"
#include "Interpreter/Interpreter.hpp"
using namespace std;

extern ProcessManager* processManager;
Memory mem1;
file_system fs;
Shell::Shell()
{
	on_off = true;
	processManager = new ProcessManager();
	//wpiszcie tu wszystko co musi sie wydarzy na starcie wystemu
}

bool numer(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it))
	{
		++it;
	}
	return !s.empty() && it == s.end();
}

void Shell::CP(std::string nazwa_procesu, std::string nazwa_pliku, int staticPriority)
{
	int number;
	std::istringstream iss(staticPriority);
	iss >> number;
	processManager->createProcess(nazwa_procesu, nazwa_pliku, number);
	mem1.createProcess(nazwa_pliku);
}

void Shell::DP(std::string nazwa_procesu)
{
	processManager->removeProcessByName(nazwa_procesu);
	mem1.deleteProcess;
}

void Shell::EXE()
{
	interpreter.pcb->instructionPointer = interpreter.step(interpreter.pcb->instructionPointer);
}

void Shell::SP(std::string nazwa)
{
	processManager->findProcess(nazwa)->displayProcess();
}

void Shell::DAP()
{
	processManager->displayAllProcesses();
}

void Shell::DWP()
{
	processManager->displayWaitingProcesses();
}

void Shell::DRP()
{
	processManager->displayReadyProcesses();
}

void Shell::SR()
{
	mem1.showMemory();

}

void Shell::SRR()
{
	mem1.showProcessInMemory();
}

void Shell::PH()
{
	mem1.showCharPhysicAddr();
}
void Shell::LH()
{
	mem1.showCharLogicAddr();
}
void Shell::LA()
{
	mem1.LoadAllProcessToMemory();
}
void Shell::PT()
{
	mem1.showPageTable();
}

void Shell::LD()
{
	fs.display_all_information_about_all_files();
}

void Shell::CFF(std::string nazwa_pliku)
{
	fs.create_file_v2(nazwa_pliku);
}
void Shell::DF(std::string nazwa_pliku)
{
	fs.delete_file_v2(nazwa_pliku);
}

void Shell::RF(std::string nazwa_pliku, std::string nowa_nazwa)
{
	fs.rename_file_v2(nazwa_pliku, nowa_nazwa);
}

void Shell::AP(std::string nazwa, std::string dane)
{
	fs.add_in_data_to_file_v2(nazwa, dane);
}

void Shell::OF(std::string nazwa, std::string dane)
{
	fs.overwrite_data_to_file_v2(nazwa, dane);
}

void Shell::RDF(std::string nazwa)
{
	fs.display_file_v2(nazwa);
}

void Shell::RDFF(std::string nazwa, int pozycja_poczatkowa, int ilosc_znakow)
{
	fs.display_part_of_file(nazwa, pozycja_poczatkowa, ilosc_znakow);
}

void Shell::EXIT()
{
	on_off = false;
}

void Shell::HELP()
{
	string line;

	ifstream plik("help.txt");
	if (plik.is_open())
	{
		while (getline(plik, line))
		{
			cout << line << endl;
		}
		plik.close();
	}
	else
	{
		cout << "Nie mozna otworzyc pliku" << endl;
	}
}

void Shell::wybierz_metode(std::string komenda)
{
	//wpisywanie slow do vectora
	istringstream pom(komenda);
	vector<std::string> polecenie;
	do
	{
		string slowo;
		pom >> slowo;
		polecenie.push_back(slowo);
	} while (pom);
	if (polecenie[0] == "CP")
	{
		if (polecenie.size() != 5)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			CP(polecenie[1], polecenie[2], stoi(polecenie[3]));
		}
	}
	else if (polecenie[0] == "DP")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DP(polecenie[1]);
		}
	}
	else if (polecenie[0] == "EXE")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			EXE();
		}
	}
	else if (polecenie[0] == "SP")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			SP(polecenie[1]);
		}
	}
	else if (polecenie[0] == "DAP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DAP();
		}
	}
	else if (polecenie[0] == "DWP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DWP();
		}
	}
	else if (polecenie[0] == "DRP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DRP();
		}
	}
	else if (polecenie[0] == "SR")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			SR();
		}
	}
	else if (polecenie[0] == "SRR")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			SRR();
		}
	}
	else if (polecenie[0] == "PH")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			PH();
		}
	}
	else if (polecenie[0] == "LH")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			LH();
		}
	}
	else if (polecenie[0] == "LA")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			LA();
		}
	}
	else if (polecenie[0] == "PT")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			PT();
		}
	}
	else if (polecenie[0] == "LD")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			LD();
		}
	}
	else if (polecenie[0] == "CF")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			CFF(polecenie[1]);
		}
	}
	else if (polecenie[0] == "DF")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			DF(polecenie[1]);
		}
	}
	else if (polecenie[0] == "RF")
	{
		if (polecenie.size() != 4)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			RF(polecenie[1], polecenie[2]);
		}
	}
	else if (polecenie[0] == "AP")
	{
		if (polecenie.size() != 4)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			AP(polecenie[1], polecenie[2]);
		}
	}
	else if (polecenie[0] == "OF")
	{
		if (polecenie.size() != 4)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			OF(polecenie[1], polecenie[2]);
		}
	}
	else if (polecenie[0] == "RDF")
	{
		if (polecenie.size() != 3)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			RDF(polecenie[1]);
		}
	}
	else if (polecenie[0] == "RDFF" && numer(polecenie[2]) && numer(polecenie[3]))
	{
		if (polecenie.size() != 5)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			RDFF(polecenie[1], stoi(polecenie[2]), stoi(polecenie[3]));
		}
	}
	else if (polecenie[0] == "EXIT")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			EXIT();
		}
	}
	else if (polecenie[0] == "HELP")
	{
		if (polecenie.size() != 2)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			HELP();
		}
	}
	else
	{
		cout << "Nieprawidlowe polecenie" << endl;
	}
}
