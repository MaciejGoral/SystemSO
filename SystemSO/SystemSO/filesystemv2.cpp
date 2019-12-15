#include "filesystemv2.h"
#include <math.h>
#include <iostream>
//OG”LNIE TROCH  SI  ZAJEBA£EM I PIERWSZE 2 SEKTORY ZAMIAST WSKAèNIK”W NA BLOK S• INDEKSAMI BLOKU I W SUMIE MUSZE TO POPRAWIC I W OGOLE DODAC BLOK JAKO TAKI, ALE CHYBA WIADOMO DO CZEGO SIE ODWOLYWAC
disk_drive::disk_drive()
{
	disk_space = new char[SIZE_OF_DISK];
	number_of_blocks = SIZE_OF_DISK / SIZE_OF_BLOCK;
	for (int i = 0; i < SIZE_OF_DISK; i++)
	{
		disk_space[i] = -1; //-1 oznacza iø przestrzeÒ jest do zapisu;
	}
}
disk_drive::~disk_drive()
{
	delete[] disk_space;
}
void disk_drive::write_block(unsigned int block_number, char block[]) //zapisujemy podany blok danymi;usigned øeby nie by≥o bloku o numerze ujemnym, bo takiego nie ma;, dane musza zostaÊ zamienione na tablice charÛw
{
	for (int i = number_of_blocks*SIZE_OF_BLOCK,j=0;i< static_cast<int>( block_number*SIZE_OF_BLOCK+SIZE_OF_BLOCK-1);i++,j++) //mechanizm sprawdzania czy wystarczy miejsca zainmplemenotwany gdzie indziej
	{
		disk_space[i] = block[j]; //niezapisane wartoúci w sektorze przepdaja
	}
}
void disk_drive::read_block(unsigned int block_number, char result_block[]) 
{
	for (int i = number_of_blocks * SIZE_OF_BLOCK, j = 0; i <static_cast<int>( block_number * SIZE_OF_BLOCK + SIZE_OF_BLOCK-1); i++, j++) //bo pierwzy blok od 0 do 31 itd
	{
		result_block[j]= disk_space[i]; //jako, øe nie moøemy zwrÛciÊ tablicy, funkcja przypisuje zawartoúÊ bloku z dysku do przekazanej zmiennej, ktÛra naleøy utworzyÊ
	}
}
unsigned int disk_drive::search_free_block()
{
	int help = 0;
	for (int i = 0; i <= number_of_blocks; i++)
	{
		for (int j =i; j < i * SIZE_OF_BLOCK+SIZE_OF_BLOCK-1; j++) //bo pierwszy blok od 0 do 31 itd
		{
			if (disk_space[j] != -1)
			{
				help = -1; //w przypadku gdy znajdziemy w jakimú bloku dane inne niø -1 zmieniamy zmienna pomocnicza na -1
			}

		}
		if (help == 0) //jezeli blok jest zapisany w -1, czyli pusty, zwracamy jego numer
		{
			return i;
		}
	}
}
std::vector< int> disk_drive::search_free_blocks(int number_of_searched_blocks) //mozna poprawic wydajnosc
{
	std::vector<int> returning_vector;
	for (int i = 0; i < number_of_searched_blocks; i++)
	{
		int help = 0;
		for (int j= 0; j <= number_of_blocks; j++)
		{
			for (int k = j; k < j * SIZE_OF_BLOCK + SIZE_OF_BLOCK - 1; k++) //bo pierwszy blok od 0 do 31 itd
			{
				
				if (disk_space[k] != -1)
				{
					help = -1; //w przypadku gdy znajdziemy w jakimú bloku dane inne niø -1 zmieniamy zmienna pomocnicza na -1
				}

			}
			if (help == 0) //jezeli blok jest zapisany w -1, czyli pusty, zwracamy jego numer
			{
				returning_vector.push_back(j);
			}
		}
	}
	return returning_vector;
}
void disk_drive::print_drive()
{
	for (int i = 0; i < number_of_blocks; i++)
	{
		std::cout << std::endl << "NEW BLOCK" << std::endl;
		for (int j = 0; j < SIZE_OF_BLOCK; j++)
		{
			std::cout <<(int) disk_space[i * SIZE_OF_BLOCK + j];
		}
		
	}
}
file_system::file_system()
{
	disk_drive::disk_drive();
}
file_system::~file_system()
{
	//disk_drive::~disk_drive(); //ogarnij na potem
}
inode file_system::initialize_inode(std::string file_name) //tworzymy iwezel o danej nazwie, reszta pol jest pusta, zawiera -1
{
	int negative_one = -1;
	inode initialized;
	initialized.file_name = file_name; 
	initialized.file_size = -1;
	initialized.first_data_block = -1;
	initialized.second_data_block = -1;
	return initialized;
}
void file_system::create_file(std::string file_name)
{
	inode helping_inode = initialize_inode(file_name);
	disk_drive::inode_table.push_back(helping_inode);
}
void file_system::add_data_to_file(std::string file_name, std::string data)
{
	if (data.length() <= SIZE_OF_BLOCK)
	{
		
		int free_block = search_free_block();
		for (int i = 0; i < data.length(); i++)
		{
			disk_space[free_block * SIZE_OF_BLOCK + i] = data.at(i);
		}
		int inode_index = search_inode(file_name);
		inode_table[inode_index].first_data_block = free_block;
		inode_table[inode_index].file_size = data.length();
			
		
		
	}
	else if (data.length() <= 2*SIZE_OF_BLOCK)
	{
		int inode_index = search_inode(file_name);
		std::vector<int> free_blocks= search_free_blocks(2);
		int bytes_counter = 0; //zliczamy bajty	ktore zapisalismy, aby po podzieleniu przez rozmiar bloku wiedziec ktory blok z vectora wolnych blokow mamy zapisac, dodadkowo sluzy do obslug data.at
		for (int i = 0,j=0; i < data.length(); i++,j++) //j jako licznik bitow zapisanych w aktualnie zapisanym bloku, gdy wybije 32, czyli gdybyúmy przechodzili do bloku, zeruje sie 
		{
			if (j == SIZE_OF_BLOCK)
			{
				j = 0;
			}
			disk_space[free_blocks[i / SIZE_OF_BLOCK] * SIZE_OF_BLOCK + j] = data.at(i);
		}
		inode_table[inode_index].first_data_block = free_blocks[0];
		inode_table[inode_index].second_data_block = free_blocks[1];
		inode_table[inode_index].file_size = data.length();
	}
	else if (data.length() >2*SIZE_OF_BLOCK)
	{
		int inode_index = search_inode(file_name);
		std::vector<int> free_blocks = search_free_blocks(ceil(data.length()/SIZE_OF_BLOCK)); //obliczamy ile blokÛw potrzebujemy
		int bytes_counter = 0; //zliczamy bajty	ktore zapisalismy, aby po podzieleniu przez rozmiar bloku wiedziec ktory blok z vectora wolnych blokow mamy zapisac, dodadkowo sluzy do obslug data.at
		for (int i = 0, j = 0; i < data.length(); i++, j++) //j jako licznik bitow zapisanych w aktualnie zapisanym bloku, gdy wybije 32, czyli gdybyúmy przechodzili do bloku, zeruje sie 
		{
			if (j == SIZE_OF_BLOCK)
			{
				j = 0;
			}
			disk_space[free_blocks[i / SIZE_OF_BLOCK] * SIZE_OF_BLOCK + j] = data.at(i);
		}
		inode_table[inode_index].first_data_block = free_blocks[0];
		inode_table[inode_index].second_data_block = free_blocks[1];
		for (int i=2;i<free_blocks.size(); i++)
		{
			inode_table[inode_index].index_block.push_back(free_blocks[i]);
		}
		inode_table[inode_index].file_size = data.length();

	}
}
void file_system::rename_file(std::string old_file_name, std::string new_file_name)
{
	int inode_index = search_inode(old_file_name);
	inode_table[inode_index].file_name = new_file_name;
	std::cout << "File renamed" << std::endl;
	
}
void file_system::free_up_block(int block)
{
	for (int j = 0; j < SIZE_OF_BLOCK; j++)
	{
		disk_space[block * SIZE_OF_BLOCK + j] = -1;
	}
}
void file_system::delete_file(std::string file_name)
{
	int inode_index = search_inode(file_name);
	//czyscimy bloki na dysku
	if (inode_table[inode_index].first_data_block !=-1)
	{
		free_up_block(inode_table[inode_index].first_data_block);
	}
	if (inode_table[inode_index].second_data_block != -1)
	{
		free_up_block(inode_table[inode_index].second_data_block);
	}
	if (!inode_table[inode_index].index_block.empty())
	{
		for (int i = 0, j = 0; i < inode_table[inode_index].index_block.size(); i++)
		{
			free_up_block(inode_table[inode_index].index_block[i]);
		}
	}
	inode_table.erase(inode_table.begin() + inode_index);//usuwamy iwezel
		
	

}
void file_system::overwrite_data_to_file(std::string file_name, std::string data)
{
	//wpierw usuwamy dane z dysku
	int inode_index = search_inode(file_name);
	if (inode_table[inode_index].first_data_block != -1)
	{
		free_up_block(inode_table[inode_index].first_data_block);
	}
	if (inode_table[inode_index].second_data_block != -1)
	{
		free_up_block(inode_table[inode_index].second_data_block);
	}
	if (!inode_table[inode_index].index_block.empty())
	{
		for (int i = 0, j = 0; i < inode_table[inode_index].index_block.size(); i++)
		{
			free_up_block(inode_table[inode_index].index_block[i]);
		}
	}
	inode_table[inode_index].file_size = -1;
	inode_table[inode_index].first_data_block = -1;
	inode_table[inode_index].second_data_block = -1;
	inode_table[inode_index].index_block.clear();
	add_data_to_file(file_name, data);

}
void file_system::display_file(std::string file_name)
{
	int inode_index = search_inode(file_name);
	if (inode_table[inode_index].first_data_block != -1)
	{
		for (int i = 0; i < SIZE_OF_BLOCK; i++)
		{
			if (disk_space[inode_table[inode_index].first_data_block * SIZE_OF_BLOCK + i] == -1) //gdy dojdziemy do niezapisanego elementu bloku przerywamy
			{
				break;
			}
			std::cout << static_cast<char>(disk_space[inode_table[inode_index].first_data_block * SIZE_OF_BLOCK + i]);
		}
	}
	if (inode_table[inode_index].second_data_block != -1)
	{
		for (int i = 0; i < SIZE_OF_BLOCK; i++)
		{
			if (disk_space[inode_table[inode_index].second_data_block * SIZE_OF_BLOCK + i] == -1)
			{
				break;
			}
			std::cout << static_cast<char>(disk_space[inode_table[inode_index].second_data_block * SIZE_OF_BLOCK + i]);
		}
	}
	if (!inode_table[inode_index].index_block.empty())
	{
		for (int i = 0,j=0; i < inode_table[inode_index].index_block.size(); i++)
		{
			if (j ==SIZE_OF_BLOCK)
			{
				j = 0;
			}
			if (disk_space[inode_table[inode_index].second_data_block * SIZE_OF_BLOCK*i + j] == -1)
			{
				break;
			}
			std::cout << static_cast<char>(disk_space[inode_table[inode_index].second_data_block * SIZE_OF_BLOCK*i + j]);
		}
		
	}
}
int file_system::search_inode(std::string file_name)
{
	for (int i = 0; i < inode_table.size(); i++)
	{
		if (inode_table[i].file_name == file_name)
		{
			return i;
		}
	}
}
int main()
{
	//disk_drive b;
	file_system a;
	//std::cout << (int)a.number_of_blocks;
	a.create_file("Ugabuga");
	//a.rename_file("Ugabuga", "Dupa");
	//std::cout << a.inode_table[0].file_name;
	//std::cout<<a.inode_table[0].file_name<<std::endl;
	//std::cout << a.inode_table[0].file_size << std::endl;
	//std::cout << a.inode_table[0].first_data_block<< std::endl;
	//std::string aa = "Andrzej duda sie uda";
	//std::cout << aa.length() << "jhsjhsd";
	std::string aa = "Andrzej duda, to sie uda2115123XAndrzej duda, to sie uda2115123XAndrzej duda, to sie uda2115123XSDSDSDSSDSDSD";
	std::cout << "size" << aa.length();
	a.add_data_to_file("Ugabuga", aa);
	a.print_drive();
	std::cout<<std::endl<<"Wypisujemy" << std::endl;
	a.display_file("Ugabuga");
	a.overwrite_data_to_file("Ugabuga", "XDDD");
	a.print_drive();
	a.display_file("Ugabuga");
	/*std::cout << a.inode_table[0].file_name << a.inode_table[0].file_size << std::endl << a.inode_table[0].first_data_block<<"X**XDD"<< std::endl << a.inode_table[0].second_data_block<<a.inode_table[0].index_block[0]<< a.inode_table[0].index_block[1] << std::endl;
	for (int i = 0; i < 32; i++)
	{
		std::cout << (int)a.disk_space[i] <<" "<< (char)a.disk_space[i] << std::endl;
	}
	//a.add_data_to_file()
	
	//b.print_drive();
//	b.disk_space[2] = (char)-1;
	//std::cout<<"SDSDSSD"<<(int)b.disk_space[2];
	//b.disk_space[3] = 'XY';
	/*if (b.disk_space[3] == -1)
	{
		std::cout << "kskldjmsksldklsd";
	}*/
	//std::cout << "ssss"<<b.disk_space[3];
}