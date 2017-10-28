#ifndef MATRIX
#define MATRIX
#include <vector>
#include <cassert>
#include <iostream>

using namespace std;

template<typename T>
class Matrixrow
{	
public:
	Matrixrow(T* row, size_t size);
	~Matrixrow(){};
	T& operator[](size_t col);

private:
	T* Arow; 	
	size_t size; 
};

template<typename T>
class Matrix
{	
public:
	Matrix(size_t rows, size_t cols);
	~Matrix();
	size_t get_n_rows();
	size_t get_n_cols();
	Matrixrow<T> operator[](size_t row);
	vector<T> operator*(vector<T> v);
	Matrix<T> operator*(T value);
	bool operator==(Matrix<T>& B);
	bool operator!=(Matrix<T>& B);
	Matrix(const Matrix<T>& copied);
	Matrix(Matrix<T>&& movied);
	Matrix<T>& operator=(const Matrix<T>& copied);
	Matrix<T>& operator=(Matrix<T>&& movied);


private:
	T** A;
	size_t n_cols;
	size_t n_rows;
};

template<typename T>
ostream& operator<<(ostream& out, Matrix<T> &A);

#endif
