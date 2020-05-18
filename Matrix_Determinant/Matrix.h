#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix
{
protected:
	double** matrix;
	int m;
	int n;
public:
	Matrix() { }
	Matrix(double** M, int matrix_m, int matrix_n)
	{
		m = matrix_m;
		n = matrix_n;
		allocMatrix(matrix_m, matrix_n);
		reassignMatrix(M, matrix_m, matrix_n);
	}
	Matrix(int matrix_m, int matrix_n) 
	{
		m = matrix_m;
		n = matrix_n;
		allocMatrix(matrix_m, matrix_n);
	}
	int getRow() const { return m; }
	int getColumn() const { return n; }
	void setRow(int row) { m = row; }
	void setColumn(int col) { n = col; }

	void reassignMatrix(double** M, int matrix_m, int matrix_n);
	void allocMatrix(int matrix_m, int matrix_n);
	virtual ~Matrix();
};



#endif