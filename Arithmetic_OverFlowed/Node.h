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
	Node* head = nullptr;
public:
	Node();	//default constructor
	Node(int num);	//overloading constructor
	Node(int pos, int num);

	int getNum() const;
	int getPos() const;

	void setNum(int n);
	void setPos(int pos);
	void setNextPtr(Node*& ptr);
	void addNode(int num, int pos);
	int getListValue(int pos);
	void setValue(int pos, int val);
	void initializeResult(int totalNode);
	void incrementValue(int pos, int val);

	~Node();
};
#endif