#pragma once

#include <list>
#include <queue>
#include <array>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "Process.hpp"
#include "..\Interpreter\Interpreter.hpp"


#define PriorityVector std::vector<std::shared_ptr<PCB>>
#define ProcessTable std::array<PriorityVector,140>
/*
struct PCB
{
	int static_process_priority;
	int process_nice;
	int dynamic_priority;
	int average_sleep_time;
};
*/
class O1Scheduler {
private:
	


	
public:
	O1Scheduler();
	~O1Scheduler();

	int DEFAULT_PRIORITY = 120;
//	std::shared_ptr<PCB>pcb;

	std::array<bool, 140>bitmapa;
	std::array<PriorityVector, 140>active_array;
	std::array<PriorityVector, 140>expired_array;
	std::shared_ptr<ProcessTable> active_array_pointer, expired_array_pointer;			//wskaŸniki na tablice zadañ aktywnych i przeterminowanych
	

	
	std::shared_ptr<PCB> O1SchedulingAlgorithm();				//zwraca proces który ma byæ wykonywany 
	
	void change_era_function();					//zamiana tablic w momencie, w którym tablica zadañ aktywnych jest pusta
		
	void add_new_process_to_expired(std::shared_ptr<PCB>&giving_process);

	void creating_bitmap(std::shared_ptr<ProcessTable>table);

	int number_of_first_biggest_priority_in_bitmap();

	void time_slice_calculation(std::shared_ptr<PCB>& giving_process);

	void move_process_to_expired_table(int new_dynamic_priority, std::shared_ptr<PCB>& pcb);				//przeniesienie procesu up³yniêciu przeznaczonego mu kwantu czasu

	void calculating_dynamic_priority(std::shared_ptr<PCB>& pcb);						//obliczenie nowego priorytetu

	int calculating_bonus(std::shared_ptr<PCB>&giving_process);				//obliczenie bonusu

	void displayActiveArray();
	void displayExpiredArray();

	void displayBitmap();
};



