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
    if (!(head1 >= head2))
    {
        //do a swap of head1 and head2
        LinkedList temp(head1);
        head1 = head2;
        head2 = temp;
        head3 = head1;
        underflowSubtract(n);
        cout << "-";
    }
    else
    {
        //a - b >= 0, do normal calculation
        underflowSubtract(n);
    }
    head3.clearTopZero();
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
