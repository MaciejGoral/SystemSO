#pragma once
#include <string>
#include <vector>
#include "Semaphore.h"
#define SIZE_OF_BLOCK 32 //w bajtach
#define SIZE_OF_DISK 1024

struct inode
{
	std::string file_name;
	std::vector<char>* first_data_block; //blok wskaznikowy, daje szybki dostep do pliku
	std::vector<char>* second_data_block;//blok wskaznikowy, daje szybki dostep do pliku
	std::vector<int> index_block; //dalsze bloki, wektor przechowuje nr indeksow blokow w ktorych zapisane sa dane
	int file_size;
	int occupied_blocks_size; //liczba blokow w ktorych znajduja sie dane pliku
	int first_data_block_index;  //indeks bloku wskaznikowego
	int second_data_block_index;  //indeks bloku wskaznikowego

	//Synhronizacja, Jan Witczak
	Semaphore File_Mutex;
	int Read_Count;
	bool writing;
	//Synchronizacja.
};
class disk_drive
{
	friend class file_system;
public:
	const void print_drive(); //wypisuje zawartosc dysku z podzia³em na bloki
	const void print_inode_catalogue(); //wyswietla zawartosc katalogu i wezlow
	const void display_occupied_blocks(std::string file_name);
	const void display_all_information_about_all_files();
	const int search_inode(std::string file_name); //zwraca indeks inode z  odpowiadajaca nazwa
	const unsigned int search_free_block(); //funkcja zwraca indeks do pierwszego wolnego bloku
	const std::vector<int> search_free_blocks(int number_of_searched_blocks); //funkcja zwraca wektor o zadanej dlugosci zawierajacy indeksy wolnych blokow
	const bool is_enough_size(std::string data);
	const bool is_enough_size(std::string data, int old_file_size); //uzywane do przeliczenia miejsca w przypadku nadpisywania pliku
protected:
	disk_drive();
	int number_of_blocks;
	int number_of_free_blocks;
	std::vector<std::vector<char>> disk_space;
	std::vector<inode> inode_table;
	std::vector<int> free_drive_blocks;
	inode initialize_inode(std::string file_name);
};
class file_system : public disk_drive
{
public:
	file_system();
	void create_file(std::string file_name);
	void delete_file(std::string file_name);
	void rename_file(std::string old_file_name, std::string new_file_name); 
	void add_in_data_to_file(std::string file_name, std::string data); //dopisuje dane do pliku
	void overwrite_data_to_file(std::string file_name, std::string data); //nadpisuje dane w pliku - czysci plik i zapisuje od nowa
	void free_up_block_for_index(int block);//czysci blok, przeznaczony do zastosowania z blokami indeksowymi
	void free_up_block_for_pointer(std::vector<char>* pointer, int pointer_block_index);//czysci blok, przeznaczony do zastosowania z blokami wskaznikowymi
	const void display_file(std::string file_name); 

	//Synhronizacja, Jan Witczak
	void open_file(std::string file_name_);
	void close_file(std::string file_name_);

	void open_file_reading(std::string file_name_);
	void close_file_reading(std::string file_name_);
	//Synchronizacja.
};