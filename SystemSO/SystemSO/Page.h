#pragma once
#include <string>
struct PageTable // tablica stronic indeks->nrStronicy tworze dla ka¿dego procesu
{
	int ramka_zajeta; // ramka w ktorej znajduje sie stronica
	bool bit; // bit sprawdzajacy czy stronica jest w pamieci

	PageTable(int frame, bool bit) {
		this->ramka_zajeta = frame;
		this->bit = bit;
	}

	PageTable();

};

class Page
{
public:
	std::string str = "";
	int licznik = 0;
	PageTable* pageTable;
	int pageTableSize;
	void UstTabStronic(PageTable* newpageTable);			//Przemkowe RAM'y
	PageTable* PobTabStronic();
	void UstWielTabStronic(int num);
	int PobWielTabStronic();
	void UstWielLicznika(int num);
	int PobWielLicznika();
};