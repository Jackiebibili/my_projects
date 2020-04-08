#ifndef ADDITION_H
#define ADDITION_H
#include<iostream>
#include<cstdlib>
#include "Node.h"
class Add
{
private:
	Node* head1;
	Node* head2;
public:
	Add();
	Add(int num1, int num2);

	void addNode(Node*& head, int num, int pos);


};


#endif // !ADDITION_H

