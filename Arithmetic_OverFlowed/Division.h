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
	int decimal_point;
	int k;
public:
	Divide() { }
	Divide(LinkedList obj1, LinkedList obj2) :
		head3(nullptr)
	{
		decimal_length = 0;
		decimal_point = 0;
		k = 0;
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
			k = sup;
		}
	}
	LinkedList getResult()
	{
		return head3;
	}
	int getDecimalPointPos() const
	{
		return decimal_point;
	}
	void division();
	int divisionFor(LinkedList aug, int loc, int place);
	int sequentialDivi(LinkedList head1, LinkedList& r, int val1, int val2, int val2Ceil);
	bool compareValue(LinkedList head, LinkedList& testHead1, LinkedList& testHead2, int lower, int upper);
	void stepNextNode(int& pos, int& place);
	int getNextDigit(LinkedList head, int pos, int sub);
	LinkedList getFirstDiviNum(LinkedList head1, int& offsetNode, int& place);
	int getFirstThreeDigit(LinkedList head);
	int getFirstTwoDigit(LinkedList head, int& ceiling);
	bool isfloor(LinkedList head, int pos, int look);
	bool isfloor(LinkedList head, int pos);
	int getUpmostDigit(int num);
	int modifyLowerBound(int num, int secondary);
	LinkedList newNodeInt(int place);
	LinkedList cutNodes(LinkedList head, int pos);



};


#endif