/*
This program is to solve a given linear system using
A = LDU factorization and then Lc = b and Ux = c
(forward substitution and backward substitution)
*/

#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<string>
using namespace std;

int tm = 0; //efficiency of the program
int ta = 0;

//global constants
const int PRECISION = 3;	//accuracy of the decimal pts for each entries


void eliminationAbovePivot(int auguCols, double** matrix_A, int cycle);
int eliminationMatrix_A(int rows, int cols, double** matrix_A, double* pivot, double* tempRow, double** matrix_L, int cycle);
void constantMulti(int auguCols, double** matrix_A, int cycle, double* pivot);
void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C);
int integerIdentify(int num);
void forwardSub(double** matrix_L, double* vectorC, double* vectorB, int i); // 0 <= i < n
void backwardSub(double** matrix_A, double* vectorX, double* vectorC, int cols, int i); // 0 <= i < n
void displayMatrix(double** ptr, int row, int col);
void displayMatrix(double* ptr, int row);
void displayMatrixLU(double** ptr1, double** ptr2, int row, int col);
void displayElem(double entry, int pts = PRECISION);


int main()
{
	int rows_A, cols_A;
	int i, j;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> rows_A >> cols_A;

	double** matrix_A = nullptr;
	matrix_A = new double* [rows_A];
	double** matrix_L = nullptr;
	matrix_L = new double* [rows_A];
	double** matrix_temp = nullptr;
	matrix_temp = new double* [rows_A];
	double* vB = nullptr;
	vB = new double[cols_A];
	double* vC = nullptr;
	vC = new double[cols_A];
	double* vX = nullptr;
	vX = new double[cols_A];

	double* tempRow = nullptr;

	double* pivot = nullptr;
	pivot = new double[rows_A];
	//initialization of pivot values------origianl 1.0 for each
	for (i = 0; i < rows_A; i++)
	{
		pivot[i] = 1.0;
	}
	for (i = 0; i < cols_A; i++)
	{
		vC[i] = 0.0;
	}
	for (i = 0; i < cols_A; i++)
	{
		vX[i] = 0.0; //must be 0.0
	}


	for (i = 0; i < rows_A; i++)
	{
		matrix_A[i] = new double[cols_A];
		//initialization needed
	}
	for (i = 0; i < rows_A; i++)
	{
		matrix_L[i] = new double[cols_A];
		//initialization needed
	}
	for (i = 0; i < rows_A; i++)
	{
		matrix_temp[i] = new double[cols_A];
	}


	//initialization of L and D
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_A; j++)
		{
			if (i == j)
				matrix_L[i][j] = 1.0;
			else
				matrix_L[i][j] = 0.0;

			matrix_temp[i][j] = 0.0;
		}
	}

	//populate the entries of matrix A
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

	//Enter for the vector b: Ax = b
	cout << "Enter the vector b each at a time, separate by a space\n";
	for (i = 0; i < cols_A; i++)
	{
		cin >> vB[i];
	}
	cout << "--------\n";
	cout << endl;


	//display A on the left side
	cout << endl << endl;
	cout << "Matrix A:\n";
	displayMatrix(matrix_A, rows_A, cols_A);


	//display the vector b vertically
	cout << "Vector b:\n";
	displayMatrix(vB, rows_A);


	//factorization of A into U
	for (i = rows_A - 1; i >= 0; i--)///////////////issues!!!!!
	{
		if (eliminationMatrix_A(rows_A, cols_A, matrix_A, pivot, tempRow, matrix_L, i) == -1)
			exit(0);
	}


	//display the relationship of A = LU
	cout << endl;
	cout << fixed << showpoint << setprecision(3);
	cout << "LU:\n";
	displayMatrixLU(matrix_L, matrix_A, rows_A, cols_A);


	//forward substitution Lc = b
	for (i = 0; i < cols_A; i++)
	{
		forwardSub(matrix_L, vC, vB, i);
	}
	//backward substitution Ux = c
	for (i = cols_A - 1; i >= 0; i--)
	{
		backwardSub(matrix_A, vX, vC, cols_A, i);
	}

	
	//display the solution x vertically
	cout << endl;
	cout << "Vector x:\n";
	displayMatrix(vX, rows_A);


	//efficiency of the program
	cout << "Multiplication: " << tm << endl;
	cout << "Addition/sub  : " << ta << endl;

	return 0;
}


