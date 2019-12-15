#pragma once
#include <string>
#include <vector>
#define SIZE_OF_BLOCK 32 //w bajtach
#define SIZE_OF_DISK 1024

struct inode
{
	std::string file_name;
	int file_size;//size_t file_size;
	int first_data_block;
	int second_data_block;
	std::vector<int> index_block;
};
class disk_drive
{
public:
	std::vector<inode> inode_table;
	int size_of_disk;
	int number_of_blocks;
	disk_drive();
	~disk_drive();
	void read_block(unsigned int block_number, char result_block[]); //sprawdz czy tak dziala; niuzywane
	void write_block(unsigned int block_number, char block[]); //nieuzywane
	std::vector<int> search_free_blocks(int number_of_searched_blocks);
	unsigned int search_free_block();
	void print_drive(); //do testowania
	
//protected:
	char* disk_space;
};
class file_system : public disk_drive
{
public:
	file_system();
	~file_system();
	void create_file(std::string file_name); 
	inode initialize_inode(std::string file_name); //dziala
	void delete_file(std::string file_name);  //dziala
	void rename_file(std::string old_file_name, std::string new_file_name); //dziala
	void add_data_to_file(std::string file_name, std::string data); 
	void overwrite_data_to_file(std::string file_name, std::string data);
	void free_up_block(int block); //dziala
	void display_file(std::string file_name);
	int search_inode(std::string file_name);
};