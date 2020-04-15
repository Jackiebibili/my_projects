#include "Node.h"
#include "LinkedList.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
#include "Division.h"
#include <iostream>
#include <cstdlib>
using namespace std;


void Divide::division()
{
    int totalDec, totalDecNode = 0, integerSize = 0, pos = 0, place = 3, sup = 0;
    LinkedList aug(nullptr), aux(nullptr);
    cout << "Result in how many decimal places: ";
    cin >> totalDec;
    cin.ignore();
    ////////////////////////////////
    //need a validation
    ////////////////////////////////
    decimal_length = totalDec;
    cout << "Performing division\n";
    //do normal division with result >= 1
    //augumented the number if the result contains decimals
    aug = head1;

    if (totalDec != 0)
    {
        aug = nullptr;
        if (totalDec % 3 == 0)
        {
            aux.initializeResult(totalDec / 3 + 1);
            aux.setValue(totalDec / 3, 1);
        }
        else if (totalDec % 3 == 1)
        {
            aux.initializeResult(totalDec / 3 + 1);
            aux.setValue(totalDec / 3, 10);
        }
        else
        {
            aux.initializeResult(totalDec / 3 + 1);
            aux.setValue(totalDec / 3, 100);
        }
        Multiply multi(head1, aux);
        aug = multi.getResult();
        //set the position
        pos = totalDec / 3;
        place = 3 - (totalDec % 3);
    }

    /////////////////////////////////////////////
    integerSize = divisionFor(temp, head2, head3, head1, n, pos, place, sup);
    /////////////////////////////////////////////
    //if (numberDigits(head2) == 1)
    //    integerSize++;
    cout << "The result is: \t\t";
    displayEveryDigit(head3, integerSize);
    cout << endl;

}