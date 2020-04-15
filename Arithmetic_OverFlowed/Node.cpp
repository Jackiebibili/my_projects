#include "Node.h"
#include<iostream>
#include<cstdlib>
using namespace std;

Node::Node()
{ }

Node::Node(int n)
{
	num = n;
}

Node::Node(int pos, int n)
{
	loc = pos;
	num = n;
}

Node::Node(const Node& right)
{
	num = right.num;
	loc = right.loc;
	next = nullptr;
	//avoid address assignment
}


int Node::getNum()const
{
	return num;
}

int Node::getPos()const
{
	return loc;
}

Node* Node::getNext()
{
	//return current's next
	return next;
}


void Node::setNum(int n)
{
	num = n;
}

void Node::setPos(int pos)
{
	loc = pos;
}

void Node::setNext(Node* ptr)
{
	next = ptr;
}


Node::~Node()
{ }