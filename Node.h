#pragma once
#include "Donator.h"
#include <iostream>
class Node
{
public:
	Node(Donator& d, Node* l = nullptr, Node* r = nullptr, int lN = 0, int rN = 0) : info(d), left(l), right(r), leftNr(lN), rightNr(rN) {};
	Node(Node* n);
	Node(const Node& n);
	Node& operator=(const Node& n);
	~Node();
	Node* left;
	Node* right;
	int leftNr;
	int rightNr;
	Donator info;
};

