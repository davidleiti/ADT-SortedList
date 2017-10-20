#include "BST.h"
#include <iostream>

using namespace std;

BST::BST(BST & tree)
{
	if (tree.root == nullptr)
		root = nullptr;
	else {
		copyTree(this->root, tree.root);
		this->size = tree.size;
	}
}

void BST::copyTree(Node *& root, Node *& sourceRoot)
{
	if (sourceRoot == nullptr)
	{
		root = nullptr;
	}
	else
	{
		root = new Node{sourceRoot->info};
		root->leftNr = sourceRoot->leftNr;
		root->rightNr = sourceRoot->rightNr;
		copyTree(root->left, sourceRoot->left);
		copyTree(root->right, sourceRoot->right);
	}
}

BST & BST::operator=(BST & tree)
{
	if (tree.root == nullptr)
		root = nullptr;
	else {
		copyTree(this->root, tree.root);
		this->size = tree.size;
	}
	return *this;
}

void BST::destroyRec(Node * n)
{
	if (n) {
		destroyRec(n->right);
		destroyRec(n->left);
		delete n;
	}
}

BST::~BST()
{
	destroyRec(this->root);
}

Node* BST::getMax() const
{
	Node* result = nullptr;
	getMaxRec(this->root, &result);
	return result;
}

Node* BST::getMin() const
{
	Node* result = nullptr;
	getMinRec(this->root, &result);
	return result;
}

void BST::insert(Donator & d)
{
	if (!root) {	 //Tree is empty
		this->root = new Node{ d };
		this->size++;
		return;
	}
	Node* node = this->root;
	while (node) {
		if (node->info.getAmount() < d.getAmount()) {
			node->leftNr++;
			if (node->left)
				node = node->left;
			else {
				node->left = new Node{ d };
				this->size++;
				return;
			}
		}
		else if (node->info.getAmount() > d.getAmount()) {
			node->rightNr++;
			if (node->right)
				node = node->right;
			else {
				node->right = new Node{ d };
				this->size++;
				return;
			}
		}
		else {		//Node with the same amount, we check for the leftNr and rightNr, so we keep the tree as balanced as possible
			if (node->leftNr <= node->rightNr) {
				Node* newNode = new Node{ d };
				newNode->left = node->left;
				node->left = newNode;
				this->size++;
				node->leftNr++;
				return;
			}
			else {
				Node* newNode = new Node{ d };
				newNode->right = node->right;
				node->right = newNode;
				this->size++;
				node->rightNr++;
				return;
			}
		}
	}
}

int BST::getPosition(Donator & d) const
{
	int res = -1;
	getPosRec(d, this->root, &res);
	if (res == -1)
		throw(std::runtime_error("Element not found..."));
	return res;
}

Node * BST::getElementAtPosition(int pos) const
{
	if (pos < 1 || pos > size)
		throw(runtime_error("Not a valid position!"));

	Node* node = this->root;
	int currentPos = node->leftNr + 1;
	while (currentPos != pos) {
		if (currentPos > pos) {
			currentPos = currentPos - node->leftNr + node->left->leftNr;
			node = node->left;
		}
		else {
			currentPos += node->right->leftNr + 1;
			node = node->right;			
		}
	}
	return node;
}

bool BST::search(Donator & d) const
{
	bool ok = false;
	this->searchRec(d, this->root, &ok);
	return ok;
}

void BST::remove(Donator & d)
{
	bool found = false;
	this->root = removeRec(d, this->root, &found);
	if (found)
		this->size--;
}

void BST::getMaxRec(Node * root, Node ** result) const
{
	if (root)
		if (root->left)
			getMaxRec(root->left, result);
		else
			*result = root;
}

void BST::getMinRec(Node * root, Node ** result) const
{
	if (root)
		if (root->right) {
			getMinRec(root->right, result);
		}
		else
			*result = root;
}

void BST::searchRec(Donator & d, Node * r, bool * ok) const
{
	if (r) {
		if (r->info == d)
			*ok = true;
		else if (r->info.getAmount() < d.getAmount())		//We have to look left
			searchRec(d, r->left, ok);
		else if (r->info.getAmount() > d.getAmount())		//We have to look right
			searchRec(d, r->right, ok);
		else {		//We have to look on both sides, since in case of duplicate ammounts, we can't know where the element will be
			searchRec(d, r->left, ok);
			searchRec(d, r->right, ok);
		}
	}
}

void BST::getPosRec(Donator & d, Node * r, int * result, int currentPos) const
{
	if (r) {
		if (r->info == d) {
			*result = r->leftNr + currentPos + 1;
			return;
		}
		else if (r->info.getAmount() < d.getAmount())
			getPosRec(d, r->left, result, currentPos);
		else if (r->info.getAmount() > d.getAmount())
			getPosRec(d, r->right, result, r->leftNr + currentPos + 1);
		else{
			getPosRec(d, r->left, result, currentPos);
			getPosRec(d, r->right, result, r->leftNr + currentPos + 1);
		}
	}
}

Node* BST::removeRec(Donator & d, Node * r,bool *found)
{
	if (!r)
		return nullptr;
	if (r->info.getAmount() < d.getAmount()) {
		r->left = removeRec(d, r->left,found );
	}
	else if (r->info.getAmount() > d.getAmount()) {
		r->right = removeRec(d, r->right,found );
	}
	else if (r->info.getName() == d.getName()) {
		*found = true;
		if (r->left == nullptr && r->right == nullptr) {
			delete r;
			r = nullptr;
		}
		else if (r->left == nullptr) {	
			Node* temp = r;
			r = r->right;
			delete temp;
		}
		else if (r->right == nullptr) {
			Node* temp = r;
			r = r->left;
			delete temp;
		}
		else {/*
			Node* min = nullptr;
			getMinRec(r->left, &min);
			r->info = min->info;
			r->left = removeRec(min->info, r->left, found);*/
			Node* max = nullptr;
			getMaxRec(r->right, &max);
			r->info = max->info;
			r->right = removeRec(max->info, r->right, found);
		}
	}
	else {
		Node* left = removeRec(d, r->left, found);
		if (found) {
			r->left = left;
		}
		else {
			Node* right = removeRec(d, r->right, found);
			if (found)
				r->right = right;
		}
	}
	return r;
}

