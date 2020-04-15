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
	Add(LinkedList obj1, LinkedList obj2, int totalNodes = 0)
	{
		head1 = obj1;
		head2 = obj2;
		if (totalNodes == 0)
		{
			//addition initialization
			head3 = head1;
		}
		else
		{
			//multiplication initialization--all to 0's
			head3.initializeResult(totalNodes);
		}
	}
	Add(Node* obj1, Node* obj2) :
		head1(obj1),
		head2(obj2)
	{
		head3 = head1;
	}
	Add(Add& obj);
	LinkedList getResult()
	{
		return head3;
	}
	int getHead1_NodeNum() const
	{
		return head1.getNodeNum();
	}
	int getHead2_NodeNum() const
	{
		return head2.getNodeNum();
	}
	int getHead1_ListValue(int pos) const
	{
		return head1.getListValue(pos);
	}
	int getHead2_ListValue(int pos) const
	{
		return head2.getListValue(pos);
	}
	void addition();
	int nodeNumAddition(int m, int n);
	void overflowAddition(int n);
	void sequentialFlow(const int val, int pos);
	void plus(const int val, int pos);


};


#endif // !ADDITION_H

