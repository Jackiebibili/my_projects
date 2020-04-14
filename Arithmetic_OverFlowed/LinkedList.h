#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList : public Node
{
	using Node::Node;

private:
	Node* head = nullptr;
	int numDigits = 0;
	int numNodes = 1;
public:
	LinkedList();
	LinkedList(Node* ptr);
	//copy constructor
	LinkedList(LinkedList&);
	void initializeResult(Node* head1, int totalNode);
	LinkedList operator=(const LinkedList& right);
	void addNode(int num, int pos);
	int getListValue(int pos) const;
	int getNodeNum() const;
	int getNumDigits() const;
	Node* getHead() const;
	void setValue(int pos, int val);
	void initializeResult(int totalNode);
	//void incrementValue(int pos, int val);
	void modifyNumberDigits();
	void modifyNumberNodes();
	int NodeNum();
	int numberDigits();
	//void emptyList();
	//void deleteAllNodes(Node* ptr);
	Node* currentNode(int pos);
	void clearTopZero();
	//void* operator new(size_t size);
	//void operator delete(void* p);
	void freeSpace();
	~LinkedList();

};



#endif