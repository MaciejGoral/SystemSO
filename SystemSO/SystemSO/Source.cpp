#include <iostream>
#include <string>
#include "Shell.h"
//za³¹czcie tu swoje klasy
int main()
{
	Shell shell;
	std::string komenda;//zmienna pomocnicza do uzyskania linii z konsoli
	while (shell.on_off) //pêtla g³ówna systemu
	{
		std::getline(std::cin, komenda);
		shell.wybierz_metode(komenda);
	}
	return 0;
}