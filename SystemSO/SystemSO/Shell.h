#include <vector>
#include <string>
#include <iostream>
#include"Interpreter/Interpreter.hpp"
class Shell
{
public:
	Interpreter interpreter;
	bool on_off;

	Shell();
	void wybierz_metode(std::string komenda); //metoda wybieraj¹ca polecenie

	void CP(std::string nazwa_procesu, std::string nazwa_pliku, int staticPriority); //utworzenie procesu
	void DP(std::string nazwa_procesu); //usuwanie procesu
	void EXE(); //wykonanie kolejnego rozkazu procesu
	void SP(std::string nazwa); //wyœwietla parametry procesu

	void DAP(); //wyœwietla wszystkie procesy
	void DWP(); //wyœwietla oczekuj¹ce procesy
	void DRP(); //wyœwietla gotowe procesy

	void SR(); //wyœwietla zawartoœci ca³ej pamiêci RAM
	void SRR(); //wyœwietla pamiêæ RAM od wskazanego adresu o wskazanej wielkoœci
	void PH(); //pokazuje adres fizyczny
	void LH(); //pokazuje adres logiczny
	void LA(); //³aduje ca³y program do RAMU
	void PT(); //pokazuje tablice stronnic

	void LD(); //metoda wyœwietlaj¹ca zawartoœæ
	void CFF(std::string nazwa_pliku); //tworzy plik
	void DF(std::string nazwa_pliku); //usuwa plik
	void RF(std::string nazwa_pliku, std::string nowa_nazwa); //zmiana nazwy pliku
	void AP(std::string nazwa, std::string dane); //dopisywanie do pliku
	void OF(std::string nazwa, std::string dane); //nadpisywanie pliku
	void RDF(std::string nazwa); //wyœwietlanie zawartoœci pliku
	void RDFF(std::string nazwa, int pozycja_poczatkowa, int ilosc_znakow); //wyœwietlanie czesci zawartoœci pliku

	void EXIT(); //zamkniêcie systemu
	void HELP(); //wyœwietlenie dostêpnych komend

};

