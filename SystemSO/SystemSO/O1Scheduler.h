#pragma once

#include <list>
#include <queue>
#include <array>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>


#define PriorityVector std::vector<std::shared_ptr<PCB>>
#define ProcessTable std::array<PriorityVector,140>

struct PCB
{
	int static_process_priority;
	int process_nice;
	int dynamic_priority;
	int average_sleep_time;
};

class O1Scheduler {
private:
	


	
public:
	O1Scheduler();
	~O1Scheduler();

	int instructions_in_one_era;
	int DEFAULT_PRIORITY = 120;
	PCB* pcb;

	std::array<bool, 140>bitmapa;
	std::array<PriorityVector, 140>active_array;
	std::array<PriorityVector, 140>expired_array;
	std::shared_ptr<ProcessTable> active_array_pointer, expired_array_pointer;			//wskaŸniki na tablice zadañ aktywnych i przeterminowanych
	

	
	void O1SchedulingAlgorithm();				//zwraca proces który ma byæ wykonywany 
	
	void change_era_function();					//zamiana tablic w momencie, w którym tablica zadañ aktywnych jest pusta
		
	void add_new_process_to_expired(std::shared_ptr<PCB>giving_process);

	void creating_bitmap(std::shared_ptr<ProcessTable>table);

	int number_of_first_biggest_priority_in_bitmap();

	int time_slice_calculation(int some_priority);

	void move_process_to_expired_table(int new_dynamic_priority, std::shared_ptr<PCB>& pcb);				//przeniesienie procesu up³yniêciu przeznaczonego mu kwantu czasu

	int calculating_dynamic_priority(int bonus, std::shared_ptr<PCB>& pcb);						//obliczenie nowego priorytetu

	int calculating_bonus(int average_sleep_time);				//obliczenie bonusu

	void RunProcess();
	void RunProcess(int);
};



