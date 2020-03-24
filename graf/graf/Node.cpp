#include "Node.h"

Node::Node() : info(0), next(NULL){
}

Node::Node(int i, Node* n) : info(i), next(n){
}

Node::Node(const Node& nod) : info(nod.info), next(nod.next){
}

void Node::setInfo(int i) {
	info = i;
}

void Node::setNext(Node* n) {
	next = n;
}

int Node::getInfo() const {
	return info;
}

Node* Node::getNext() const {
	return next;
}

Node& Node::operator=(const Node& other)				
{
	this->info = other.getInfo();
	this->next = other.getNext();
	return *this;
}

std::ostream& operator<<(std::ostream& out, Node* node)
{
	out << node->getInfo();
	return out;
}