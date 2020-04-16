#include"Addition.h"
#include"Node.h"
#include"LinkedList.h"
#include<iostream>
using namespace std;

void Add::addition()
{
    int m = head1.getNodeNum();
    int n = head2.getNodeNum();
    cout << "Performing addition\n";
    cout << "The result is: \t\t";
    int totalNode = nodeNumAddition(m, n);
    head3 = head1;
    overflowAddition(n);
    head3.clearTopZero();
}


Add::Add(Add& obj)
{
    head1 = obj.head1;
    head2 = obj.head2;
    head3 = obj.head3;
}


int Add::nodeNumAddition(int m, int n)
{
    if (m > n)
    {
        return m + 1;
    }
    else
    {
        return n + 1;
    }
}


void Add::overflowAddition(int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        sequentialFlow(head2.getListValue(i), i);
    }
}


void Add::sequentialFlow(const int val, int pos)
{
    //in case of carrying
    int sum = head3.getListValue(pos) + val;
    if (sum > 999)
    {
        sequentialFlow(sum / 1000, pos + 1);
        head3.setValue(pos, sum % 1000);
    }
    //if the addition does not exceed 3-digit size (<1000)
    else
    {
        head3.setValue(pos, sum);
    }
}

void Add::plus(const int val, int pos)
{
    sequentialFlow(val, pos);
}

