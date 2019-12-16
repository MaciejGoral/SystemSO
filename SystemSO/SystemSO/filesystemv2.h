#pragma once
#include <string>
#include <vector>
#include "Semaphore.h"

#define SIZE_OF_BLOCK 32 //w bajtach
#define SIZE_OF_DISK 1024

struct inode
{
	std::string file_name;
	int file_size;
	std::vector<char>* first_data_block;
	std::vector<char>* second_data_block;
	std::vector<int> index_block;

	//Synhronizacja, Jan Witczak
	Semaphore File_Mutex(1);
	int Read_Count = 0;
	//Synchronizacja.
};
class disk_drive
{
public:
	char block[SIZE_OF_BLOCK];
	std::vector<std::vector<char>> disk_space;
	std::vector<inode> inode_table;
	int size_of_disk;
	int number_of_blocks;
	int number_of_free_blocks;
	disk_drive();
	//~disk_drive(); //dorób
	const void read_block_as_int(unsigned int block_number);
	const void read_block(unsigned int block_number);// niuzywane
	void write_block(unsigned int block_number, std::vector<char>block); //nieuzywane
	std::vector<int> search_free_blocks(int number_of_searched_blocks); //funkcja zwraca wektor o zadanej dlugosci zawierajacy indeksy wolnych blokow
	unsigned int search_free_block(); //funkcja zwraca indeks do pierwszego wolnego bloku
	void print_drive(); //do testowania
	bool is_enough_size(std::string data);
	bool is_enough_size(std::string data, int old_file_size);
};
class file_system : public disk_drive
{
public:
	file_system();
	~file_system();
	void create_file(std::string file_name); //dziala
	inode initialize_inode(std::string file_name); //dziala
	void delete_file(std::string file_name);  //dziala
	void rename_file(std::string old_file_name, std::string new_file_name); //dziala
	void add_data_to_file(std::string file_name, std::string data); //dziala
	void overwrite_data_to_file(std::string file_name, std::string data);
	void free_up_block_for_index(int block); //dziala
	void free_up_block_for_pointer(std::vector<char>* pointer);//dziala
	void display_file(std::string file_name); 
	int search_inode(std::string file_name);

	//Synhronizacja, Jan Witczak
	void open_file(std::string file_name_);
	void close_file(std::string file_name_);

	void open_file_reading(std::string file_name_);
	void close_file_reading(std::string file_name_);
	//Synchronizacja.	
};