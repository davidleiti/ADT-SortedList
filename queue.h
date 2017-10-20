#pragma once
#include <iostream>
#include "Donator.h"
using namespace std;

struct node {
	Donator info;
	struct node *next;
};

class Queue {
private:
	node *rear;
	node *end;
	int elems;
public:
	Queue() : rear(nullptr), end(nullptr) {};
	~Queue();
	Queue(const Queue& q);
	Queue& operator=(const Queue& q);
	void push(Donator& data);
	void pop();
	int size() {return this->elems;};
	Donator& front() { return this->end->info; };
	void display();
};
