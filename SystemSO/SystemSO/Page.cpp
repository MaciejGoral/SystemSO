#include "Page.h"



void Page::UstTabStronic(PageTable* newpageTable)
{
	this->pageTable = newpageTable;
}

PageTable* Page::PobTabStronic()
{
	return this->pageTable;
}
void Page::UstWielTabStronic(int num)
{
	this->pageTableSize = num;
}
int Page::PobWielTabStronic()
{
	return this->pageTableSize;
}

void Page::UstWielLicznika(int num)
{
	this->licznik = num;
}

int Page::PobWielLicznika()
{
	return this->licznik;
}