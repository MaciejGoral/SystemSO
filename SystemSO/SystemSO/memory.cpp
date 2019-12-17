#include <iostream>
#include <list>
#include "memory.h"


using namespace std;

Memory m;



const void Memory::Show_RAM_state(int DoWypis) {
	if (DoWypis <= 0 || DoWypis > FRAME_COUNT)
		DoWypis = FRAME_COUNT;

	for (int i = 0; i < DoWypis; i++)
	{
		WydrukujRame(i);
	}
}

const void Memory::WydrukujRame(int RamaNr, int PageNr)
{
	int addr = RamaNr * FRAME_SIZE;
	string space = "        ";
	cout << "Ramka nr: " << RamaNr;
	if (PageNr >= 0)
	{
		cout << ", zawiera strone nr: " << PageNr;
	}
	cout << endl;

	for (int i = 0; i < FRAME_SIZE; i++)
	{
		if (addr + i < 10)
			printf("  %d  |", addr + i);
		else
			printf(" %3d |", addr + i);
	}
	cout << endl;
	// wyzwietla zawartosc RAMu
	addr = RamaNr * FRAME_SIZE;

	for (int i = 0; i < FRAME_SIZE; i++)
	{
		printf("  %c  |", RAM[addr + i]);

	}
	cout << endl;
	// ----------------------------------------------------------------------
	// wyzwietla spod ramki
}


void Memory::PIDproces(int PID, string plik, Page *g) {
	int ADDR = 0;
	//PrzydzialPamieci(PID, plik, plik.length(), g);
	/*ADDR = WolneRamki.front();
	WolneRamki.pop_front();*/

	/*
	for (int IndeksPlik = 0; IndeksPlik < plik.length(); IndeksPlik++)
	{
		ZapiszWPamieci(PID, ADDR + IndeksPlik, plik[IndeksPlik], g);
	}*/
}

const void Memory::ZapiszWPamieci(int PID, int addr1, char element, Page *g) {
	if (BrakMieWPowAdr(PID, addr1, g)) {
		cout << "Out of Range / Brak miejsca mordeczko" << endl;
		return;
	}
	ZapewnijStroneWPamieci(PID, addr1, g);
	int p_Addr = ObliczAdresFizyczny(PID, addr1, g);
	RAM[p_Addr] = element;
}

const void Memory::ZapewnijStroneWPamieci(int PID, int AdresLogiczny, Page *g) {
	PageTable * TabelaStron = g->PobTabStronic();

	int NumerPam = ObliczNumerStrony(AdresLogiczny);

}

const bool Memory::BrakMieWPowAdr(int PID, int AdresLogiczny, Page *g) {
	int NumerStrony = ObliczNumerStrony(AdresLogiczny);
	if (NumerStrony >= g->PobWielTabStronic())
		return true;
	else
		return false;
}

const int Memory::ObliczNumerStrony(int addr1) {
	return (addr1 & 0xf0) >> 4;
}

const int Memory::ObliczAdresFizyczny(int PID, int addr1, Page *g) {
	PageTable * TablicaStronic = g->PobTabStronic();
	int NumerStrony = ObliczNumerStrony(addr1);
	//int offset = ObliczOffset(addr1);
	if (TablicaStronic[NumerStrony].ramka_zajeta) {
		int NumerRamy = TablicaStronic[NumerStrony].ramka_zajeta;
		return NumerRamy * FRAME_SIZE;
	}
	else {
		return 99999;
	}
}

char Memory::ZwrocZnak(int Addr) {
	if (Addr >= 0 && Addr <= 255) {
		return RAM[Addr];
	}
	else {
		cout << "Zly Adres";
	}
}

Memory::Memory()
{
	RAM = new char[RAM_SIZE];

	for (int i = 0; i < RAM_SIZE; i++)
	{
		RAM[i] = ' ';
	}
	for (int i = 0; i < FRAME_COUNT; i++)
		freeMemoryFrames.push_back(i);

	Page *g = new Page;
	m.PIDproces(0, "JP 0", g);
}
Memory::~Memory()
{
	delete[] RAM;
}

	int main() 
	{
		m.Show_RAM_state();
		system("pause");
	}