#include "Node.h"
#include <iostream>

using namespace std;

Node::Node(Node * n)
{
	if (n) {
		this->info = n->info;
		this->left = n->left;
		this->right = n->right;
		this->leftNr = n->leftNr;
		this->rightNr = n->rightNr;
	}
}

Node::Node(const Node & n)
{
	this->info = n.info;
	this->right = n.right;
	this->left = n.left;
	this->rightNr = n.rightNr;
	this->leftNr = n.leftNr;
}


Node & Node::operator=(const Node & n)
{
	if (this == &n)
		return *this;
	this->info = n.info;
	this->right = n.right;
	this->left = n.left;
	this->rightNr = n.rightNr;
	this->leftNr = n.leftNr;
	return *this;
}

Node::~Node()
{}
