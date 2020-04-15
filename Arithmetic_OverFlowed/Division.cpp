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
    int totalDec, totalDecNode = 0, integerSize = 0, pos = 0, place = 3;
    LinkedList aug(nullptr), aux(nullptr);
    cout << "Result in how many decimal places: ";
    cin >> totalDec;
    cin.ignore();
    ////////////////////////////////
    //need a validation
    ////////////////////////////////
    decimal_length = totalDec;
    cout << "Performing division\n";
    cout << "The result is: \t\t";
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
        multi.multiplication();
        aug = multi.getResult();
        //set the position
        pos = totalDec / 3;
        place = 3 - (totalDec % 3);
    }

    /////////////////////////////////////////////
    integerSize = divisionFor(aug, pos, place);
    /////////////////////////////////////////////
    decimal_point = integerSize;
}


//function call:     int digit = sequentialDivi(firstNum, head2, r, getNodeNum(firstNum), n, first3List1, first2List2, ceiling);
int Divide::sequentialDivi(LinkedList head, LinkedList &r, int val1, int val2, int val2Ceil)
{
    LinkedList testHead1 (nullptr), testHead2 (nullptr);
    int lower = val1 / val2Ceil;
    int upper = val1 / val2;
    if (lower != upper)
    {
        for (int i = lower; i < upper; i++)
        {
            if (!compareValue(head, testHead1, testHead2, i, i + 1))
            {
                Subtract temp(head, testHead1);
                temp.subtraction();
                r = temp.getResult();
                return i;
            }
        }
        Subtract temp(head, testHead2);
        temp.subtraction();
        r = temp.getResult();
        return upper;
    }
    else
    {
        //get nothing from the compareValue function; instead, calculate the remainder
        LinkedList testHead(lower, 0);
        Multiply multi(head2, testHead);
        multi.multiplication();
        Subtract temp(head, multi.getResult());
        temp.subtraction();
        r = temp.getResult();
        return lower;
    }
}

//function call: compareValue(head1, head2, testHead1, testHead2, m, n, i, i + 1)
bool Divide::compareValue(LinkedList head, LinkedList &testHead1, LinkedList &testHead2, int lower, int upper)
{
    LinkedList tempLow(lower, 0), tempUp(upper, 0);
    Multiply multiLow(head2, tempLow), multiUp(head2, tempUp);
    multiLow.multiplication();
    multiUp.multiplication();
    testHead1 = multiLow.getResult();
    testHead2 = multiUp.getResult();
    if (head >= testHead2 && head >= testHead2)
    {
        //subtraction(head1, testHead2, r, m, getNodeNum(testHead2), totalNodeR);
        return true;    //have the ceiling value;
    }
    else
    {
        //subtraction(head1, testHead1, r, m, getNodeNum(testHead1), totalNodeR);
        return false;   //the ceiling value exceeds NUM1, therefore have the floor value
    }
}


void Divide::stepNextNode(int& pos, int& place)
{
    if (place >= 3)
    {
        pos--;
        place = 1;
    }
    else
    {
        place++;
    }
}


int Divide::getNextDigit(LinkedList head, int pos, int sub)
{
    int i, num;
    num = head.getListValue(pos);
    for (i = 0; i < sub; i++)
    {
        num %= static_cast<int>(pow(10, 3 - i));
    }
    return num / static_cast<int>(pow(10, 3 - i));;
}


