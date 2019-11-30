#include <vector>
#include <string>
#include <iostream>
class Shell
{
public:
	bool on_off;

	Shell();
	void wybierz_metode(std::string komenda); //metoda wybieraj�ca polecenie

	void CP(std::string nazwa_procesu, std::string nazwa_pliku); //utworzenie procesu
	void DP(std::string nazwa_procesu); //usuwanie procesu
	void EXE(); //wykonanie kolejnego rozkazu procesu
	void SP(std::string nazwa); //wy�wietla parametry procesu

	void DAP(); //wy�wietla wszystkie procesy
	void DWP(); //wy�wietla oczekuj�ce procesy
	void DRP(); //wy�wietla gotowe procesy

	void SR(); //wy�wietla zawarto�ci ca�ej pami�ci RAM
	void SRR(int adres_pocz�tkowy, int rozmiar); //wy�wietla pami�� RAM od wskazanego adresu o wskazanej wielko�ci

	void LD(); //metoda wy�wietlaj�ca zawarto��
	void CF(std::string nazwa_pliku); //tworzy plik
	void DF(std::string nazwa_pliku); //usuwa plik
	void RF(std::string nazwa_pliku, std::string nowa_nazwa); //zmiana nazwy pliku
	void AP(std::string nazwa, std::string dane); //dopisywanie do pliku
	void OF(std::string nazwa, std::string dane); //nadpisywanie pliku
	void RDF(std::string nazwa); //wy�wietlanie zawarto�ci pliku
	void RDFF(std::string nazwa, int pozycja_poczatkowa, int ilosc_znakow); //wy�wietlanie czesci zawarto�ci pliku

	void EXIT(); //zamkni�cie systemu
	void HELP(); //wy�wietlenie dost�pnych komend

};

