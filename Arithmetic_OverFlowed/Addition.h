#ifndef ADDITION_H
#define ADDITION_H
#include<iostream>
#include<cstdlib>
#include "Node.h"
#include "LinkedList.h"

class Add
{
private:
	LinkedList head1;
	LinkedList head2;
	LinkedList head3;
public:
	Add() { }
	Add(LinkedList obj1, LinkedList obj2)
	{
		head1 = obj1;
		head2 = obj2;
		head3 = head1;
	}
	Add(Node* obj1, Node* obj2) :
		head1(obj1),
		head2(obj2)
	{
		head3 = head1;
	}
	LinkedList getResult()
	{
		return head3;
	}
	void addition();
	int nodeNumAddition(int m, int n);
	void overflowAddition(int n);
	void sequentialFlow(const int val, int pos);


};


#endif // !ADDITION_H

