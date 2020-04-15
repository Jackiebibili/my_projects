#include<iostream>
#include<cstdlib>
#include<string>
#include "Node.h"
#include "LinkedList.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Multiplication.h"
using namespace std;

int modifyNodeNums(int num);
void cutString(string& num1, string& num2, LinkedList &head1, LinkedList &head2);
void input(string& num1, string& num2);
void displayList(Node* head);
void menu();
bool digit(string number);
int isNegative(LinkedList head1, LinkedList head2);
void negateNode(LinkedList &head);

int main()
{
    string choice;
    LinkedList obj1, obj2, result;
    string num1, num2;


    do
    {
        menu();
        getline(cin, choice);
        while (!digit(choice))    //input validation
        {
            cout << "Entering a number from the list in order to continue\n";
            getline(cin, choice);
        }

        //if the choice is to exit, exit the program
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4")
        {
            exit(EXIT_SUCCESS);
        }

        //else, continue the calculation
        input(num1, num2);
        cutString(num1, num2, obj1, obj2);

        //pre-display the context
        cout << "The first number is: \t";
        displayList(obj1.getHead());
        cout << endl;
        cout << "The second number is: \t";
        displayList(obj2.getHead());
        cout << endl;
        int flag = isNegative(obj1, obj2);
        switch (stoi(choice))
        {
        case 1: //+
            if (flag == 2)      //==> NUM1 + NUM2
            {
                Add example(obj1, obj2);
                example.addition();
                result = example.getResult();
            }
            else if (flag == 1) //==> NUM1 - NUM2
            {
                negateNode(obj2);
                Subtract example(obj1, obj2);
                example.subtraction();
                result = example.getResult();
            }
            else if (flag == -1)//==> NUM2 - NUM1
            {
                negateNode(obj1);
                Subtract example(obj2, obj1);
                example.subtraction();
                result = example.getResult();
            }
            else                //==> -(NUM1 + NUM2)
            {
                negateNode(obj1);
                negateNode(obj2);
                Add example(obj1, obj2);
                example.addition();
                result = example.getResult();
                cout << "-";
                //or negate the result alone
            }
            //END ADDITION
            break;
        case 2: //-
            if (flag == 2)      //==> NUM1 - NUM2
            {
                Subtract example(obj1, obj2);
                example.subtraction();
                result = example.getResult();
            }
            else if (flag == 1) //==> NUM1 - (-NUM2)
            {
                negateNode(obj2);
                Add example(obj1, obj2);
                example.addition();
                result = example.getResult();
            }
            else if (flag == -1)//==> -NUM1 - NUM2 == -(NUM1 + NUM2)
            {
                
                negateNode(obj1);
                Add example(obj1, obj2);
                result = example.getResult();
                cout << "-";
                //or negate the result alone
            }
            else                //==> -NUM1 - (-NUM2) == NUM2 - NUM1
            {
                negateNode(obj1);
                negateNode(obj2);
                Subtract example(obj2, obj1);
                example.subtraction();
                result = example.getResult();
            }
            //END SUBTRACTION
            break;
        case 3: //*
            if (flag == 2)      //==> NUM1 * NUM2
            {
                Multiply example(obj1, obj2);
                example.multiplication();
                result = example.getResult();
            }
            else if (flag == 1) //==> - (NUM1 * NUM2)
            {
                negateNode(obj2);
                Multiply example(obj1, obj2);
                example.multiplication();
                result = example.getResult();
                cout << "-";
                //or negate the result alone
            }
            else if (flag == -1)//==> - (NUM1 * NUM2)
            {
                negateNode(obj1);
                Multiply example(obj1, obj2);
                example.multiplication();
                result = example.getResult();
                cout << "-";
                //or negate the result alone
            }
            else                //==> NUM1 * NUM2
            {
                negateNode(obj1);
                negateNode(obj2);
                Multiply example(obj1, obj2);
                result = example.getResult();
                example.multiplication();
            }
            //END MULTIPLICATION
            break;
            /*
        case 4: //division
            size = division(head1, head2, head3, m, n, totalNode);
            break;
            */
        }

        if (choice != "4")
        {
            //display the result
            displayList(result.getHead());
            cout << endl;

        }

    } while (choice >= "1" && choice <= "4");

    return 0;

    //displayList((example.getResult()).getHead());
}


