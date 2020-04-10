#include "LinkedList.h"
#include "Node.h"
#include<iostream>
#include<cstdlib>


LinkedList::LinkedList()
{
    head = nullptr;
}


LinkedList::LinkedList(Node* ptr)
{
    head = ptr;
}


LinkedList::LinkedList(LinkedList*& h)
{
    initializeResult(h->getHead(), h->getNodeNum());
}


//initialize the result linked list with the first list's content
void LinkedList::initializeResult(Node* head1, int totalNode)
{
    Node* ptr1 = head1;
    initializeResult(totalNode);
    Node* ptr2 = head;
    while (ptr1 != nullptr)
    {
        ptr2->setNum(ptr1->getNum());
        ptr2->setPos(ptr1->getPos());
        ptr2 = ptr2->getNext();
        ptr1 = ptr1->getNext();
    }
}


LinkedList* LinkedList::operator=(LinkedList*& right)
{
    if (this != right)
    {
        //delete all pre-existing nodes
        emptyList();
        numDigits = right->getNumDigits();
        numNodes = right->getNodeNum();
        initializeResult(right->getHead(), right->getNodeNum());
    }
}


void LinkedList::addNode(int num, int pos)
{
    //Node* A = new Node, * ptr = head;
    Node a (pos, num);
    Node* A = &a, * ptr = head;
    A->setNext(nullptr);
    //ptr = head;
    if (head == nullptr)
    {
        head = A;
        return;
    }
    else
    {
        while (ptr->getNext() != nullptr) {
            ptr = ptr->getNext();
        }
        ptr->setNext(A);
    }
}


int LinkedList::getListValue(int pos)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->getPos() != pos)
    {
        ptr = ptr->getNext();
    }
    if (!ptr)
        return -1;
    return ptr->getNum();
}


Node*& LinkedList::getHead()
{
    return head;
}


void LinkedList::setValue(int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->getPos() != pos)
    {
        ptr = ptr->getNext();
    }
    ptr->setNum(val);
}


//initalize the result linked list with 0's
void LinkedList::initializeResult(int totalNode)
{
    int i;
    for (i = 0; i < totalNode; i++)
    {
        addNode(0, i);
    }
}


void LinkedList::incrementValue(int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->getPos() != pos)
    {
        ptr = ptr->getNext();
    }
    ptr->setNum(ptr->getNum() + val);
}


void LinkedList::modifyNumberNodes()
{
    numNodes = NodeNum();
}


int LinkedList::NodeNum()
{
    int i = 0;
    Node* ptr = head;
    while (ptr != nullptr)
    {
        ptr = ptr->getNext();
        i++;
    }
    return i;
}


int LinkedList::getNumDigits() const
{
    return numDigits;
}


int LinkedList::getNodeNum() const
{
    return numNodes;
}


void LinkedList::modifyNumberDigits()
{
    numDigits =  numberDigits();
}


int LinkedList::numberDigits()
{
    int firstNode;
    if (getListValue(numNodes - 1) / 100 != 0)
    {
        firstNode = 3;
    }
    else if (getListValue(numNodes - 1) / 10 != 0)
    {
        firstNode = 2;
    }
    else
    {
        firstNode = 1;
    }
    return firstNode + (numNodes - 1) * 3;

}


void LinkedList::emptyList()
{
    Node* ptr = head;
    deleteAllNodes(ptr);
    head = nullptr;
}


void LinkedList::deleteAllNodes(Node*& ptr)
{
    if (ptr->getNext())
    {
        ptr->setNext(ptr->getNext());
        deleteAllNodes(ptr);
        ptr->setNext(nullptr);
        delete ptr;
    }
    else
    {
        delete ptr;
    }
}


LinkedList::~LinkedList()
{
    emptyList();
}

