#ifndef SUBTRACTION_H
#define SUBTRACTION_H
#include<iostream>
#include "Node.h"
#include "LinkedList.h"

class Subtract
{
private:
	LinkedList head1;
	LinkedList head2;
	LinkedList head3;
public:
	Subtract() { }
	Subtract(LinkedList obj1, LinkedList obj2)
	{
		head1 = obj1;
		head2 = obj2;
		head3 = head1;
	}
	LinkedList getResult()
	{
		head3.clearTopZero();
		return head3;
	}
	void subtraction();
	int nodeNumSub(int m, int n);
	void underflowSubtract(int n);
	void sequentialUnderflow(const int val, int pos);
	bool numCompare() const;

};





#endif
