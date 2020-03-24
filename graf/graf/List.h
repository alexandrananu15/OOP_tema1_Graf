#ifndef _LIST_H
#define _LIST_H

#include "Node.h"

class List
{
	Node* start, * end;
	unsigned size;
	friend std::ostream& operator<<(std::ostream&, List*);
public:
	List();
	List(const List&);
	void insert(int);
	~List();
	int getLength() const;
	Node* getStart() const;
	List& operator=(const List&);
};

#endif 
