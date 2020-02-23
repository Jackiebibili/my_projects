#include<iostream>
#include<cstdlib>
#include<iomanip>
#include<memory>
#include<string>
#include<vector>
#include<cmath>
using namespace std;

//global constants
const int PRECISION = 3;	//accuracy of the decimal pts for each entries

//function prototypes
void transposeOperation(shared_ptr<shared_ptr<double[]>[]> matrix, int rows, int cols);
shared_ptr<shared_ptr<double[]>[]> inputMatrix(int& rows, int& cols);
void displayMatrix(shared_ptr<shared_ptr<double[]>[]> ptr, int row, int col);
void displayElem(double entry, int pts = PRECISION);

int main()
{
	int row, col;
	//int i, j;
	shared_ptr<shared_ptr<double[]>[]> ptr;

	//get the user's input
	ptr = inputMatrix(row, col);

	//display the user's input matrix
	displayMatrix(ptr, row, col);

	//calculate the transpose of the matrix
	transposeOperation(ptr, row, col);

	//display the transpose of the matrix
	displayMatrix(ptr, row, col);

	return 0;
}

void displayMatrix(shared_ptr<shared_ptr<double[]>[]> ptr, int row, int col)
{
	//display the detailed entries of a matrix
	int i, j, k;
	cout << endl;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			displayElem(ptr[i][j]);
		}
		cout << endl;
		if (i < row - 1)
		{
			for (k = 0; k < row; k++)
				cout << "--------";
		}
		cout << endl;
	}
}


void displayElem(double entry, int pts)
{
	cout << fixed << showpoint << setprecision(pts);
	if (entry - static_cast<int>(entry) == 0.0)
		cout << setw(6) << static_cast<int>(entry) << " ";
	else
	{
		int i = 1;
		while (i < pts)	//entry * 10 ^n folds
		{			
			if ((entry * pow(10, i)) - static_cast<int>(entry * pow(10, i)) == 0.0)
			{
				cout << setprecision(i);
				cout << setw(6) << entry << " ";
				cout << setprecision(pts);
				break;
			}
			i++;
		}
		if(i == pts)
			cout << setw(6) << entry << " "; //default 3 decimal points

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
			j++;
		}
		j++;
	}
	cols = rows = j;


	//dynamically allocate memory
	shared_ptr<shared_ptr<double[]>[]> matrix (new shared_ptr<double[]> [cols]);
	shared_ptr<double[]> m_row (new double[cols]); //assist for each row's input

	//copy the first row to the 2D array  ||row = 0
	//m_row = make_shared<double[]>(cols);
	for (i = 0; i < cols; i++)
	{
		//shared_ptr<double[]> matrix(new double[cols]);
		//matrix[i].get() = make_shared<double[]>[cols];
		m_row[i] = firstRow[i];
	}
	matrix[0] = move(m_row);

	//the rest of the rows
	i = 1;
	m_row.reset(new double[cols]);
	//m_row = make_shared<double[]>(cols);
	while (i < cols && getline(cin, line))
	{
		if (line == "")
			break;
		for (j = 0; j < cols && line != ""; j++)
		{
			m_row[j] = stod(line.substr(0, line.find(' ')));
			line.erase(0, line.find(' ') + 1);
		}
		matrix[i] = move(m_row);
		m_row.reset(new double[cols]);
		i++;
	}
	cout << "Finish reading the matrix\n";
	cout << "It's a " << rows << "x" << cols << " matrix\n";
	return matrix;
}



void transposeOperation(shared_ptr<shared_ptr<double[]>[]> matrix, int rows, int cols)
{
	int i, j, k = 1;
	for (i = 0; i < rows; i++)
	{
		for (j = k; j < cols; j++)
		{
			swap(matrix[i][j], matrix[j][i]);
		}
		k++;
	}
}