#pragma once
#include "SortedList.h"
#include <string>
class UI
{
public:
	UI(SortedList& list) { this->list = list; };
	void start();
	~UI() {};
private:
	SortedList list;
	void printMenu();
	void chooseRandomDonators();
	void chooseOneDonator();
	std::string readString(const std::string& msg) ;
	int readInteger(const std::string& msg) ;
	void printList();
};

