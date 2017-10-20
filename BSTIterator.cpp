#include "BSTIterator.h"

BSTIterator::BSTIterator(Node * node)
{
	this->inOrderTraversal(node);
	if (this->q.size() > 0)
		this->current = q.front();
	this->q.push(nullptr);
	q.pop();
}

BSTIterator::~BSTIterator()
{
}

BSTIterator::BSTIterator(const BSTIterator & it)
{
	this->current = it.current;
	this->q = it.q;
}

bool BSTIterator::valid()
{
	return this->q.size() == 0;
}

void BSTIterator::inOrderTraversal(Node * node)
{
	if (!node)
		return;
	inOrderTraversal(node->left);
	this->q.push(node);
	inOrderTraversal(node->right);
}

BSTIterator & BSTIterator::operator=(const BSTIterator & it)
{
	this->current = it.current;
	this->q = it.q;
	return *this;
}

BSTIterator & BSTIterator::operator++()
{
	this->current = q.front();
	q.pop();
	return *this;
}

BSTIterator & BSTIterator::operator++(int)
{
	this->operator++();
	return *this;
}

