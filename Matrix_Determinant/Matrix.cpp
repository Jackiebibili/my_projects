#include "Matrix.h"
#include <iostream>

void Matrix::allocMatrix(int matrix_m, int matrix_n)
{
	matrix = new double* [matrix_m];
	for (int i = 0; i < matrix_m; i++)
	{
		matrix[i] = new double[matrix_n];
		for (int j = 0; j < matrix_n; j++)
		{
			matrix[i][j] = 0;
		}
	}
}


void Matrix::reassignMatrix(double** M, int matrix_m, int matrix_n)
{
	int i, j;
	//reassignment
	for (i = 0; i < matrix_m; i++)
	{
		for (j = 0; j < matrix_n; j++)
		{
			matrix[i][j] = M[i][j];
		}
	}
}


Matrix::~Matrix()
{
	for (int i = 0; i < m; i++)
	{
		delete matrix[i];
	}
}


