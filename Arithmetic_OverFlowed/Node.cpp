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

int Node::getNum()const
{
	return num;
}

int Node::getPos()const
{
	return loc;
}

void Node::setNum(int n)
{
	num = n;
}

void Node::setPos(int pos)
{
	loc = pos;
}

void Node::setNextPtr(Node*& ptr)
{
	next = ptr;
}


void Node::addNode(int num, int pos)
{
    Node* A = new Node, * ptr = head;
    A->num = num;
    A->loc = pos;
    A->next = nullptr;
    ptr = head;
    if (head == nullptr)
    {
        head = A;
        return;
    }
    else
    {
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }
        ptr->next = A;
    }
}


int Node::getListValue(int pos)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    if (!ptr)
        return -1;
    return ptr->num;
}


void Node::setValue(int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    ptr->num = val;
}


//initalize the result linked list with 0's
void Node::initializeResult(int totalNode)
{
    int i;
    for (i = 0; i < totalNode; i++)
    {
        addNode(0, i);
    }
}

void Node::incrementValue(int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->loc != pos)
    {
        ptr = ptr->next;
    }
    ptr->num += val;
}


Node::~Node()
{ }