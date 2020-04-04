#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<string>

using namespace std;

void eliminationAbovePivot(int auguCols, double** matrix_A, int cycle);
int eliminationMatrix_A(int rows, int cols, int auguCols, double** matrix_A, double* pivot, double* tempRow, int cycle);
void constantMulti(int auguCols, double** matrix_A, int cycle, double* pivot);
void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C);
int integerIdentify(int num);

int main()
{
	int rows_A, cols_A, rows_B, cols_B;
	int i, j;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> rows_A >> cols_A;
	cout << "Enter the row #m and col #n of a matrix B\n";
	cin >> rows_B >> cols_B;

	//validation
	if (cols_A != rows_B)
	{
		cout << "Column of A must be the same as row of B\n";
		exit(0);
	}

	double** matrix_A = nullptr;
	matrix_A = new double* [rows_A];
	double** matrix_B = nullptr;
	matrix_B = new double* [rows_B];
	double** matrix_C = nullptr;
	matrix_C = new double* [rows_A];

	for (i = 0; i < rows_A; i++)
	{
		matrix_A[i] = new double[cols_A];
		//initialization needed
	}
	for (i = 0; i < rows_B; i++)
	{
		matrix_B[i] = new double[cols_B];
		//initialization needed
	}
	for (i = 0; i < rows_A; i++)
	{
		matrix_C[i] = new double[cols_B];
		//initialization needed
	}

	cout << "Enter the matrix A by entering each row at a time\n";
	cout << "separate each row's input by an newline\n";
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_A; j++)
		{
			cin >> matrix_A[i][j];
		}
		if (i != rows_A - 1)
		{
			cout << "--------\n";
		}
	}

	cout << "\nEnter the matrix B by entering each row at a time\n";
	cout << "separate each row's input by an newline\n";
	for (i = 0; i < rows_B; i++)
	{
		for (j = 0; j < cols_B; j++)
		{
			cin >> matrix_B[i][j];
		}
		if (i != rows_B - 1)
		{
			cout << "--------\n";
		}
	}
	//initialization of C
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_B; j++)
		{
			matrix_C[i][j] = 0.0;
		}
	}

	matrixMulti(rows_A, cols_B, cols_A, matrix_A, matrix_B, matrix_C);

	cout << "The multiplication of AB is: \n";
	cout << fixed << showpoint << setprecision(3);
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_B; j++)
		{
			if (matrix_C[i][j] == 0.0)
				cout << setw(7) << "0" << " | ";
			else
				cout << setw(7) << matrix_C[i][j] << " | ";
		}
		if (i != rows_A - 1)
		{
			cout << endl;
			for (int z = 0; z < cols_B; z++)
			{
				cout << "----------";

			}
			cout << endl;
		}
	}
	cout << endl << endl;
	system("pause");
	return 0;
	
}

//have issue finding fraction less than 1, use causiously
int integerIdentify(int num)
{
	string str = to_string(num);
	int pos = str.find(".");
	str = str.substr(pos + 1);
	if (str == "")
		return 1;
	for (int b = 0; b < str.length(); b++)
	{
		if (str[b] != '0')
			return -1;
	}
	return 1;
}

void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C)
{
	int i, j, k;
	for (i = 0; i < rows; i++)
	{
		for (k = 0; k < cols; k++)
		{
			for (j = 0; j < commonCR; j++)
			{
				matrix_C[i][k] += matrix_A[i][j] * matrix_B[j][k];
			}
		}
	}
}


void constantMulti(int auguCols, double** matrix_A, int cycle, double* pivot)
{
	int i, j;
	for (i = 0; i < cycle; i++)
	{
		for (j = 0; j < auguCols; j++)
		{
			matrix_A[i][j] /= pivot[i];
		}
	}
}

void eliminationAbovePivot(int auguCols, double** matrix_A, int cycle)
{
	int i, j, k;
	double multiplier = 0.0;
	double p = 0.0;
	for(i = 1; i <= cycle; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			p = matrix_A[i][i];
			multiplier = matrix_A[j][i];
			for (k = 0; k < auguCols; k++)
			{
				matrix_A[j][k] -= (multiplier / p) * matrix_A[i][k];
			}

		}
	}
}



int eliminationMatrix_A(int rows, int cols, int auguCols, double **matrix_A, double* pivot, double* tempRow, int cycle)
{
	//process to find A-1
	//Goal: [A I] to get [I A-1]
	static int i, j;
	int a;
	tempRow = new double[auguCols];
	for (a = 0; a < auguCols; a++)
		tempRow[a] = 0.0;
	int k;
	int copyRowOff = 0;
	double multiplier = 0.0;
	int rowOperate = 1;
	if (cycle == 0)
	{
		pivot[i] = matrix_A[i][i];
		if (pivot[i] == 0.0)
		{
			cout << "Lack at least one non-zero pivot\n";
			cout << "A is not invertible\n";
			return -1;
		}
		else
			return 1;
	}
	while (rowOperate <= cycle)
	{
		while (matrix_A[i][j] == 0.0)
		{
			//swap the row with the one comes right after
			if (copyRowOff >= rows - 1)		//validation
			{
				cout << "Lack at least one non-zero pivot\n";
				cout << "A is not invertible\n";
				return -1;
			}
			for (k = 0; k < auguCols; k++)
			{
				tempRow[k] = matrix_A[i + 1 + copyRowOff][k];
			}
			for (k = 0; k < auguCols; k++)
			{
				matrix_A[i + 1 + copyRowOff][k] = matrix_A[i][k];
			}
			for (k = 0; k < auguCols; k++)
			{
				matrix_A[i][k] = tempRow[k];
			}
			copyRowOff++;
		}
		copyRowOff = 0;
		pivot[i] = matrix_A[i][j];
		if (pivot[i] == 0.0)
		{
			cout << "Lack at least one non-zero pivot\n";
			cout << "A is not invertible\n";
			return -1;
		}
		multiplier = matrix_A[i + rowOperate][j];
		for (k = 0; k < auguCols; k++)
		{
			matrix_A[i + rowOperate][k] -= (multiplier / pivot[i]) * matrix_A[i][k];
		}
		rowOperate++;

	}
	i++;
	j++;
	delete[] tempRow;
	tempRow = nullptr;
	return 1;
}


//print out the 2d array(every entry of it)
/*
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			cout << matrix_A[i][j] << "  ";

		}
		if (i != rows - 1)
		{
			cout << "\n--------\n";
		}
	}

*/
