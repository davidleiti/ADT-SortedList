#include "SortedList.h"

void ListIterator::inOrderTraversal(Node * node)
{
	if (!node)
		return;
	inOrderTraversal(node->left);
	this->q.push(node->info);
	inOrderTraversal(node->right);
}

ListIterator::~ListIterator()
{  
	delete this->list;
}

ListIterator::ListIterator(SortedList & l)
{
	if (l.getLength() == 0) 
		this->current = Donator{};
	else {
		BST itTree{ l.tree };
		SortedList* itList = new SortedList{ itTree };
		this->list = itList;
		this->inOrderTraversal(this->list->tree.root);
		this->current = q.front();
		this->q.push(Donator{});
		this->q.pop();
	}
}

ListIterator::ListIterator(const ListIterator & it)
{
	this->q = it.q; 
	this->current = it.current;
	this->list = new SortedList{ *it.list };
}

ListIterator & ListIterator::operator=(const ListIterator & it)
{
	this->q = it.q;
	this->current = it.current;
	this->list = new SortedList{ *it.list };
	return *this;
}

ListIterator & ListIterator::operator++()
{
	this->current = this->q.front();
	this->q.pop();
	return *this;
}

ListIterator SortedList::begin()
{
	ListIterator it{*this};
	return it;
}

ListIterator SortedList::end()
{
	ListIterator it{ *this };
	while (it.q.size() > 0)
		it++;
	return it;
}

Donator SortedList::getElementAtPos(int pos)
{
	return this->tree.getElementAtPosition(pos)->info;
}

void SortedList::add(Donator & d)
{
	if (tree.search(d))
		throw(runtime_error("Donator already added!"));
	tree.insert(d);
}

void SortedList::remove(Donator & d)
{
	if (!tree.search(d))
		throw(runtime_error("Donator not registered yet!"));
	tree.remove(d);
}

Donator SortedList::removeFromPos(int p)
{
	Donator d = getElementAtPos(p);
	remove(d);
	return d;
}

Donator & SortedList::first()
{
	if (isEmpty())
		throw(std::runtime_error("List is empty"));
	return this->tree.getMax()->info;
}

Donator & SortedList::last()
{
	if (isEmpty())
		throw(std::runtime_error("List is empty"));
	return this->tree.getMin()->info;
}

