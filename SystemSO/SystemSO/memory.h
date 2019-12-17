#pragma once
#include <iostream>
#include "Page.h"
#include <string>

using namespace std;
/*
class Page {

	std::string str = "";
	int licznik = 0;
	PageTable* pageTable;
	int pageTableSize;
	void UstTabPageTableic(PageTable* newpageTable);			//Przemkowe RAM'y
	PageTable* PobTabStronic();
	void UstWielTabStronic(int num);
	int PobWielTabStronic();
	void UstWielLicznika(int num);
	int PobWielLicznika();
};*/
class Memory {


private:


	const int RAM_SIZE =256; // rozmiar pamieci 256B
	const int FRAME_SIZE = 16; // rozmiar ramki oraz stronicy
	const int FRAME_COUNT = RAM_SIZE / FRAME_SIZE; // ILOSC RAMEK
	bool Is_free(int, int); //sprawdza czy dany obszar pamieci jest wolny
	

	char * RAM; //tablica symulujaca RAM
	list<int>freeMemoryFrames; //lista wolnych ramek w RAM

		//---Zapewnienie wolnej ramy Procesowi---//
	const void ZapewnijWolnaRamke();//=Zapewnienie ¿e rama jest wolna
	//---Odczyt Pamieci---//
	const char OdczytajZPamieci(int PID, int addr1, Page *g);
	//---Zapisanie danych w PAMRam---//
	const void ZapiszWPamieci(int PID, int addr1, char element, Page *g);
	//---Zapewnienie miejsca dla Strony w pamieci ram---//
	const void ZapewnijStroneWPamieci(int PID, int logicalAddress, Page *g);
	//---Pobranie Ramy z pamieci dla procesu---//
	const int PobierzWolnaRamkePamieci();

	//---Obliczenia zwiazane z ramem i plikiem wym---//
	const int ObliczNumerStrony(int addr1);
	//FIFO
	const bool BrakMieWPowAdr(int PID, int logicalAddress, Page *g);
	// oblicza logiczny na fizyczny
	const int ObliczAdresFizyczny(int PID, int addr1, Page *g);


public:



	void PIDproces(int PID, string plik, Page *g);
	const void Show_RAM_state(int DoWypis =0); //pokaze wszystkie informacje o pamieci
	const void WydrukujRame(int RamaNr, int PageNr = -1);
	char ZwrocZnak(int indeks); ///FUNKCJA DLA INTERPRETERA, ZWRACAJACA ZNAK ZNAJDUJACY SIE POD DANYM INDEKSEM
	const void PrzydzialPamieci(int PID, string proces, int size, Page *g);

	Memory();
	~Memory();
};
