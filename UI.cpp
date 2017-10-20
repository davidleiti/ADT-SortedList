#include "UI.h"
#include <iostream>
#include <sstream>

using namespace std;

void UI::start()
{
	printMenu();
	bool stop = false;
	while (!stop) {
		try {
			int cmd = readInteger("Enter a command: ");
			switch (cmd) {
			case 1: {
				string name = readString("Enter the name of the donator: ");
				int amount = readInteger("Enter the amount offered: ");
				list.add(Donator{ name,amount });
				cout << "Donator added successfully! " << endl << endl;
				break;
			}
			case 2: {
				string name = readString("Enter the name of the donator: ");
				int amount = readInteger("Enter the amount offered: ");
				list.remove(Donator{ name,amount });
				cout << "Donator removed successfully! " << endl << endl;
				break;
			}
			case 3:
			{
				string name = readString("Enter the name of the donator: ");
				int amount = readInteger("Enter the amount offered: ");
				cout << name << " is seated at chair nr " << list.getPosition(Donator{ name,amount }) << endl << endl;
				break;
			}
			case 4: {
				printList();
				break;
			}
			case 5: {
				chooseRandomDonators();
				break;
			}
			case 6:
			{
				chooseOneDonator();
				break;
			}
			case 0:
			{
				stop = true;
				cout << "Leaving program...bye! " << endl;
				break;
			}
			default:
				cout << "Oops,  invalid command, please try again!" << endl;
			}
		}
		catch (runtime_error& re) {
			cout << re.what() << endl << endl;
		}
	}
}

void UI::printMenu()
{
	cout << "\t1. Add a new donator" << endl;
	cout << "\t2. Remove a donator" << endl;
	cout << "\t3. Show the seat number of a donator " << endl;
	cout << "\t4. Show all donators" << endl;
	cout << "\t5. Choose random winners" << endl;
	cout << "\t0. Exit" << endl;
}

void UI::chooseRandomDonators()
{
	int sum = 0;
	for (auto it = list.begin(); it != list.end(); it++)
		sum += it.getCurrent().getAmount();
	int giftsNr = sum / 500;
	if (giftsNr) 
		cout << "Congratulations to the above donators! " << endl;
	for (int i = 0; i < giftsNr; i++) {
		int randNr = rand() % list.getLength() + 1;
		cout << this->list.getElementAtPos(randNr).getName() << " (" << this->list.getElementAtPos(randNr).getAmount() << ")" << endl; ;
	}
}

void UI::chooseOneDonator()
{
	int randNr = rand() % list.getLength() + 1;
	cout << "Congratulations to: ";
	cout << this->list.getElementAtPos(randNr).getName() << " (" << this->list.getElementAtPos(randNr).getAmount() << ")" << endl; ;
}

string UI::readString(const string & msg)
{
		cout << msg;
		string input = "";
		getline(cin, input);
		return input;
}

int UI::readInteger(const string& msg)
{
	int res;
	string input = "";
	bool stop = false;
	while (!stop) {
		try {
			cout << msg;
			getline(cin, input);
			stringstream myStream(input);
			if (myStream >> res) stop = true;
			else throw "Not an integer!";
		}
		catch (const char* errMsg) {
			cout << errMsg << endl;
		}
	}
	return res;
}

void UI::printList()
{
	int count = 1;
	if (this->list.getLength() != 0)
		for (auto it = this->list.begin(); it!=this->list.end(); it++)
			cout << count++ << ". " << it.getCurrent().getName() << ": " << it.getCurrent().getAmount() << endl;
}


