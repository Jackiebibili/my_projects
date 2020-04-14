#include "Node.h"
#include "LinkedList.h"
#include "Subtraction.h"
#include<iostream>
using namespace std;

void Subtract::subtraction()
{
    int m = head1.getNodeNum();
    int n = head2.getNodeNum();
    cout << "Performing subtraction\n";
    cout << "The result is: \t\t";
    int totalNode = nodeNumSub(m, n);
    if (!numCompare())
    {
        LinkedList temp(head1);
        head1 = head2;
        head2 = temp;
        head3 = head1;
        underflowSubtract(n);
        cout << "-";
    }
    else
    {
        underflowSubtract(n);
    }
    //a - b >= 0, do normal calculation
}


void Subtract::underflowSubtract(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        sequentialUnderflow(head2.getListValue(i), i);
    }
}


void Subtract::sequentialUnderflow(const int val, int pos)
{
    int sub = head3.getListValue(pos) - val;
    //in case of borrowing
    if (sub < 0)
    {
        sequentialUnderflow(1, pos + 1);
        head3.setValue(pos, 1000 + sub);
    }
    else
    {
        head3.setValue(pos, sub);
    }
}


int Subtract::nodeNumSub(int m, int n)
{
    if (m > n)
    {
        return m;
    }
    else
    {
        return n;
    }
}


bool Subtract::numCompare() const
{
    if (head1.getNodeNum()> head2.getNodeNum())
    {
        return true;
    }
    else if (head1.getNodeNum() < head2.getNodeNum())
    {
        return false;
    }
    else
    {
        //if they are equal
        int i;
        //check every node(3 digits)
        for (i = head1.getNodeNum() - 1; i >= 0; i--)
        {
            if (head1.getListValue(i) > head2.getListValue(i))
            {
                return true;
            }
            else if (head1.getListValue(i) < head2.getListValue(i))
            {
                return false;
            }
        }
        return true;
    }
}