void displayList(Node* head)
{
    if (head->getNext() != nullptr)
    {
        displayList(head->getNext());
        if (head->getNum() >= 0 && head->getNum() < 10)
            cout << "00" << head->getNum();
        else if (head->getNum() > 10 && head->getNum() < 100)
            cout << "0" << head->getNum();
        else
            cout << head->getNum();
    }
    else
    {
        if (head->getNum() != 0)
            cout << head->getNum();
    }
}


void input(string& num1, string& num2) 
{
    cout << "Enter two overflowed number\n";
    getline(cin, num1);
    getline(cin, num2);
}


int modifyNodeNums(int num)
{
    if (num % 3 == 0)
    {
        return num / 3;
    }
    else
    {
        return num / 3 + 1;
    }
}


void cutString(string& num1, string& num2, LinkedList &head1, LinkedList &head2)
{
    int length1 = static_cast<int>(num1.length());
    int length2 = static_cast<int>(num2.length());
    int nodeForNum1, nodeForNum2;
    if (num1[0] == '-')
        nodeForNum1 = modifyNodeNums(length1 - 1);
    else
        nodeForNum1 = modifyNodeNums(length1);
    if (num2[0] == '-')
        nodeForNum2 = modifyNodeNums(length2 - 1);
    else
        nodeForNum2 = modifyNodeNums(length2);

    cout << "The first number is splited into " << nodeForNum1 << " nodes" << endl;
    cout << "The second number is splited into " << nodeForNum2 << " nodes" << endl;

    //Node* ptr = head1;
    int i, j = 0;
    if (length1 <= 4 && num1[0] == '-')
    {
        head1.addNode(stoi(num1.substr(0, length1)), 0);
    }
    else
    {
        for (i = length1 - 3; i >= 0; i = i - 3) {
            //cout << num1.substr(i, 3) << endl;
            head1.addNode(stoi(num1.substr(i, 3)), j);
            j++;
            if ((i == 4 && num1[0] == '-') || i < 3)
                break;
        }
        if (i != 0)
            head1.addNode(stoi(num1.substr(0, i)), j);
    }

    //ptr = head2;
    j = 0;
    if (length2 <= 4 && num2[0] == '-')
    {
        head2.addNode(stoi(num2.substr(0, length2)), 0);
    }
    else
    {
        for (i = length2 - 3; i >= 0; i = i - 3) {
            //cout << num1.substr(i, 3) << endl;
            head2.addNode(stoi(num2.substr(i, 3)), j);
            j++;
            if ((i == 4 && num2[0] == '-') || i < 3)
                break;
        }
        if (i != 0)
            head2.addNode(stoi(num2.substr(0, i)), j);
    }
}


void menu() 
{
    cout << "Select from menu" << endl
        << "1. addition" << endl
        << "2. subtruction" << endl
        << "3. multiplication" << endl
        << "4. division " << endl;
    cout << "Or enter any other key to exit\n";
}


bool digit(string number)
{
    if (number == "")
        return false;
    if (number.length() != 1)
        return false;
    if (!isdigit(number[0]))
        return false;
    return true;
}


int isNegative(LinkedList head1, LinkedList head2)
{
    if (head1.getListValue(head1.getNodeNum() - 1) > 0 && head2.getListValue(head2.getNodeNum() - 1) > 0)
    {
        return 2;   //2 numbers are all positive
    }
    else if (head1.getListValue(head1.getNodeNum() - 1) > 0 && head2.getListValue(head2.getNodeNum() - 1) < 0)
    {
        return 1;   //the first number is positive and the other is negative
    }
    else if (head1.getListValue(head1.getNodeNum() - 1) < 0 && head2.getListValue(head2.getNodeNum() - 1) > 0)
    {
        return -1;  //the second number is positive and the other is negative
    }
    else
    {
        return -2;  //2 numbers are all negative
    }
}


void negateNode(LinkedList &head)
{
    head.setValue(head.getNodeNum() - 1, -head.getListValue(head.getNodeNum() - 1));
}

