#pragma once
#include <queue>
#include "Node.h"
class BSTIterator
{
public:
	BSTIterator(Node* node = nullptr);
	~BSTIterator();
	BSTIterator(const BSTIterator& it);
	bool valid();
	void inOrderTraversal(Node* node);
	bool operator==(const BSTIterator& it) { return this->current == it.current; };
	bool operator!=(const BSTIterator& it) { return this->current != it.current; };
	BSTIterator& operator=(const BSTIterator& it);
	Node* getCurrent() { return this->current; };
	BSTIterator& operator++();
	BSTIterator& operator++(int);
	std::queue<Node*> q;
private:
	Node* current;
};

