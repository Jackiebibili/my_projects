#include<iostream>
#include<cstdlib>
#include "Node.h"
#include "LinkedList.h"
#include "Addition.h"
#include "Multiplication.h"
using namespace std;


void Multiply::multiplication()
{
    int m = obj.getHead1_NodeNum();
    int n = obj.getHead2_NodeNum();
    cout << "Performing multiplication\n";
    cout << "The result is: \t\t";
    int totalNode = nodeNumMulti(m, n);
    overflowMulti(m, n);
    head = obj.getResult();
    head.clearTopZero();
}


void Multiply::overflowMulti(int m, int n)
{
    int i, j, val;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            val = obj.getHead1_ListValue(i) * obj.getHead2_ListValue(j);
            obj.plus(val, i + j);
        }
    }
}


int Multiply::nodeNumMulti(int m, int n)
{
    return m + n;
}

