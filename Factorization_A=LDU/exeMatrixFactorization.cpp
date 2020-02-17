/*
This program is to compute the factorization of
matrix A into a lower triangular matrix L and the
upper triagular matrix U. In order to record the
array of pivots, the matrix U is divided into a
diagonal matrix D and U with 1's on the main diagonal
entries.
*/

#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<string>

using namespace std;

void eliminationAbovePivot(int auguCols, double** matrix_A, int cycle);
int eliminationMatrix_A(int rows, int cols, double** matrix_A, double** matrix_D, double* tempRow, double** matrix_L, int cycle);
void constantMulti(int cols, double** matrix_A, int rows, double** matrix_D);
void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C);
int integerIdentify(int num);

int main()
{
	int rows_A, cols_A;
	int i, j, k;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> rows_A >> cols_A;

	double** matrix_A = nullptr;
	matrix_A = new double* [rows_A];
	double** matrix_L = nullptr;
	matrix_L = new double* [rows_A];
	double** matrix_D = nullptr;
	matrix_D = new double* [rows_A];
	double** matrix_C = nullptr;
	matrix_C = new double* [rows_A];
	double** matrix_temp = nullptr;
	matrix_temp = new double* [rows_A];

	double* tempRow = nullptr;

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
		matrix_D[i] = new double[cols_A];
		//initialization needed
	}
	for (i = 0; i < rows_A; i++)
	{
		matrix_C[i] = new double[cols_A];
	}
	for (i = 0; i < rows_A; i++)
	{
		matrix_temp[i] = new double[cols_A];
	}



	//initialization of L and D and C
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_A; j++)
		{
			if(i == j)
				matrix_L[i][j] = 1.0;
			else
				matrix_L[i][j] = 0.0;

			matrix_D[i][j] = 0.0;
			matrix_C[i][j] = 0.0;
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

	//display A on the left side
	cout << endl << endl;
	cout << "Matrix A:\n";
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_A; j++)
		{
			if (matrix_A[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			else
				cout << setw(7) << matrix_A[i][j] << " ";
		}
		cout << endl;
		if (i != rows_A - 1)
		{
			for(k = 0; k < cols_A; k++)
				cout << "---------";
		}
		cout << endl;
	}
	cout << endl << endl;


	//factorization of A into U
	for (i = rows_A - 1; i >= 0; i--)///////////////
	{
		if (eliminationMatrix_A(rows_A, cols_A, matrix_A, matrix_D, tempRow, matrix_L, i) == -1)
			exit(0);
	}

	//divide each row by its pivot
	constantMulti(cols_A, matrix_A, rows_A, matrix_D);

	//calculate the multiplication of LDU = C
	matrixMulti(rows_A, cols_A, cols_A, matrix_D, matrix_A, matrix_temp);
	matrixMulti(rows_A, cols_A, cols_A, matrix_L, matrix_temp, matrix_C);


	//display the relationship of A = LDU
	cout << fixed << showpoint << setprecision(3);
	cout << "LDU:\n";
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_A; j++)
		{
			if (matrix_L[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			else
				cout << setw(7) << matrix_L[i][j] << " ";
		}
		cout << " | ";

		for (j = 0; j < cols_A; j++)
		{
			if (matrix_D[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			else
				cout << setw(7) << matrix_D[i][j] << " ";
		}
		cout << " | ";

		for (j = 0; j < cols_A; j++)
		{
			if (matrix_A[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			else
				cout << setw(7) << matrix_A[i][j] << " ";
		}
		cout << endl;
		/*
		if (i != rows_A - 1)
		{
			cout << "\n-------------------------\n";
		}
		*/
	}


	//display C(should be the same as A) on the left side
	cout << endl;
	cout << "Reassure Matrix A is the same as above: A=LDU\n";
	for (i = 0; i < rows_A; i++)
	{
		for (j = 0; j < cols_A; j++)
		{
			if (matrix_C[i][j] == 0.0)
				cout << setw(7) << "0" << " ";
			else
				cout << setw(7) << matrix_C[i][j] << " ";
		}
		cout << endl;
		if (i != rows_A - 1)
		{
			for (k = 0; k < cols_A; k++)
				cout << "---------";
		}
		cout << endl;
	}
	cout << endl << endl;

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


void constantMulti(int cols, double** matrix_A, int rows, double** matrix_D)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < cols; j++)
		{
			matrix_A[i][j] /= matrix_D[i][i];
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



int eliminationMatrix_A(int rows, int cols, double** matrix_A, double** matrix_D, double* tempRow, double** matrix_L, int cycle)
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
		matrix_D[i][i] = matrix_A[i][i];
		if (matrix_D[i][i] == 0.0)
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
		matrix_D[i][i] = matrix_A[i][j];
		if (matrix_D[i][i] == 0.0)
		{
			cout << "Lack at least one non-zero pivot\n";
			cout << "A is not invertible\n";
			return -1;
		}
		multiplier = matrix_A[i + rowOperate][j];
		matrix_L[i + rowOperate][i] = multiplier / matrix_D[i][i];
		for (k = 0; k < cols; k++)
		{
			matrix_A[i + rowOperate][k] -= (matrix_L[i + rowOperate][i]) * matrix_A[i][k];
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
