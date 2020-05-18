#include "Matrix.h"
#include "Det.h"
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

const int TWOBYTWO_MATRIX = 2;

double Det::calcDeterminant(double** M, int currN)
{
	if (currN > TWOBYTWO_MATRIX)
	{
		double determinant = 0.0;
		for (int i = 0; i < currN; i++)
		{
			determinant += pow(-1, line_row + i) * M[line_row][i] * calcDeterminant(reduceMatrix(M, currN - 1, line_row, i), currN - 1);
		}
		return determinant;
	}

	if (currN == TWOBYTWO_MATRIX)
	{
		return calc2x2Matrix(M);
	}
}

double** Det::reduceMatrix(double** M, int currN, int e_row, int e_col)
{
	if (e_col > currN)
		return nullptr;

	double** subMatrix = new double* [currN];
	int i, j;
	for (i = 0; i < currN; i++)
	{
		subMatrix[i] = new double[currN];
	}

	int a, b;
	//reassign matrix
	for (i = 0, a = 0; i < currN + 1; i++, a++)
	{
		//skip the elimination row
		if (i == e_row)
		{
			a--;
			continue;
		}
		for (j = 0, b = 0; j < currN + 1; j++, b++)
		{
			//skip the elimination col
			if (j == e_col)
			{
				b--;
				continue;
			}
			subMatrix[a][b] = M[i][j];
		}
	}
	return subMatrix;
}

double Det::calc2x2Matrix(double **M)
{
	if (!M)
		return 0.0;
	return M[1][1] * M[0][0] - M[0][1] * M[1][0];
}
