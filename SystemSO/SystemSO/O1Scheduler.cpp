#include "O1Scheduler.h"



O1Scheduler::O1Scheduler() {
	active_array_pointer = std::make_shared<ProcessTable>(active_array);
	expired_array_pointer = std::make_shared<ProcessTable>(expired_array);
}

O1Scheduler::~O1Scheduler(){}

std::shared_ptr<PCB> O1Scheduler::O1SchedulingAlgorithm() {
	while (1) {

	}


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
	}
}

void O1Scheduler::add_new_process_to_expired(const std::shared_ptr<PCB>&giving_process) {
	expired_array_pointer->at(giving_process->staticPriority).push_back(giving_process);
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
}

void O1Scheduler::time_slice_calculation(std::shared_ptr<PCB>& giving_process) {
	if (giving_process->dynamicPriority>= 100 && giving_process->dynamicPriority < 120) {
		giving_process->time_slice= (140 - giving_process->dynamicPriority) * 4;
	}
	else if (giving_process->dynamicPriority >= 120 && giving_process->dynamicPriority < 140) {
		giving_process->time_slice = (140 - giving_process->dynamicPriority) * 1;
	}

}

void O1Scheduler::move_process_to_expired_table(int new_dynamic_priority, std::shared_ptr<PCB>& pcb) {
	expired_array_pointer->at(new_dynamic_priority).push_back(active_array_pointer->at(pcb->dynamicPriority)[0]);
	active_array_pointer->at(pcb->dynamicPriority).erase(active_array_pointer->at(pcb->dynamicPriority).begin());
	pcb->dynamicPriority = new_dynamic_priority;
}

void O1Scheduler::calculating_dynamic_priority(std::shared_ptr<PCB>& pcb) {
	int bonus = calculating_bonus(pcb);
	pcb->dynamicPriority = std::max(100, (std::min(pcb->staticPriority - bonus + 5, 139)));
}

int O1Scheduler::calculating_bonus(std::shared_ptr<PCB>&giving_process) {
	giving_process->average_sleep_time = giving_process->whenStartRunning - giving_process->whenStartWaiting;
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



void O1Scheduler::displayActiveArray() {
	for (int i = 100; i < 140; i++) {
		std::cout << i << " ";
		for (int j = 0; j < active_array_pointer->size(); j++) {
			std::cout << active_array_pointer->at(i)[j]->getProcessName << " " << active_array_pointer->at(i)[j]->getPID << " | ";
		}
		std::cout << std::endl;
	}
}
void O1Scheduler::displayExpiredArray() {
	for (int i = 100; i < 140; i++) {
		std::cout << i << " ";
		for (int j = 0; j < expired_array_pointer->size(); j++) {
			std::cout << expired_array_pointer->at(i)[j]->getProcessName << " " << expired_array_pointer->at(i)[j]->getPID << " | ";
		}
		std::cout << std::endl;
	}
}

void O1Scheduler::displayBitmap() {
	for (int i = 100; i < bitmapa.size(); i++) {
		std::cout << i<<":"<<bitmapa[i] << " ";
	}
	std::cout<<std::endl;
}