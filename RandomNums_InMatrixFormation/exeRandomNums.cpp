#include<iostream>
#include<cstdlib>
#include<fstream>
#include<string>
#include<ctime>
using namespace std;

void randomNums(fstream& file, string filename, int row, int col);

int main()
{
	string name;
	int row, col;
	cout << "Enter the creation name of the output file\n";
	getline(cin, name);
	cout << "Enter the row and column size of the matrix\n";
	cin >> row >> col;
	cin.ignore();
	fstream file(name, ios::out);
	file.close();
	randomNums(file, name, row, col);
}

void randomNums(fstream& file, string filename, int row, int col)
{
	int i, j;
	file.open(filename, ios::out);
	file.clear();
	srand(time(0));
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			file << 10 * (rand() % 10) + 1 * (rand() % 10) + 0.1 * (rand() % 10) + 0.01 * 1 * (rand() % 10) << " ";
		}
		file << endl;
	}
	file.close();
}
