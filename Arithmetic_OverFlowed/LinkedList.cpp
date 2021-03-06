#include "LinkedList.h"
#include "Node.h"
#include<iostream>
#include<cstdlib>

LinkedList::LinkedList()
{
    head = nullptr;
    numDigits = 0;
    numNodes = 1;
}


LinkedList::LinkedList(Node* ptr)
{
    head = ptr;
    numNodes = NodeNum();
    numDigits = numberDigits();
}


LinkedList::LinkedList(const LinkedList& h)
{
    
    initializeResult(h.head, h.numNodes);
    numNodes = NodeNum();
    numDigits = numberDigits();
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


LinkedList LinkedList::operator=(const LinkedList& right)
{
    if (this != &right)
    {
        //delete all pre-existing nodes
        freeSpace();
        head = nullptr;
        initializeResult(right.getHead(), right.getNodeNum());
        numNodes = right.getNodeNum();
        numDigits = right.getNumDigits();
    }
    return *this;
}


bool LinkedList::operator>=(const LinkedList& right) const
{
    if (numNodes > right.numNodes)
    {
        return true;
    }
    else if (numNodes < right.numNodes)
    {
        return false;
    }
    else
    {
        //if they are equal
        int i;
        //check every node(3 digits)
        for (i = numNodes - 1; i >= 0; i--)
        {
            if (this->getListValue(i) > right.getListValue(i))
            {
                return true;
            }
            else if (this->getListValue(i) < right.getListValue(i))
            {
                return false;
            }
        }
        return true;
    }
}



void LinkedList::addNode(int num, int pos)
{
    Node* A = new Node(pos, num), * ptr = head;
    A->setNext(nullptr);
    if (head == nullptr)
    {
        head = A;
    }
    else
    {
        while (ptr->getNext() != nullptr) {
            ptr = ptr->getNext();
        }
        ptr->setNext(A);
    }
    numNodes = NodeNum();
    numDigits = numberDigits();
}


int LinkedList::getListValue(int pos) const
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


Node* LinkedList::getHead() const
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
    numNodes = NodeNum();
    numDigits = numberDigits();
}


//initalize the result linked list with 0's
void LinkedList::initializeResult(int totalNode)
{
    int i;
    freeSpace();
    head = nullptr;
    for (i = 0; i < totalNode; i++)
    {
        addNode(0, i);
    }
}

//increment by one-digit long value, already have 0 in place
//it's not recursively carrying
void LinkedList::incrementValue(int pos, int val)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->getPos() != pos)
    {
        ptr = ptr->getNext();
    }
    if(ptr)
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


//this function obtains the number of upmost digits (either 3, 2, or 1)
int LinkedList::getUpmostNodeDigitNum() const
{
    if (getListValue(numNodes - 1) < 10)
    {
        return 1;
    }
    else if (getListValue(numNodes - 1) < 100)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}





int LinkedList::getNodeNum() const
{
    return numNodes;
}


void LinkedList::modifyNumberDigits()
{
    numDigits = numberDigits();
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

/*
void LinkedList::emptyList()
{
    Node* ptr = head;
    if (!head)
    {
        if(!head->getNext())
            delete head;
    }
    else
    {
        deleteAllNodes(ptr);
        head = nullptr;
    }

    numNodes = NodeNum();
    numDigits = numberDigits();
}


void LinkedList::deleteAllNodes(Node* ptr)
{
    if (ptr->getNext() && (ptr->getNext())->getNext())
    {
        ptr= ptr->getNext();
        deleteAllNodes(ptr);
        delete ptr;
        //ptr = nullptr;
    }
    else
    {
        delete ptr;
        //ptr = nullptr;
    }
}
*/
/*
void *LinkedList::operator new(size_t size)
{
    void* p = malloc(size);
    return p;
}


void LinkedList::operator delete(void* p)
{
    free(p);
}
*/

Node* LinkedList::currentNode(int pos)
{
    Node* ptr = head;
    while (ptr != nullptr && ptr->getPos() != pos)
    {
        ptr = ptr->getNext();
    }
    return ptr;
}


void LinkedList::clearTopZero()
{
    Node* temp = currentNode(numNodes - 1);
    while (temp != nullptr && temp->getNum() == 0)
    {
        temp = currentNode(numNodes - 2);
        if (temp != nullptr)
        {
            delete temp->getNext();
            temp->setNext(nullptr);
            numNodes--;
        }
    }
}


void LinkedList::freeSpace()
{
    while (head)
    {
        Node* temp = head->getNext();
        delete head;
        head = temp;
    }
}




LinkedList::~LinkedList()
{
    freeSpace();
}