//original parameter list: (Node*& head1, Node*& head2, Node*& head3, Node*& origHead1, int n, int loc, int place, int k)
//                          aug / head2 = head3; aug might be head1 or augmented form of head1
//                          m for aug and n for head2
int Divide::divisionFor(LinkedList aug, int loc, int place)
{
    int i, totalNode = 0;
    int ceiling = 0, a = 0;
    int sub, next, offset;
    int first2List2;
    bool flag = true;
    LinkedList aux10(10, 0), r(nullptr), R(nullptr);

    LinkedList firstNum = getFirstDiviNum(aug, offset, sub);
    offset = aug.getNodeNum() - offset - 1;
    if (offset == 0 && sub == 3)
        flag = false;
    //int currNode = firstNum.getNodeNum();
    int first3List1 = getFirstThreeDigit(firstNum);
    if (head2.getNumDigits() != 1)
        first2List2 = getFirstTwoDigit(head2, ceiling);
    else
    {
        first2List2 = (head2.getHead()->getNum()) * 10;
        ceiling = first2List2;
    }
    int digit = sequentialDivi(firstNum, r, first3List1, first2List2, ceiling);
    a++;
    head3.addNode(digit, k);
    k++;
    Multiply multi(r, aux10);
    multi.multiplication();
    R = multi.getResult();
    stepNextNode(offset, sub);
    next = getNextDigit(aug, offset, sub);
    R.incrementValue(0, next);

    if (!flag)
        return 1;

    while (offset != 0 || sub != 3)
    {
        if (offset > loc || offset == loc && sub <= place)
            a++;
        if (R >= head2)
        {
            //have enough number to be divided
            first3List1 = getFirstThreeDigit(R);
            digit = sequentialDivi(R, r, first3List1, first2List2, ceiling);
            head3.addNode(digit, k);
            k++;
            Multiply multi(r, aux10);
            multi.multiplication();
            R = multi.getResult();
            stepNextNode(offset, sub);
            next = getNextDigit(aug, offset, sub);
            R.incrementValue(0, next);
        }
        else
        {
            //have not enough number to be divided, commit a borrowing
            head3.addNode(0, k);
            k++;
            Multiply multi(R, aux10);
            multi.multiplication();
            R = multi.getResult();
            stepNextNode(offset, sub);
            next = getNextDigit(head1, offset, sub);
            R.incrementValue(0, next);
        }
    }

    //for the last digit calculation
    if (R >= head2)
    {
        //have enough number to be divided
        first3List1 = getFirstThreeDigit(R);
        digit = sequentialDivi(R, r, first3List1, first2List2, ceiling);
        head3.addNode(digit, k);
        k++;
        R = r;
    }
    else
    {
        head3.addNode(0, k);
        k++;
    }

    return a;
}



LinkedList Divide::getFirstDiviNum(LinkedList aug, int& offsetNode, int& place)
{
    LinkedList temp(nullptr), h(nullptr), aux(nullptr);
    int pos;
    int list1NodeLow;
    int secondary = (head2.getNodeNum() - 1) * 3 + head2.getUpmostNodeDigitNum() - aug.getUpmostNodeDigitNum();
    if (head1 >= head2)
    {
        int list1High = aug.getListValue(aug.getNodeNum() - 1);
        list1High = getUpmostDigit(list1High);
        int list2High = head2.getListValue(head2.getNodeNum() - 1);
        list2High = getUpmostDigit(list2High);
        if (list1High < list2High)  //the part of list1 with the same length of list2 cannot divide list2
        {
            secondary++;    //move to the next digit on the right
        }
    }
    offsetNode = secondary / 3;
    place = secondary % 3;
    if (place != 0)
    {
        offsetNode++;
        pos = aug.getNodeNum() - 1 - offsetNode;
        list1NodeLow = aug.getListValue(pos);
        list1NodeLow = modifyLowerBound(list1NodeLow, secondary);
    }
    else
    {
        place = 3;
        pos = aug.getNodeNum() - 1 - offsetNode;
        list1NodeLow = aug.getListValue(pos);
        list1NodeLow = modifyLowerBound(list1NodeLow, secondary);
    }
    aux = newNodeInt(place);
    LinkedList lowNode(list1NodeLow, 0);
    h = cutNodes(aug, pos + 1);
    Multiply multi(h, aux);
    multi.multiplication();
    Add sum(multi.getResult() , lowNode);
    sum.addition();
    temp = sum.getResult();
    temp.clearTopZero();
    return temp;
}


