#include "Matrix.h"

Matrix::Matrix(size_t rows, size_t cols)
{	
	n_rows = rows;
	n_cols = cols;
	A = new double* [n_rows];
    for(size_t i = 0; i < n_rows; i++)
    {
        A[i] = new double [n_cols];
    }
}

Matrix::~Matrix()
{	
	
	for(size_t i = 0; i < n_rows; i++)
    {	
        delete[] A[i];
    }
    delete[] A;
    
}

size_t Matrix::get_n_rows()
{
	return n_rows;
}

size_t Matrix::get_n_cols()
{
	return n_cols;
}

Matrixrow Matrix::operator[](size_t row)
{	
	assert(row < n_rows && row >= 0);
	return Matrixrow(A[row], n_cols);
}

Matrix Matrix::operator*(double value)
{	
	Matrix C(n_rows, n_cols);
	for(size_t i = 0; i < n_rows; i++)
	{
		for(size_t j = 0; j < n_cols; j++)
		{
			C[i][j] = A[i][j] * value;
		}
	}
	return C;
}

bool Matrix::operator==(Matrix& B) 
{	
	if (n_rows != B.get_n_rows()) return false;
	if (n_cols != B.get_n_cols()) return false;

    for (size_t i = 0; i < n_rows; ++i)
    {
    	for (size_t j = 0; j < n_cols; ++j)
    	{
    		if (A[i][j] != B[i][j]) return false;
    	}
    }
                
    return true;
}

bool Matrix::operator!=(Matrix& B) 
{	
	if (n_rows != B.get_n_rows()) return true;
	if (n_cols != B.get_n_cols()) return true;

    for (size_t i = 0; i < n_rows; ++i)
    {
    	for (size_t j = 0; j < n_cols; ++j)
    	{
    		if (A[i][j] != B[i][j]) return true;
    	}
    }
                
    return false;
}

vector<double> Matrix::operator*(vector<double> v)
{
	assert(v.size() == n_cols);
	vector<double> res(n_rows);


	for(size_t i = 0; i < n_rows; i++)
	{	
		res[i] = 0;
		for(size_t j = 0; j < n_cols; j++)
		{
			res[i] += A[i][j] * v[j];
		}
	}

	return res;
}

Matrixrow::Matrixrow(double* row, size_t col_size)
{
	Arow = row;
	size = col_size;
}

double& Matrixrow::operator[](size_t col)
{	
	assert(col < size && col >= 0);
	return Arow[col];
}