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
	LinkedList(int num, int pos)
	{
		head = new Node(pos, num);
		modifyNumberDigits();
		modifyNumberNodes();
	}
	//copy constructor
	LinkedList(const LinkedList&);
	void initializeResult(Node* head1, int totalNode);
	LinkedList operator=(const LinkedList& right);
	bool operator>=(const LinkedList& right) const;
	void addNode(int num, int pos);
	int getListValue(int pos) const;
	int getNodeNum() const;
	int getNumDigits() const;
	int getUpmostNodeDigitNum() const;
	Node* getHead() const;
	void setValue(int pos, int val);
	void initializeResult(int totalNode);
	void incrementValue(int pos, int val);
	void modifyNumberDigits();
	void modifyNumberNodes();
	int NodeNum();
	int numberDigits();
	Node* currentNode(int pos);
	void clearTopZero();
	//void emptyList();
	//void deleteAllNodes(Node* ptr);
	//void* operator new(size_t size);
	//void operator delete(void* p);
	friend void showList(const LinkedList &start);
	friend void showList(const LinkedList &start, int point);
	void freeSpace();
	~LinkedList();

};



#endif