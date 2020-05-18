#ifndef DET_H
#define DET_H
#include "Matrix.h"
#include <iostream>

class Det : public Matrix
{
private:
	int line_row;
	int line_col;
public:
	Det() 
	{
		line_row = -1;
		line_col = -1;
	}
	Det(double** M, int matrix_m, int matrix_n) : Matrix(M, matrix_m, matrix_n)
	{
		line_row = -1;
		line_col = -1;
	}
	Det(int matrix_m, int matrix_n) : Matrix(matrix_m, matrix_n)
	{
		line_row = -1;
		line_col = -1;
	}
	double getDeterminant() 
	{
		line_col = 0;
		line_row = 0;
		return calcDeterminant(matrix, m);
	}
	double calcDeterminant(double** M, int currN);
	double calc2x2Matrix(double **M);
	double** reduceMatrix(double** M, int currN, int e_row, int e_col);
	~Det() { }

};



#endif