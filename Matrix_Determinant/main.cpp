#include <iostream>
#include "Matrix.h"
#include "Det.h"
#include <cstdlib>
#include <string>
#include <chrono>
using namespace std;

void prompt(int rows, int cols, double **&matrix_A);

int main()
{
	int m, n;
	cout << "Enter the row #m and col #n of a matrix A\n";
	cin >> m >> n;
	double **matrix_A = nullptr;
	matrix_A = new double *[m];
	for (int i = 0; i < m; i++)
	{
		matrix_A[i] = new double[n];
	}
	prompt(m, n, matrix_A);
	Det matrix(matrix_A, m, n);
	auto start = std::chrono::system_clock::now();
	// computation
	double det = matrix.getDeterminant();

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;

	cout << "The determinant of the matrix is " << det << endl;
	cout << "Time elapsed = " << elapsed_seconds.count() << "s\n";

	system("pause");
}

void prompt(int rows, int cols, double **&matrix_A)
{
	int i, j;
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
}