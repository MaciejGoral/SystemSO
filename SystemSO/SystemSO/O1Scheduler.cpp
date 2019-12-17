#include "O1Scheduler.h"



O1Scheduler::O1Scheduler() {
	active_array_pointer = std::make_shared<ProcessTable>(active_array);
	expired_array_pointer = std::make_shared<ProcessTable>(expired_array);
}

O1Scheduler::~O1Scheduler(){}

void O1Scheduler::O1SchedulingAlgorithm() {

	change_era_function();						//sprawdzenie czy trzeba zmieniæ epokê, jeœli tak to tworzy siê bitmapa dla nowej tablicy aktywnej
	int first_set_bit = number_of_first_biggest_priority_in_bitmap();				//odnalezienie w bitmapie najwy¿szego priorytetu który ma procesy
	int time_slice = time_slice_calculation(first_set_bit);							//liczymy kwant czasu który przys³uguje procesowi
//	active_array_pointer->at(first_set_bit)[0];

}



int O1Scheduler::number_of_first_biggest_priority_in_bitmap() {
	for (int i = 0; i<140; i++) {
		if (O1Scheduler::bitmapa[i] == 1) return i;
	}
	return -1;
}

void O1Scheduler::change_era_function() {
	/*
	if (std::all_of(bitmapa.begin(), bitmapa.end(), [](int i) { return i == 0; })) {
		std::swap(active_array_pointer, expired_array_pointer);
	}
	*/
	if (number_of_first_biggest_priority_in_bitmap() == -1) {
		std::swap(active_array_pointer, expired_array_pointer);
		creating_bitmap(active_array_pointer);
		instructions_in_one_era = 0;
	}
}

void O1Scheduler::add_new_process_to_expired(std::shared_ptr<PCB>giving_process) {
	expired_array[DEFAULT_PRIORITY].push_back(giving_process);
}


void O1Scheduler::creating_bitmap(std::shared_ptr<ProcessTable>table) {
	int pomocnicza = 0;
	for (auto i=table->begin();i<table->end() ; i++) {
		if (i->empty()) {
			O1Scheduler::bitmapa[pomocnicza] = 0;
		}
		else {
			O1Scheduler::bitmapa[pomocnicza] = 1;
		}
		pomocnicza++;
	}

//	table->at(5).empty()
}

int O1Scheduler::time_slice_calculation(const std::shared_ptr<PCB>& giving_process) {
	int time_slice;
	if (giving_process->dynamic_priority>= 100 && giving_process->dynamic_priority < 120) {
		time_slice = (140 - giving_process->dynamic_priority) * 4;
	}
	else if (giving_process->dynamic_priority >= 120 && giving_process->dynamic_priority < 140) {
		time_slice = (140 - giving_process->dynamic_priority) * 1;
	}
	return time_slice;
}

void O1Scheduler::move_process_to_expired_table(int new_dynamic_priority, std::shared_ptr<PCB>& pcb) {
	expired_array_pointer->at(new_dynamic_priority).push_back(active_array_pointer->at(pcb->dynamic_priority)[0]);
	active_array_pointer->at(pcb->dynamic_priority).erase(active_array_pointer->at(pcb->dynamic_priority).begin());
	pcb->dynamic_priority = new_dynamic_priority;
}

void O1Scheduler::calculating_dynamic_priority(int bonus,std::shared_ptr<PCB>& pcb) {

	pcb->dynamic_priority = std::max(100, (std::min(pcb->static_process_priority - bonus + 5, 139)));
}

int O1Scheduler::calculating_bonus(const std::shared_ptr<PCB>&giving_process) {
	if (giving_process->average_sleep_time >= 0 && giving_process->average_sleep_time < 20) {
		return 0;
	}
	else if (giving_process->average_sleep_time >= 20 && giving_process->average_sleep_time < 40) {
		return 1;
	}
	else if (giving_process->average_sleep_time >= 40 && giving_process->average_sleep_time < 60) {
		return 2;
	}
	else if (giving_process->average_sleep_time >= 60 && giving_process->average_sleep_time < 80) {
		return 3;
	}
	else if (giving_process->average_sleep_time >= 80 && giving_process->average_sleep_time < 100) {
		return 4;
	}
	else if (giving_process->average_sleep_time >= 100 && giving_process->average_sleep_time < 120) {
		return 5;
	}
	else if (giving_process->average_sleep_time >= 120 && giving_process->average_sleep_time < 140) {
		return 6;
	}
	else if (giving_process->average_sleep_time >= 140 && giving_process->average_sleep_time < 160) {
		return 7;
	}
	else if (giving_process->average_sleep_time >= 160 && giving_process->average_sleep_time < 180) {
		return 8;
	}
	else if (giving_process->average_sleep_time >= 180 && giving_process->average_sleep_time < 200) {
		return 9;
	}
	else if (giving_process->average_sleep_time >= 200) {
		return 10;
	}
}