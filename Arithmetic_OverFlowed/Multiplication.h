#ifndef MULTIPLICATION_H
#define MULTIPLICATION_H
#include<iostream>
#include<cstdlib>
#include "Node.h"
#include "LinkedList.h"
#include "Addition.h"
//using namespace std;

class Multiply
{
private:
	Add obj;
	LinkedList head;
public:
	Multiply() { }
	Multiply(LinkedList obj1, LinkedList obj2) :
		obj(obj1, obj2, nodeNumMulti(obj1.getNodeNum(), obj2.getNodeNum()))
	{ }
	LinkedList& getResult()
	{
		return head;
	}

	void multiplication();
	void overflowMulti(int m, int n);
	int nodeNumMulti(int m, int n);
};


#endif

