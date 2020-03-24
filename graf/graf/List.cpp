#include "List.h"
#include <iostream>

List::List() : start(NULL), end(NULL), size(0) {
}

List::List(const List& l) 
{
	start = end = NULL;
	size = 0;
	Node* p = l.start;
	while (p != NULL) {
		insert(p->getInfo());
		p = p->getNext();
	}
}

void List::insert(int x) 
{
	if (size == 0)
		start = end = new Node(x, NULL);
	else
	{
		Node* p = new Node(x, NULL);
		end->setNext(p);
		end = p;
	}
	size++;
}

List::~List()
{
	Node* p = start, * o;
	while (p != NULL) {
		o = p;
		p = p->getNext();
		delete o;
	}
	start = end = NULL;
	size = 0;
}

Node* List::getStart() const
{
	return start;
}

int List::getLength() const
{
	return size;
}

List& List::operator=(const List& other)
{
	if (this != &other)
	{
		this->start = this->end = NULL;
		size = 0;
		Node* p = other.start;
		while (p != NULL) {
			insert(p->getInfo());
			p = p->getNext();
		}
	}
	return *this;
}

std::ostream& operator<<(std::ostream& out, List* l)
{
	Node* p = l->getStart();
	while (p != NULL)
	{
		out << p << ' ';
		p = p->getNext();
	}
	return out;
}