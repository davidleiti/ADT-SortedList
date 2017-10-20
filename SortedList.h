#pragma once
#include "BST.h"
#include "queue.h"
#include <iostream>

class SortedList;
class ListIterator {
public :
	std::queue<Donator> q;
	Donator current;
	SortedList* list;
	~ListIterator();
	ListIterator(SortedList& l);
	ListIterator(const ListIterator& it);
	ListIterator& operator=(const ListIterator& it);
	bool valid() { return this->q.size() != 0 || this->current == Donator{}; };
	Donator& getCurrent() { return this->current; };
	ListIterator& operator++(int) { this->operator++(); return *this; };
	bool operator==(const ListIterator& it) { return this->current == it.current; };
	bool operator!=(const ListIterator& it) { return this->current != it.current; };
private:
	ListIterator& operator++();
	void inOrderTraversal(Node* node);
};

class SortedList {
private:
	BST tree;
public:
	friend ListIterator;
	SortedList() {};
	SortedList(BST& t) { this->tree = t; };
	SortedList& operator=(SortedList& l) { this->tree = l.tree; return *this; };
	SortedList(SortedList& l) { this->tree = l.tree; };
	int getLength() { return this->tree.getLength(); };
	bool isEmpty() { return this->tree.isEmpty(); };
	Donator& first();
	Donator& last();
	ListIterator begin();
	ListIterator end();
	Donator getElementAtPos(int pos);
	int getPosition(Donator& d) { return this->tree.getPosition(d); };
	void add(Donator& d);
	void remove(Donator & d);
	Donator removeFromPos(int p);
	~SortedList() {};
};


