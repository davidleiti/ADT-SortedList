#include "queue.h"
Queue::~Queue()
{
	while (end) {
		node* temp = end;
		end = end->next;
		delete temp;
		cout << "destructor called" << endl;
	}
}

Queue::Queue(const Queue & q)
{
	if (q.end == nullptr)
		this->end = nullptr;
	else {
		node* qEnd = q.end;
		node* qRear = q.rear;
		while (qEnd != qRear){
			this->push(qEnd->info);
			qEnd = qEnd->next;
		}
	}
}

Queue & Queue::operator=(const Queue & q)
{
	if (q.end == nullptr)
		this->end = nullptr;
	else {
		node* qEnd = q.end;
		node* qRear = q.rear;
		while (qEnd != qRear) {
			this->push(qEnd->info);
			qEnd = qEnd->next;
		}
	}
	return *this;
}

void Queue::push(Donator& data) {
	cout << "pushed once" << endl;
	node *temp = new node;
	temp->info = data;
	temp->next = nullptr;
	if (end == nullptr) {
		end = temp;
	}
	else {
		rear->next = temp;
	}
	rear = temp;
	elems++;
}

void Queue::pop() {

	node *temp = new node;

	if (end != nullptr) {
		temp = end;
		end = end->next;
		delete temp;
	}
	elems--;
}

void Queue::display() {
	node *p = end;
	if (end == nullptr) {
		cout << "Nothing to Display\n";
	}
	else {
		while (p != nullptr) {
			cout << p->info.toString() << endl;
			p = p->next;
		}
	}
}