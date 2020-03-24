#pragma once
#ifndef _NODE_H
#define _NODE_H

#include <iostream>

class Node
{
	int info;
	Node* next;
	friend std::ostream& operator<<(std::ostream&, Node*);
public:
	Node();
	Node(int, Node*);
	Node(const Node&);
	void setInfo(int);
	void setNext(Node*);
	int getInfo() const;
	Node* getNext() const;
	Node& operator=(const Node&);
};

#endif
