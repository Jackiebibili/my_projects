#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList : public Node
{
	using Node::Node;

private:
	Node* head = nullptr;
	int numDigits = 0;
	int numNodes = 0;
public:
	LinkedList();
	LinkedList(Node* ptr);
	//copy constructor
	LinkedList(LinkedList*&);
	void initializeResult(Node* head1, int totalNode);
	LinkedList* operator=(LinkedList*& right);
	void addNode(int num, int pos);
	int getListValue(int pos);
	int getNodeNum() const;
	int getNumDigits() const;
	Node*& getHead();
	void setValue(int pos, int val);
	void initializeResult(int totalNode);
	void incrementValue(int pos, int val);
	void modifyNumberDigits();
	void modifyNumberNodes();
	int NodeNum();
	int numberDigits();
	void emptyList();
	void deleteAllNodes(Node*& ptr);

	~LinkedList();



};



#endif