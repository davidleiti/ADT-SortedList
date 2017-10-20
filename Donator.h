#pragma once
#include <string>
class Donator
{
public:
	Donator() : name(""), sum(0) {};
	Donator(const std::string& n, int s) : name(n), sum(s) {};
	Donator(const Donator& d) { this->name = d.name; this->sum = d.sum; };
	std::string getName() { return this->name; };
	int getAmount() const { return this->sum; };
	std::string toString() const { return this->name + " donated " + std::to_string(this->sum); };
	friend std::istream& operator >> (std::istream& in, Donator& d) {};
	bool operator==(const Donator& d) const { return this->name == d.name && this->sum == d.sum; };
	bool operator!=(const Donator& d) const { return this->name != d.name || this->sum != d.sum; };
	~Donator() {};
private:
	std::string name;
	int sum;
};