void displayMatrix(double** ptr, int row, int col)
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
		//dash line for better view of the matrix entries
		if (i < row - 1) //ignore appending the last-row dash line 
		{
			for (k = 0; k < col; k++)
				cout << "---------";
		}
		cout << endl;
	}
	cout << endl;
}


void displayMatrix(double* ptr, int row)
{
	//display the detailed entries of a vector
	int i;
	cout << endl;
	for (i = 0; i < row; i++)
	{
		displayElem(ptr[i]);
		cout << endl;
	}
	cout << endl;

}


void displayMatrixLU(double** ptr1, double** ptr2, int row, int col)
{
	//display the detailed entries of a matrix
	int i, j, k;
	cout << endl;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			displayElem(ptr1[i][j]);
		}
		cout << " | ";
		for (j = 0; j < col; j++)
		{
			displayElem(ptr2[i][j]);
		}
		cout << endl;
	}
	cout << endl << endl;
}



void displayElem(double entry, int pts)
{
	cout << fixed << showpoint << setprecision(pts);
	if (entry - static_cast<int>(entry) == 0.0)
		cout << setw(7) << static_cast<int>(entry) << " ";
	else
	{
		int i = 1;
		while (i < pts)	//entry * 10 ^n folds
		{
			if ((entry * pow(10, i)) - static_cast<int>(entry * pow(10, i)) == 0.0)
			{
				cout << setprecision(i);
				cout << setw(7) << entry << " ";
				cout << setprecision(pts);
				break;
			}
			i++;
		}
		if (i == pts)
			cout << setw(7) << entry << " "; //default 3 decimal points

	}
}


void forwardSub(double** matrix_L, double* vectorC, double* vectorB, int i) // 0 <= i < n
{
	int j;
	for (j = 0; j <= i; j++)
	{
		if (i != j)
		{
			vectorB[i] -= matrix_L[i][j] * vectorC[j]; //C must be initialized with 0.0
			tm++;
			ta++;
		}
	}
	vectorC[i] = vectorB[i];
}

void backwardSub(double** matrix_A, double* vectorX, double* vectorC, int cols, int i) // 0 <= i < n
{
	int j;
	for (j = cols - 1; j >= i; j--)
	{
		if (i != j)
		{
			vectorC[i] -= matrix_A[i][j] * vectorX[j]; //X must be initialized with 0.0
			tm++;
			ta++;
		}
	}
	vectorX[i] = vectorC[i] / matrix_A[i][i];
	tm++;
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
	for (i = 1; i <= cycle; i++)
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



int eliminationMatrix_A(int rows, int cols, double** matrix_A, double* pivot, double* tempRow, double** matrix_L, int cycle)
{
	//process to find A-1
	//Goal: [A I] to get [I A-1]
	static int i, j;
	int a;
	tempRow = new double[cols];
	for (a = 0; a < cols; a++)
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
			for (k = 0; k < cols; k++)
			{
				tempRow[k] = matrix_A[i + 1 + copyRowOff][k];
			}
			for (k = 0; k < cols; k++)
			{
				matrix_A[i + 1 + copyRowOff][k] = matrix_A[i][k];
			}
			for (k = 0; k < cols; k++)
			{
				matrix_A[i][k] = tempRow[k];
			}
			copyRowOff++;
		}

		//Permutation matrix P is
		//

		copyRowOff = 0;
		pivot[i] = matrix_A[i][j];
		if (pivot[i] == 0.0)
		{
			cout << "Lack at least one non-zero pivot\n";
			cout << "A is not invertible\n";
			return -1;
		}
		multiplier = matrix_A[i + rowOperate][j];
		matrix_L[i + rowOperate][i] = multiplier / pivot[i];
		for (k = 0; k < cols; k++)
		{
			matrix_A[i + rowOperate][k] -= (matrix_L[i + rowOperate][i]) * matrix_A[i][k];
			tm++;
			ta++;
		}
		rowOperate++;

	}
	i++;
	j++;
	delete[] tempRow;
	tempRow = nullptr;
	return 1;
}

