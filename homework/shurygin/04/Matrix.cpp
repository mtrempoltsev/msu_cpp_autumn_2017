#include "Matrix.h"
#include <cassert>

Matrix::Matrix(std::size_t rows, std::size_t cols): rows_(rows), cols_(cols) 
{
	for (std::size_t i = 0; i < rows_; ++i)
	{
		Row r(cols);
		matrix_.push_back(r);
	}
}

Row& Matrix::operator[](std::size_t i)
{
	assert(i < matrix_.size());
	return matrix_[i];
}

Matrix Matrix::operator*=(double a)
{	
	for (std::size_t i = 0; i < rows_; ++i)
		for (std::size_t j = 0; j < cols_; ++j)
			matrix_[i][j] *= a;
	return *this;
}

Matrix Matrix::operator*=(std::vector<double> v)
{
	assert(v.size() == cols_);
	Matrix m(rows_, 1);
	for (std::size_t i = 0; i < rows_; ++i)
	{
		double s = 0.0;
		for (std::size_t j = 0; j < cols_; ++j)
		{
			s += matrix_[i][j] * v[j];
		}
		m[i][0] = s;
	}	
	matrix_.clear();
	*this = m;
	return *this;
}

bool Matrix::operator==(Matrix m) const
{
	if (rows_ != m.GetRows() || cols_ != m.GetCols())
		return false;
	for (std::size_t i = 0; i < rows_; ++i)
		for (std::size_t j = 0; j < cols_; ++j)
			if (matrix_[i][j] != m[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(Matrix m) const
{
	return !((*this) == m);
}

Matrix::~Matrix()
{
}
