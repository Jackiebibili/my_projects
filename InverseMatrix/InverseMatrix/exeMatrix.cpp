#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<string>
using namespace std;

int tm = 0; //efficiency of the program
int ta = 0;

void eliminationAbovePivot(int auguCols, double** matrix_A, int cycle);
int eliminationMatrix_A(int rows, int cols, int auguCols, double** matrix_A, double* pivot, double* tempRow, int cycle);
void constantMulti(int auguCols, double** matrix_A, int cycle, double* pivot);
void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C);
int integerIdentify(int num);

int main()
{
	int rows, cols;
	int i, j;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> rows >> cols;
	double** matrix_A = nullptr;
	matrix_A = new double* [rows];
	int auguCols = cols + rows;
	for (i = 0; i < rows; i++)
	{
		matrix_A[i] = new double[auguCols];
		//initialization needed
	}

	//normal matrix A nxn
	double** matrix = nullptr;
	matrix = new double* [rows];
	for (i = 0; i < rows; i++)
	{
		matrix[i] = new double[cols];
		//initialization needed
	}

	double** vB = nullptr;
	vB = new double* [cols];
	double** vX = nullptr;
	vX = new double* [cols];
	for (i = 0; i < rows; i++)
	{
		vB[i] = new double[cols];
		//initialization needed
	}
	for (i = 0; i < rows; i++)
	{
		vX[i] = new double[cols];
		//initialization needed
	}

	for (i = 0; i < cols; i++)
	{
		vB[i][0] = 0.0;
	}
	for (i = 0; i < cols; i++)
	{
		vX[i][0] = 0.0; //must be 0.0
	}


	cout << "Enter the matrix A by entering each row at a time\n";
	cout << "separate each row's input by an newline\n";
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			cin >> matrix_A[i][j];
		}
		if (i != rows - 1)
		{
			cout << "--------\n";
		}
	}
	cout << endl << endl;


	//Enter for the vector b: Ax = b
	//display vector b
	cout << "Enter the vector b each at a time, separate by a space\n";
	for (i = 0; i < cols; i++)
	{
		cin >> vB[i][0];
	}
	cout << "--------\n";
	cout << endl;
	cout << "Vector b:\n";
	for (i = 0; i < cols; i++)
	{
		cout << setw(7) << vB[i][0] << endl;
	}
	cout << endl;



	//1. Augumented matrix formed
	//populate with [A I]
	int onesPos = cols;		//position of 1 in the nxn I
	for (i = 0; i < rows; i++)
	{
		for (j = cols; j < auguCols; j++)
		{
			if (j == onesPos)
				matrix_A[i][j] = 1.0;
			else
				matrix_A[i][j] = 0.0;
		}
		onesPos++;
	}


	double* pivot = nullptr;
	pivot = new double[rows];
	//initialization of pivot values------origianl 1.0 for each
	for (i = 0; i < rows; i++)
	{
		pivot[i] = 1.0;
	}


	cout << "To find the inverse of A\n";
	//2. solving a n-D linear system regarding [A I] 
	double* tempRow = nullptr;
	for (i = rows - 1; i >= 0; i--)
	{
		if (eliminationMatrix_A(rows, cols, auguCols, matrix_A, pivot, tempRow, i) == -1)
			exit(0);
	}

	//3. get entries above each pivot 0 by row adding/subtracting
	eliminationAbovePivot(auguCols, matrix_A, rows - 1);

	//4. divide/multiply each row with a number so that it the left part form an identity matrix
	constantMulti(auguCols, matrix_A, rows, pivot);


	//display the inverse A
	cout << "The inverse A is: \n";
	cout << fixed << showpoint << setprecision(3);
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < auguCols; j++)
		{
			if (matrix_A[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			/*else if (integerIdentify(matrix_A[i][j]) == 1)
				cout << setw(7) << static_cast<int>(matrix_A[i][j]) << " ";*/
			else
				cout << setw(7) << matrix_A[i][j] << " ";
		}
		if (i != rows - 1)
		{
			cout << "\n-------------------------\n";
		}
	}
	cout << endl << endl;

	//change the augumented matrix into a normal matrix A
	//display the matrix A
	for (i = 0; i < rows; i++)
	{
		for (j = cols; j < auguCols; j++)
		{
			matrix[i][j - cols] = matrix_A[i][j];
		}
	}
	cout << "Matrix A nxn:\n";
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			cout << setw(7) << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;


	//compute inverse of A times vector b
	//x = (A-1) b
	matrixMulti(rows, 1, cols, matrix, vB, vX);


	//display the vector x
	cout << "Vector x:\n";
	for (i = 0; i < cols; i++)
	{
		cout << setw(7) << vX[i][0] << endl;
	}
	cout << endl << endl;


	//efficiency of the program
	cout << "Multiplication: " << tm << endl;
	cout << "Addition/sub  : " << ta << endl;

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
				tm++;
				ta++;
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
			tm++;
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
				tm++;
				ta++;
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