//    function call: int first3List1 = getFirstThreeDigit(firstNum, currNode, numberDigits(head2));
int Divide::getFirstThreeDigit(LinkedList head)
{
    if (head.getNumDigits() > head2.getNumDigits())
    {
        if (head.getUpmostNodeDigitNum() == 1)
        {
            return head.getListValue(head.getNodeNum() - 1) * 100 + head.getListValue(head.getNodeNum() - 2) / 10;
        }
        else if (head.getUpmostNodeDigitNum() == 2)
        {
            return head.getListValue(head.getNodeNum() - 1) * 10 + head.getListValue(head.getNodeNum() - 2) / 100;
        }
        else
        {
            return head.getListValue(head.getNodeNum() - 1);
        }
    }

    if (head.getUpmostNodeDigitNum() == 1)
    {
        //place = 1;
        //pos = m - 2;
        return head.getListValue(head.getNodeNum() - 1) * 10 + head.getListValue(head.getNodeNum() - 2) / 100;
    }
    else if (head.getUpmostNodeDigitNum() == 2)
    {
        //place = 3;
        //pos = m - 2;
        return head.getListValue(head.getNodeNum() - 1);
    }
    else
    {
        //place = 2;
        //pos = m - 1;
        return head.getListValue(head.getNodeNum() - 1) / 10;
    }
}

//function call:         first2List2 = getFirstTwoDigit(head2, n, ceiling);

int Divide::getFirstTwoDigit(LinkedList head, int& ceiling)
{
    int num;
    if (head.getUpmostNodeDigitNum() == 1)
    {
        ceiling = num = head.getListValue(head.getNodeNum() - 1) * 10 + head.getListValue(head.getNodeNum() - 2) / 100;
        if (!isfloor(head, head.getNodeNum() - 2, 100))
            ceiling++;
        return num;
    }
    else if (head.getUpmostNodeDigitNum() == 2)
    {
        ceiling = num = head.getListValue(head.getNodeNum() - 1);
        if (!isfloor(head, head.getNodeNum() - 2))
            ceiling++;
        return num;
    }
    else
    {
        ceiling = num = head.getListValue(head.getNodeNum() - 1) / 10;
        if (!isfloor(head, head.getNodeNum() - 2))
            ceiling++;
        return num;
    }
}


bool Divide::isfloor(LinkedList head, int pos, int look)
{
    int i;
    if (head.getListValue(pos) % look != 0)
        return false;
    for (i = pos - 1; i >= 0; i--)
    {
        if (head.getListValue(i) != 0)
            return false;
    }
    return true;
}


bool Divide::isfloor(LinkedList head, int pos)
{
    int i;
    for (i = pos; i >= 0; i--)
    {
        if (head.getListValue(i) != 0)
            return false;
    }
    return true;
}


int Divide::getUpmostDigit(int num)
{
    if (num >= 100)
        return num / 100;
    else if (num >= 10)
        return num / 10;
    else if (num >= 1)
        return num;
    else
        return 0;
}


int Divide::modifyLowerBound(int num, int secondary)
{
    if (secondary % 3 == 1)
    {
        return num / 100;
    }
    else if (secondary % 3 == 2)
    {
        return num / 10;
    }
    else
    {
        return num;
    }

}


LinkedList Divide::newNodeInt(int place)
{
    LinkedList temp(nullptr);
    if (place != 0)
        temp.addNode(pow(10, place), 0);
    else
    {
        temp.addNode(0, 0);
        temp.addNode(1, 1);
    }
    return temp;
}


LinkedList Divide::cutNodes(LinkedList head, int pos)
{
    int i, j;
    LinkedList temp(nullptr);
    j = pos;
    for (i = 0; i < head.getNodeNum() - pos && j < head.getNodeNum(); i++, j++)
    {
        temp.addNode(head.getListValue(j), i);
    }
    return temp;
}
