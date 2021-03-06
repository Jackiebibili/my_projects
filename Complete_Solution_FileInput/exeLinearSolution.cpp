#include<iostream>
#include<cstdlib>
#include<cmath>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

void eliminationAbovePivot(int auguCols, double** matrix_A, int* index, int minRow);
int eliminationMatrix_A(int rows, int cols, int auguCols, double** matrix_A, double* pivot, int* index, double* tempRow, int cycle);
void constantMulti(int auguCols, double** matrix_A, int cycle, double* pivot);
void matrixMulti(int rows, int cols, int commonCR, double** matrix_A, double** matrix_B, double** matrix_C);
int integerIdentify(int num);
void displayElem(double entry, int pts = 2);
void displayMatrix(double** ptr, int row, int col);
void particularSolution(double** ptr, double** vX, int* index, int rows, int auguCols);
void nullspaceSolution(double** ptr, int dimen, int rows, int cols, int* index);
void fileInput(fstream& file, string filename, double** ptr, int col);

int main()
{
	int rows, cols;
	int i, j;
	int real_row;
	int xnDim = 0;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> rows >> cols;
	cin.ignore();

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

	string nameMatrix, nameVector;
	cout << "Enter the matrix A file name\n";
	getline(cin, nameMatrix);
	cout << endl;
	cout << "Enter the vector b file name\n";
	getline(cin, nameVector);
	cout << endl;

	fstream file(nameMatrix, ios::in);
	fstream fileV(nameVector, ios::in);
	file.close();
	fileV.close();
	fileInput(file, nameMatrix, matrix_A, cols);
	fileInput(fileV, nameVector, vB, 1);




	//1. Augumented matrix formed
	//populate with [A b]
	for (i = 0; i < rows; i++)
	{
		for (j = cols; j < auguCols; j++)
		{
			matrix_A[i][j] = vB[i][0];
		}
	}



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
		if (real_row == -1)
		{
			cout << "Inconsistency\nThe systems have no solution\n";
			exit(0);
		}
	}

	//3. divide/multiply each row with a number so that it the left part form an identity matrix
	constantMulti(auguCols, matrix_A, rows, pivot);
	//4. get entries above each pivot 0 by row adding/subtracting
	eliminationAbovePivot(auguCols, matrix_A, index, real_row);



	//find the particular solution
	particularSolution(matrix_A, vX, index, real_row, auguCols);

	//display the Xp
	cout << "Xp = \n";
	displayMatrix(vX, cols, 1);

	//find the nullspace N(A) solution(s)
	xnDim = cols - real_row;
	cout << "There exist solution(s) in the column space of R^";
	if (xnDim > 0)
	{
		cout << cols - real_row;
		nullspaceSolution(matrix_A, xnDim, real_row, cols, index);
		cout << endl;
	}
	else
	{
		cout << "1\n";
		cout << "The nullspace solution is {0}" << endl;
	}

	//system pause included for exe file
	system("pause");
	return 0;

}


void fileInput(fstream& file, string filename, double **ptr, int col)
{
	file.open(filename, ios::in);
	file.clear();
	int i = 0, j = 0;
	string temp, l;
	while (getline(file, temp, ','))
	{
		if (temp != "\n")
		{
			ptr[i][j] = stod(temp);
			j++;
		}
		if (j >= col)
		{
			i++;
			j = 0;
		}
	}
	file.close();
}




void particularSolution(double** ptr, double** vX, int* index, int rows, int auguCols)
{
	int i = 0;
	while (i < rows)
	{
		vX[index[i]][0] = ptr[i][auguCols - 1];
		i++;
	}
}


void nullspaceSolution(double** ptr, int dimen, int rows, int cols, int* index)
{
	int i, j, k;
	double** xn = nullptr;
	xn = new double* [cols];
	for (i = 0; i < cols; i++)
	{
		xn[i] = new double[dimen];
	}
	//must initialize to 0
	for (i = 0; i < dimen; i++)
	{
		for (j = 0; j < cols; j++)
		{
			xn[j][i] = 0.0;
		}
	}
	k = 0;
	bool test = true;
	int* free = nullptr;
	free = new int[dimen];
	//get the free row number(since 0)
	for (i = 0; i < cols; i++)
	{
		for (j = 0; j < cols; j++)
		{
			if (i == index[j])
			{
				test = false;
				break;
			}
		}
		if (test)
		{
			free[k] = i;
			k++;
		}
		test = true;
	}
	for (k = 0; k < dimen; k++)
	{
		for (j = 0; j < rows; j++)
		{
			xn[index[j]][k] = -ptr[j][free[k]];
		}
	}
	//free varibles to be 1.0
	for (i = 0; i < dimen; i++)
	{
		xn[free[i]][i] = 1.0;
	}
	cout << endl;
	displayMatrix(xn, cols, dimen);
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
	/*
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
	*/
	for (i = 1; i < minRow; i++)
	{
		for (j = i - 1; j >= 0; j--)
		{
			pos = index[i];
			multiplier = matrix_A[j][pos];
			for (k = 0; k < auguCols; k++)
			{
				matrix_A[j][k] -= (multiplier / p) * matrix_A[i][k];
			}

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

	while (matrix_A[i][j] == 0.0)
	{
		//swap the row with the one comes right after
		if (copyRowOff >= rows - 1 - i)		//validation
		{
			/*
			cout << "Lack at least one non-zero pivot\n";
			cout << "A is not invertible\n";
			return -1;
			*/
			break;
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

	//detect the first non-zero entry at that row = col_x
	for (col_x = i; col_x < auguCols; col_x++)
	{
		if (matrix_A[i][col_x] != 0)
			break;
	}
	if (col_x == auguCols)	//reach the first all-zero's row
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
	else if (col_x == auguCols - 1)
		return -1;

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
		//displayMatrix(matrix_A, rows, auguCols);
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
			for (k = 0; k < col; k++)
				cout << "-------";
		}
		cout << endl;
	}
	cout << endl;
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
