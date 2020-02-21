#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<memory>
#include<string>
#include<vector>
using namespace std;

//function prototypes
void transposeOperation(double** matrix, int rows, int cols);
shared_ptr<shared_ptr<double[]>[]> inputMatrix(int& rows, int& cols);


int main()
{
	int row, col;
	int i, j;
	shared_ptr<shared_ptr<double[]>[]> ptr;
	ptr = inputMatrix(row, col);


	//display the detail
	//display the relationship of A = LU
	cout << endl;
	cout << fixed << showpoint << setprecision(3);
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (ptr[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			else
				cout << setw(7) << ptr[i][j] << " ";
		}
		cout << endl;
	}
}


shared_ptr<shared_ptr<double[]>[]> inputMatrix(int& rows, int& cols)
{
	cout << "Enter a square matrix:\n";
	cout << "Row by row and separate each entry by a space\n";
	string line;
	vector<double>firstRow;
	int i = 0, j = 0;
	getline(cin, line);
	while (line != "")
	{
		firstRow.push_back(stod(line.substr(0, line.find(' '))));
		line.erase(0, line.find(' ') + 1);
		if (line.find(' ') == -1)
		{
			firstRow.push_back(stod(line));
			line = "";
		}
		j++;
	}
	cols = rows = j;
	//dynamically allocate memory
	shared_ptr<shared_ptr<double[]>[]> matrix (new shared_ptr<double[]> [cols]);
	for (i = 0; i < cols; i++)
	{
		shared_ptr<double[]> matrix(new double[cols]);
	}

	//copy the first row to the 2D array
	for (i = 0; i < cols; i++)
	{
		matrix[0][i] = firstRow[i];
	}

	//the rest of the rows
	i = 1;
	while (getline(cin, line))
	{
		if (line == "")
			break;
		for (j = 0; j < cols && line != ""; j++)
		{
			matrix[i][j] = stod(line.substr(0, line.find(' ')));
			line.erase(0, line.find(' ') + 1);
		}
		i++;
	}
	cout << "End of reading a matrix\n";
	
	return matrix;
}



void transposeOperation(double** matrix, int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if(i != j)
				swap(matrix[i][j], matrix[j][i]);
		}
	}
}