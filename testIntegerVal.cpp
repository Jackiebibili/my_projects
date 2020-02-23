#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<memory>
#include<string>
#include<vector>
using namespace std;

int main()
{
   double num;
   cout << "Enter a num\n";
   cin >> num;
   if(num == 0)
      cout << static_cast<int>(num) << endl;
   cout << abs(num) << endl;

}
