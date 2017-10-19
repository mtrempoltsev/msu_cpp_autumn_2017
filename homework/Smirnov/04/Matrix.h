#ifndef MATRIX
#define MATRIX
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

class Matrixrow
{	
public:
	Matrixrow(double* row, size_t size);
	~Matrixrow(){};
	double& operator[](size_t col);

private:
	double* Arow; 	
	size_t size; 
};

class Matrix
{	
public:
	Matrix(size_t rows, size_t cols);
	~Matrix();
	size_t get_n_rows();
	size_t get_n_cols();
	Matrixrow operator[](size_t row);
	vector<double> operator*(vector<double> v);
	Matrix& operator*(double value);
	bool operator==(Matrix& B);
	bool operator!=(Matrix& B);


private:
	double** A;
	size_t n_cols;
	size_t n_rows;
};

ostream& operator<<(ostream& out, Matrix A);

#endif
