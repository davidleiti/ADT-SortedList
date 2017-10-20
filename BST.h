#pragma once
#include <queue>
#include "Node.h"
#include "BSTIterator.h"
class BST
{
public:
	Node* root;
	BST() { this->root = nullptr; this->size = 0; };
	BST(BST& tree);
	BST& operator=(BST& tree);
	~BST();	
	int getLength() const { return this->size; };
	bool isEmpty() { return this->size == 0; };
	Node* getMax() const;
	Node* getMin() const;
	int getPosition(Donator& d) const;
	Node* getElementAtPosition(int pos) const;
	void insert(Donator& d);
	bool search(Donator & d) const;
	void remove(Donator & d);
private:
	int size;
	void copyTree(Node*& root, Node*& sourceRoot);
	void destroyRec(Node* n);
	void getMaxRec(Node* root, Node** result) const;
	void getMinRec(Node* root, Node** result) const;
	void searchRec(Donator& d, Node* r, bool* ok) const;
	void getPosRec(Donator& d, Node* r, int* result, int currentPos = 0) const;
	Node* removeRec(Donator & d, Node* root,bool *found);
};

