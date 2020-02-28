#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<string>

using namespace std;

void eliminationAbovePivot(int auguCols, double** matrix_A, int* index, int minRow);
int eliminationMatrix_A(int rows, int cols, int auguCols, double** matrix_A, double* pivot, int* index, double* tempRow, int cycle);
void constantMulti(int auguCols, double** matrix_A, int cycle, double* pivot);
void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C);
int integerIdentify(int num);
void displayElem(double entry, int pts = 3);
void displayMatrix(double** ptr, int row, int col);
void particularSolution(double** ptr, double** vX, int* index, int auguCols, int rows);


int main()
{
	int rows, cols;
	int i, j;
	int real_row;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> rows >> cols;
	double** matrix_A = nullptr;
	matrix_A = new double* [rows];
	int auguCols = cols + 1; //col length of vector b = 1
	for (i = 0; i < rows; i++)
	{
		matrix_A[i] = new double[auguCols];
		//initialization needed
	}
	double** vB = nullptr;
	vB = new double* [rows];
	for (i = 0; i < rows; i++)
	{
		vB[i] = new double[1];
		//initialization needed
	}
	double** vX = nullptr;
	vX = new double* [cols];
	for (i = 0; i < cols; i++)
	{
		vX[i] = new double[1];
		vX[i][0] = 0.0;	//initialization
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

	cout << "Enter the vector b each at a time, separate by a space\n";
	for (i = 0; i < rows; i++)
	{
		cin >> vB[i][0];
	}
	cout << "--------\n";
	cout << endl;


	//1. Augumented matrix formed
	//populate with [A b]
	for (i = 0; i < rows; i++)
	{
		for (j = cols; j < auguCols; j++)
		{
			matrix_A[i][j] = vB[i][0];
		}
	}

	//display the [A b] before computing
	cout << endl << "[A b] = \n";
	displayMatrix(matrix_A, rows, auguCols);
	//check point V


	double* pivot = nullptr;
	pivot = new double[rows];
	//initialization of pivot values------origianl 1.0 for each
	for (i = 0; i < rows; i++)
	{
		pivot[i] = 1.0;
	}
	int* index = nullptr;
	index = new int[cols];
	for (i = 0; i < cols; i++)
	{
		index[i] = -1;
	}



	cout << "To find the [R d]\n";
	//2. solving a n-D linear system regarding [A b] 
	double* tempRow = nullptr;
	for (i = rows - 1; i >= 0; i--)
	{
		real_row = eliminationMatrix_A(rows, cols, auguCols, matrix_A, pivot, index, tempRow, i);
		if (real_row== -1)
			exit(0);
	}

	//3. divide/multiply each row with a number so that it the left part form an identity matrix
	constantMulti(auguCols, matrix_A, rows, pivot);
	//4. get entries above each pivot 0 by row adding/subtracting
	eliminationAbovePivot(auguCols, matrix_A, index, real_row);


	//cout << fixed << showpoint << setprecision(2);
	cout << "[R d] is: \n";

	//display the [R d] after computing
	displayMatrix(matrix_A, rows, auguCols);
	//check point


	//find the particular solution
	particularSolution(matrix_A, vX, index, auguCols, real_row);

	//display the Xp
	cout << "Xp = \n";
	displayMatrix(vX, cols, 1);



	return 0;

}



void particularSolution(double** ptr, double** vX, int* index, int auguCols, int rows)
{
	int i = 0;
	while (i < rows)
	{
		vX[index[i]][0] = ptr[i][index[i]];
		i++;
	}
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

void eliminationAbovePivot(int auguCols, double** matrix_A, int *index, int minRow)
{
	int i, j, k;
	double multiplier = 0.0;
	double p = 1.0;
	int pos = 0;
	for (i = 0; i < minRow - 1; i++)
	{
		//the second row subtracts from the first row
		pos = index[i + 1];
		multiplier = matrix_A[i][pos];
		for (k = 0; k < auguCols; k++)
		{
			matrix_A[i][k] -= (multiplier / p) * matrix_A[i + 1][k];
		}

	}
}



int eliminationMatrix_A(int rows, int cols, int auguCols, double** matrix_A, double* pivot, int *index, double* tempRow, int cycle)
{
	//process to find A-1
	//Goal: [A I] to get [I A-1]
	static int i, j;
	int col_x;
	int a;
	tempRow = new double[auguCols];
	for (a = 0; a < auguCols; a++)
		tempRow[a] = 0.0;
	int k;
	int copyRowOff = 0;
	double multiplier = 0.0;
	int rowOperate = 1; //row advanced #: e.g. rO = 1 means it's currently at row #2

	//detect the first non-zero entry at that row = col_x
	for (col_x = i; col_x < auguCols; col_x++)
	{
		if (matrix_A[i][col_x] != 0)
			break;
	}
	if (col_x >= auguCols)	//reach the first all-zero's row
	{
		//verify the rest of the row to be all zero's
		if (i == rows)	//already the last row all-zero's
			return i;
		for (a = i + 1; a < rows; a++)	//search through the rest of rows
		{
			for (k = 0; k < cols; k++)
			{
				if (matrix_A[a][k] != 0)
					return -1;
			}
		}
		return i;
	}

	//still have pivots to compute
	pivot[i] = matrix_A[i][col_x];
	index[i] = col_x;
	/*
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
	*/
	
	while (rowOperate <= cycle)
	{
		/*
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
		*/
		copyRowOff = 0;
		/*
		if (pivot[i] == 0.0)
		{
			cout << "Lack at least one non-zero pivot\n";
			cout << "A is not invertible\n";
			return -1;
		}
		*/
		multiplier = matrix_A[i + rowOperate][col_x];
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
	return rows;
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
		if (i == pts)
			cout << setw(6) << entry << " "; //default 3 decimal points

	}
}
