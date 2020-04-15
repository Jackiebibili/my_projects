#ifndef DIVISION_H
#define DIVISION_H
#include "Node.h"
#include "LinkedList.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"

class Divide
{
private:
	LinkedList head1;
	LinkedList head2;
	LinkedList head3;
	int decimal_length;

public:
	Divide() { }
	Divide(LinkedList obj1, LinkedList obj2) :
		head3(nullptr)
	{
		decimal_length = 0;
		head1 = obj1;
		head2 = obj2;
		if (!(head1 >= head2))
		{
			int sup = 0;
			if (head1.getNumDigits() != head2.getNumDigits())
				sup = head2.getNumDigits() - head1.getNumDigits();

			//supply upmost 0's in (0.00xxx00abcdef)
			for (int i = 0; i < sup; i++)
				head3.addNode(0, i);
		}
	}
	void division();
};


#endif