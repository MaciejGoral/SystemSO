#include <iostream>
#include <vector>
#include <string>
#include "Shell.h"
#include <iterator>
#include <sstream>
#include <fstream>
using namespace std;
Shell::Shell()
{
	on_off = true;
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

void Shell::CP(std::string nazwa_procesu, std::string nazwa_pliku)
{
	//ProcessManager->createProcess(nazwa_procesu,nazwa_pliku);
}

void Shell::DP(std::string nazwa_procesu)
{
	//ProcessManager->killProcess(nazwa_procesu);
}

void Shell::EXE()
{
	//interpreter->step()
}

void Shell::SP(std::string nazwa)
{
	//ProcessManager->displayProcess(nazwa);
}

void Shell::DAP()
{
	//Processmanager->displayAllProcesses();
}

void Shell::DWP()
{
	//Processmanager->displayWaitingProcesses();
}

void Shell::DRP()
{
	//Processmanager->displayReadyProcesses();
}

void Shell::SR()
{
	//modu³_zarz¹dzania_pamieci¹->showRam();

}

void Shell::SRR(int adres_pocz¹tkowy, int rozmiar)
{
	//modu³_zarz¹dzania_pamieci¹->showRamRange(adres_pocz¹tkowy,rozmiar);
}

void Shell::LD()
{
	//modu³_zarz¹dzania_plikami->listDirectory();
}

void Shell::CF(std::string nazwa_pliku)
{
	//modu³_zarz¹dzania_plikami->utworz_plik(nazwa_pliku);
}

void Shell::DF(std::string nazwa_pliku)
{
	//modu³_zarz¹dzania_plikami->usun_plik(nazwa_pliku);
}

void Shell::RF(std::string nazwa_pliku, std::string nowa_nazwa)
{
	//modu³_zarz¹dzania_plikami->zmien_nazwe_pliku(nazwa_pliku,nowa_nazwa);
}

void Shell::AP(std::string nazwa, std::string dane)
{
	//modu³_zarz¹dzania_plikami->dopisz_do_pliku(nazwa,dane);
}

void Shell::OF(std::string nazwa, std::string dane)
{
	//modu³_zarz¹dzania_plikami->nadpisz_plik(nazwa,dane);
}

void Shell::RDF(std::string nazwa)
{
	//modu³_zarz¹dzania_plikami->czytaj_plik(nazwa);
}

void Shell::RDFF(std::string nazwa, int pozycja_poczatkowa, int ilosc_znakow)
{
	//modu³_zarz¹dzania_plikami->czytaj_fragment_pliku(nazwa, dane);
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
		if (polecenie.size() != 4)
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			CP(polecenie[1], polecenie[2]);
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
		if (polecenie.size() != 4 && numer(polecenie[1]) && numer(polecenie[2]))
		{
			cout << "Komenda zawiera nieprawidlowa liczbe argumentow" << endl;
		}
		else
		{
			SRR(stoi(polecenie[1]), stoi(polecenie[2]));
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
			CF(polecenie[1]);
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
