#include <iostream>
#include <Windows.h>
#include <crtdbg.h>
#include "UI.h"
#include "queue.h"
#include <assert.h>
using namespace std;

void testDonator();
void testNode();
void testTree();
void testList();

int main() {
	srand(0);
	{
		testDonator();
		testNode();
		testTree();
		testList();
		SortedList l{};
		l.add(Donator{ "Malcolm Scott",200 });
		l.add(Donator{ "Eddie Sanders",100 });
		l.add(Donator{ "Andrew Scofield",50 });
		l.add(Donator{ "Peter Gregory",140 });
		l.add(Donator{ "Laura Wells",250 });
		l.add(Donator{ "Iris McCarter",95 });
		l.add(Donator{ "Andrea Burrows",230 });
		l.add(Donator{ "Dwight Schrute",300 });
		UI ui{l};
		ui.start();
		}
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}

void testDonator() {
	Donator a{};
	Donator b{};
	assert(a == b);
	Donator c{ "c",2 };
	assert(a != c);
	Donator d{ "d",2 };
	assert(c != d);
	Donator e{ "d",3 };
	assert(d != e);
	Donator f{ "d",3 };
	assert(e == f);
}

void testNode() {
	Node a{ Donator{"a",1} };
	assert(a.info.getName() == "a");
	assert(a.info.getAmount() == 1);
	Node* b = new Node{ Donator{"b",2} };
	Node* c = new Node{ b };
	delete b;
	delete c;
	Node d{ a };
	Node e{ Donator{} };
	e = a;
}

void testTree() {
	// Constructor and basic insertion test //
	BST tree1{};
	assert(tree1.root == nullptr);
	assert(tree1.getLength() == 0);
	assert(tree1.getMin() == nullptr);
	assert(tree1.getMax() == nullptr);
	Donator a{ "a",1 };
	Donator b{ "b",2 };
	Donator c{ "c",3 };
	Donator d{ "d",4 };
	tree1.insert(a);
	tree1.insert(b);
	tree1.insert(c);
	tree1.insert(d);
	assert(tree1.getLength() == 4);
	assert(tree1.getMax()->info == d);
	assert(tree1.getMin()->info == a);
	assert(tree1.getPosition(a) == 4);
	assert(tree1.getPosition(c) == 2);
	assert(tree1.getPosition(b) == 3);
	assert(tree1.getPosition(d) == 1);
	assert(tree1.getElementAtPosition(4)->info == a);
	try {
		Donator n{ "Not in the list",10 };
		tree1.getPosition(n);
		cout << "Error should've been raised" << endl;
	}
	catch (runtime_error&) {};
	//---------------------------------//

	// Removal tests //
	
	assert(tree1.search(c) == true);
	tree1.remove(b);
	tree1.remove(d);
	tree1.remove(a);
	assert(tree1.getLength() == 1);
	assert(tree1.search(a) == false);
	tree1.remove(a);
	assert(tree1.getLength() == 1);
	assert(tree1.search(b) == false);
	assert(tree1.search(c) == true);
	tree1.remove(d);
	// ---------------------- //

	// Removing elements with the same value // 
	Donator aLeft{ "aLeft",1 };
	Donator aRight{ "aRight",1 };
	tree1.insert(b);
	tree1.insert(c);
	tree1.insert(d);
	tree1.insert(a);
	tree1.insert(aLeft);
	tree1.insert(aRight);
	assert(tree1.search(aRight) == true);
	assert(tree1.getMin()->info == aRight);
	tree1.remove(aLeft);
	tree1.remove(aRight);
	tree1.remove(a);
	Donator e{ "e",5 };
	tree1.insert(e);
	tree1.remove(c); 
	tree1.insert(a);
	tree1.insert(aLeft);
	tree1.insert(aRight);
	tree1.remove(aRight);
	// ----------------------------//

	//		Copy constructor and operator= // 
	BST tree2{ tree1 };
	tree2.remove(d);
	assert(tree1.getLength() == 7);
	assert(tree2.getLength() == 6);
	BST tree3;
	tree3 = tree2;
	tree3.insert(aLeft); 
	assert(tree2.getLength() == 6);
	assert(tree3.getLength() == 7);
	BST empty{};
	BST empty2{ empty };
	BST empty3;
	empty3 = empty2;
}

void testList() {
	// Basic operations //
	BST tree{};
	SortedList l{ tree };
	assert(l.getLength() == 0);
	Donator b{ "b",2 }; 
	Donator a{ "a",1 };
	Donator c{ "c",3 };
	l.add(b);
	l.add(a);
	l.add(c);
	assert(l.getElementAtPos(1) == c);
	assert(l.getElementAtPos(2) == b);
	assert(l.getElementAtPos(3) == a);
	assert(l.getPosition(b) == 2);
	assert(l.first() == c);
	assert(l.last() == a);
	try {
		l.getElementAtPos(4);
		cout << "Exception should've been thrown" << endl;
	}
	catch (runtime_error&) {};
	assert(l.getLength() == 3);
	l.remove(a);
	assert(l.getLength() == 2);
	l.removeFromPos(2);
	assert(l.getLength() == 1);
	assert(l.isEmpty() == false);
	// ----------------------------// 

	// Iterator //
	l.add(a);
	l.add(b);
	try {
		l.add(a);
		cout << "Should've raised an exception" << endl;
	}
	catch (runtime_error&) {}; try {
		l.remove(Donator{ "Not in the list",0 });
		cout << "Should've raised an exception" << endl;
	}
	catch (runtime_error&) {};
	int count = 0;
	for (ListIterator it = l.begin(); it != l.end(); it++)
		count++;
	assert(count == l.getLength());
	ListIterator it{ l };
	it++;
	assert(it.valid());
	assert(l.end().getCurrent() == Donator{});
	SortedList empty{};
	ListIterator emptyIterator{ empty };
	assert(empty.isEmpty() == true);
	assert(emptyIterator.valid());
	try {
		empty.first();
		cout << "Should've raised an excpetion" << endl;
	}
	catch (runtime_error&) {};
	try {
		empty.last();
		cout << "Should've raised an excpetion" << endl;
	}
	catch (runtime_error&) {};
	emptyIterator = it;
}

