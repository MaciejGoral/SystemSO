#include "filesystemv2.h"
#include <math.h>
#include <iostream>
disk_drive::disk_drive()
{
	number_of_blocks = SIZE_OF_DISK / SIZE_OF_BLOCK; //obliczamy ilosc blokow
	number_of_free_blocks = number_of_blocks;
	std::vector<char> negative(SIZE_OF_BLOCK,-1);
	/*
	std::vector<char> negative;
	for (int i = 0; i < SIZE_OF_BLOCK;i++)
	{
		negative.push_back(-1);
	}*/
	
	for (int i = 0; i < number_of_blocks; i++)
	{
		disk_space.push_back(negative); //wypelniamy vector vectorem charow o wartosci -1
	}

}

/*disk_drive::~disk_drive()
{
	for (int i = 0; i < number_of_blocks; i++)
	{
		for (int j = 0; j < SIZE_OF_BLOCK; j++)
		{
			disk_space[i].erase(disk_space[i].begin()+disk_space[i].size()); //nie bangla :'(
		}
	}
} */
bool disk_drive::is_enough_size(std::string data)
{
	int needed_blocks = ceil((float)(data.length() / (float)SIZE_OF_BLOCK)); //liczba potrzebnych blokow aby zapisac plik
	if (number_of_free_blocks < needed_blocks)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool disk_drive::is_enough_size(std::string data,int old_file_size)
{
	int needed_blocks = ceil((float)(data.length() / (float)SIZE_OF_BLOCK))- ceil((float)(old_file_size / (float)SIZE_OF_BLOCK)); //liczba potrzebnych blokow aby zapisac plik - liczba blokow ktora zyskalismy usuwajac stary plik
	if (number_of_free_blocks < needed_blocks)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void disk_drive::write_block(unsigned int block_number, std::vector<char>block) //zapisujemy podany blok danymi;usigned ¿eby nie by³o bloku o numerze ujemnym, bo takiego nie ma;, dane musza zostaæ zamienione na tablice charów
{
		disk_space[block_number] = block; //niezapisane wartoœci w sektorze przepdaja
		number_of_free_blocks--;
} 
const void disk_drive::read_block_as_int(unsigned int block_number)
{
	for (int i = 0; i < SIZE_OF_BLOCK;i++) //bo pierwzy blok od 0 do 31 itd
	{
		std::cout <<(int) disk_space[block_number][i];
	}
	std::cout << std::endl;
} 
const void disk_drive::read_block(unsigned int block_number)
{
	for (int i = 0; i < SIZE_OF_BLOCK; i++) //bo pierwzy blok od 0 do 31 itd
	{
		std::cout << disk_space[block_number][i];
	}
	std::cout << std::endl;
}
unsigned int disk_drive::search_free_block()
{
	int help;
	for (int i = 0; i < number_of_blocks; i++) //wywali³em <=
	{
		help = 0;
		for (int j = 0; j<SIZE_OF_BLOCK; j++) //bo pierwszy blok od 0 do 31 itd
		{
			if (disk_space[i][j] != -1)
			{
				help = -1; //w przypadku gdy znajdziemy w jakimœ bloku dane inne ni¿ -1 zmieniamy zmienna pomocnicza na -1
				break;
			}

		}
		if (help == 0) //jezeli blok jest zapisany w -1, czyli pusty, zwracamy jego numer
		{
			return i;
		}
	}
	//return -1 //do zwracania bledu
}
std::vector<int> disk_drive::search_free_blocks(int number_of_searched_blocks) //mozna poprawic wydajnosc
{
	std::vector<int> returning_vector;
	int help;
	int found_blocks_counter = 0;
	for (int i= 0; i < number_of_blocks; i++)
	{
		if (found_blocks_counter == number_of_searched_blocks)
		{
			break;
		}
		help = 0;
		for (int j = 0; j < SIZE_OF_BLOCK; j++) //bo pierwszy blok od 0 do 31 itd
		{				
			if (disk_space[i][j] != -1)
			{				
				help = -1; //w przypadku gdy znajdziemy w jakimœ bloku dane inne ni¿ -1 zmieniamy zmienna pomocnicza na -1
				break;
			}
		}
		if (help == 0) //jezeli blok jest zapisany w -1, czyli pusty, zwracamy jego numer
		{				
		
			returning_vector.push_back(i);
			found_blocks_counter++;
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
			std::cout <<(int) disk_space[i][j];
		}
		
	}
	std::cout << std::endl;
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
	inode initialized;
	initialized.file_name = file_name; 
	initialized.file_size = -1; //-1 oznacza i¿ plik nie zajmuje ¿adnych bajtow
	initialized.first_data_block = nullptr;
	initialized.second_data_block =nullptr;
	return initialized;
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
	return -1; //gdy nie znajdziemy inode o podanej nazwie-plik nie istniej, zwracamy -1
}
void file_system::create_file(std::string file_name)
{
	inode helping_inode = initialize_inode(file_name);
	disk_drive::inode_table.push_back(helping_inode);
	std::cout << "File "<<file_name<<" created" << std::endl;
}
void file_system::rename_file(std::string old_file_name, std::string new_file_name)
{
	int inode_index = search_inode(old_file_name);
	if (inode_index != -1)
	{
		inode_table[inode_index].file_name = new_file_name;
		std::cout << "File " << old_file_name << " renamed to " << new_file_name << std::endl;
	}
	else
	{
		std::cout << "File " << old_file_name << " doesn't exists"<< std::endl;
	}

}
void file_system::add_data_to_file(std::string file_name, std::string data) //zabezpiecz ¿eby po 1 wpisie nie da³o siê uruchomic
{
	int inode_index = search_inode(file_name);
	if (inode_index != -1)
	{
		if (is_enough_size(data))
		{
			if (data.length() <= SIZE_OF_BLOCK)
			{
				int inode_index = search_inode(file_name);
				int free_block = search_free_block();
				for (int i = 0; i < data.length(); i++)
				{
					disk_space[free_block][i] = data.at(i);
				}
				number_of_free_blocks--;
				inode_table[inode_index].first_data_block = &disk_space[free_block]; //przypisujemy do wskaznika na 1 blok adres bloku do ktorego wpisalismy dane
				inode_table[inode_index].file_size = data.length();
			}
			else if (data.length() <= 2 * SIZE_OF_BLOCK)
			{
				int inode_index = search_inode(file_name);
				std::vector<int> free_blocks = search_free_blocks(2);
				int bytes_counter = 0; //zliczamy bajty	ktore zapisalismy, aby po podzieleniu przez rozmiar bloku wiedziec ktory blok z vectora wolnych blokow mamy zapisac, dodadkowo sluzy do obslug data.at
				for (int i = 0; i < free_blocks.size(); i++) //j jako licznik bitow zapisanych w aktualnie zapisanym bloku, gdy wybije 32, czyli gdybyœmy przechodzili do bloku, zeruje sie 
				{
					for (int j = 0; j < SIZE_OF_BLOCK and bytes_counter < data.size(); j++, bytes_counter++)
					{
						disk_space[free_blocks[i]][j] = data.at(bytes_counter);
					}
					number_of_free_blocks--;
				}
				inode_table[inode_index].first_data_block = &disk_space[free_blocks[0]]; //przypisujemy do wskaznika na 1 blok adres bloku do ktorego wpisalismy dane
				inode_table[inode_index].second_data_block = &disk_space[free_blocks[1]]; //przypisujemy do wskaznika na 2 blok adres 2 bloku do ktorego wpisalismy dane
				inode_table[inode_index].file_size = data.length();
			}
			else if (data.length() > 2 * SIZE_OF_BLOCK)
			{
				int inode_index = search_inode(file_name);
				std::vector<int> free_blocks = search_free_blocks(ceil((float)(data.length() / (float)SIZE_OF_BLOCK)));
				int bytes_counter = 0; //zliczamy bajty	ktore zapisalismy, aby po podzieleniu przez rozmiar bloku wiedziec ktory blok z vectora wolnych blokow mamy zapisac, dodadkowo sluzy do obslug data.at
				for (int i = 0; i < free_blocks.size(); i++) //j jako licznik bitow zapisanych w aktualnie zapisanym bloku, gdy wybije 32, czyli gdybyœmy przechodzili do bloku, zeruje sie 
				{
					for (int j = 0; j < SIZE_OF_BLOCK and bytes_counter < data.size(); j++, bytes_counter++)
					{
						disk_space[free_blocks[i]][j] = data.at(bytes_counter);
					}
					number_of_free_blocks--;

				}
				inode_table[inode_index].first_data_block = &disk_space[free_blocks[0]]; //przypisujemy do wskaznika na 1 blok adres bloku do ktorego wpisalismy dane
				inode_table[inode_index].second_data_block = &disk_space[free_blocks[1]]; //przypisujemy do wskaznika na 2 blok adres 2 bloku do ktorego wpisalismy dane
				for (int i = 2; i < free_blocks.size(); i++)
				{
					inode_table[inode_index].index_block.push_back(free_blocks[i]); //zapisujemy indeksy blokow nie mieszczacych sie w 2 pierwszych blokach do tablicy
				}
				inode_table[inode_index].file_size = data.length();
			}
		}
		else
		{
			std::cout << "Not enough free space on disk. Delete other files" << std::endl;
		}
	}
	else
	{
		std::cout << "File " <<file_name << " doesn't exists " <<std::endl;
	}
}

void file_system::free_up_block_for_index(int block)
{
	for (int j = 0; j < SIZE_OF_BLOCK; j++)
	{
		disk_space[block][j] = -1;
	}
} 
void file_system::free_up_block_for_pointer(std::vector<char>* pointer)
{
	for (int j = 0; j < SIZE_OF_BLOCK; j++)
	{
		(*pointer)[j] = -1;
	}
}
void file_system::delete_file(std::string file_name)
{
	int inode_index = search_inode(file_name);
	if (inode_index != -1)
	{

		//czyscimy bloki na dysku
		if (inode_table[inode_index].first_data_block != nullptr)
		{
			free_up_block_for_pointer(inode_table[inode_index].first_data_block); //czyscimy 1 blok "szybkiego dostepu"
			number_of_free_blocks++;
		}
		if (inode_table[inode_index].second_data_block != nullptr)
		{
			free_up_block_for_pointer(inode_table[inode_index].second_data_block); //czyscimy 2 blok "szybkiego dostepu"
			number_of_free_blocks++;
		}
		if (!inode_table[inode_index].index_block.empty())
		{
			for (int i = 0, j = 0; i < inode_table[inode_index].index_block.size(); i++)
			{
				free_up_block_for_index(inode_table[inode_index].index_block[i]); //czyscimy bloki indeksowe
				number_of_free_blocks++;
			}
		}
		inode_table.erase(inode_table.begin() + inode_index);//usuwamy iwezel
	}
	else
	{
		std::cout << "File " << file_name << " doesn't exists " << std::endl;
	}
	

} 
void file_system::overwrite_data_to_file(std::string file_name, std::string data)
{
	//wpierw usuwamy dane z dysku
	int inode_index = search_inode(file_name);
	if (inode_index != -1)
	{
		if (is_enough_size(data,inode_table[inode_index].file_size))
		{
			if (inode_table[inode_index].first_data_block != nullptr)
			{
				free_up_block_for_pointer(inode_table[inode_index].first_data_block); //czyscimy 1 blok "szybkiego dostepu"
				number_of_free_blocks++;
			}
			if (inode_table[inode_index].second_data_block != nullptr)
			{
				free_up_block_for_pointer(inode_table[inode_index].second_data_block); //czyscimy 2 blok "szybkiego dostepu"
				number_of_free_blocks++;
			}
			if (!inode_table[inode_index].index_block.empty())
			{
				for (int i = 0, j = 0; i < inode_table[inode_index].index_block.size(); i++)
				{
					free_up_block_for_index(inode_table[inode_index].index_block[i]); //czyscimy bloki indeksowe
					number_of_free_blocks++;
				}
			}
			inode_table[inode_index].file_size = -1;
			inode_table[inode_index].first_data_block = nullptr;
			inode_table[inode_index].second_data_block = nullptr;
			inode_table[inode_index].index_block.clear();
			add_data_to_file(file_name, data);
		}
		else
		{
			std::cout << "Not enough free space on disk. Delete other files" << std::endl;
		}
	}
	else
	{
		std::cout << "File " << file_name << " doesn't exists " << std::endl;
	}

} 
void file_system::display_file(std::string file_name)
{
	int inode_index = search_inode(file_name);
	if (inode_table[inode_index].first_data_block !=nullptr)
	{
		for (int i = 0; i < SIZE_OF_BLOCK; i++)
		{
			if ((*inode_table[inode_index].first_data_block)[i] == -1) //gdy dojdziemy do niezapisanego elementu bloku przerywamy
			{
				break;
			}
			std::cout << static_cast<char>((*inode_table[inode_index].first_data_block)[i]);
		}
	}
	if (inode_table[inode_index].second_data_block != nullptr)
	{
		for (int i = 0; i < SIZE_OF_BLOCK; i++)
		{
			if ((*inode_table[inode_index].first_data_block)[i] == -1)
			{
				break;
			}
			std::cout << static_cast<char>((*inode_table[inode_index].second_data_block)[i]);
		}
	}
	if (!inode_table[inode_index].index_block.empty())
	{
		std::cout <<std::endl;
		for (int i = 0; i < inode_table[inode_index].index_block.size(); i++)
		{
			for (int j = 0; j < SIZE_OF_BLOCK; j++)
			{
				if (disk_space[inode_table[inode_index].index_block[i]][j] == -1)
				{
					break;
				}
				std::cout << static_cast<char>(disk_space[inode_table[inode_index].index_block[i]][j]);
			}
		}
	}
} 

int main()
{
	file_system a;
	std::cout << "WOLNE BLOKI " << a.number_of_free_blocks << std::endl;
	a.create_file("BB");
	a.add_data_to_file("BB", "123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY123456789012345678901234567890ZY");
	std::cout << "WOLNE BLOKI " << a.number_of_free_blocks << std::endl;
	a.print_drive();
	a.display_file("BB");
	std::cout << "!@#$%^&*(" << std::endl;
	a.overwrite_data_to_file("BB", "ZUPANUPAALEDUPA");
	std::cout << "WOLNE BLOKI " << a.number_of_free_blocks << std::endl;
	a.display_file("BB");
	//a.add_data_to_file("XD", aa);
	//a.print_drive();
	//a.delete_file("XD");
	//a.print_drive();
	std::vector<char>* xd;
	//xd = a.inode_table[0].first_data_block;
	//std::cout << (*xd)[0] << (*xd)[1] << (*xd)[2] << (*xd)[3]; tak sie wydobwa dane z tego
	/*file_system a;

	std::string aa = "Andrzej duda, to sie uda2115123XAndrzej duda, to sie uda21151234NOWYBLOCKAndrzej duda, to sie uda2115123XAndrzej duda, ZIOM77XD";
	std::string bb = "Andrzej duda, to sie uda2115123XAndrzej duda, to sie uda9999qwerZXC";
	std::string cc = "Andrzej duda, to sie uda2115123XAndrzej duda, to sie uda";
	//std::cout << bb.size();
	a.create_file("2");
	a.add_data_to_file("2", bb);
	a.create_file("Ugabuga");
	
	
	
	a.add_data_to_file("Ugabuga", "123");
//	a.display_file("Ugabuga");
	//std::cout << aa.size() << std::endl;
	//a.add_data_to_file("Ugabuga", aa);
	
	//a.display_file("2");
	a.delete_file("Ugabuga");
	//std::cout << "po usunieciu" << std::endl;
	//a.print_drive(); 
	a.create_file("Ugabuga34");
	a.add_data_to_file("Ugabuga34", aa);
	//std::cout << "po 34" << std::endl;
	//a.print_drive();
	a.display_file("Ugabuga34");
//	a.delete_file("2");
	//std::cout << "po usunieciu" << std::endl;
	a.print_drive();
	a.overwrite_data_to_file("Ugabuga34", "123qwerty");
	std::cout << "po overwrite" << std::endl;
	a.print_drive();

	//std::cout << std::endl << "Wypisujemy" << std::endl;
	//std::cout << a.inode_table[0].index_block[0] << std::endl;
	//a.display_file("Ugabuga");
	//a.display_file("2");
	//a.create_file("123"); */
}