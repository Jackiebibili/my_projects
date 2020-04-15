#ifndef NODE_H
#define NODE_H
#include<iostream>
#include<cstdlib>

class Node
{
private:
	int num = 0;
	int loc = 0;
	Node* next = nullptr;
public:
	Node();	//default constructor
	Node(int num);	//overloading constructor
	Node(int pos, int num);
	Node(const Node& right);
	int getNum() const;
	int getPos() const;
	Node* getNext();

	void setNum(int n);
	void setPos(int pos);
	void setNext(Node* ptr);

	~Node();
};
#endif