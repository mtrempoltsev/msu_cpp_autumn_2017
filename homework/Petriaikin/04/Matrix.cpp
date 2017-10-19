#include "Matrix.h"
#include <cassert>

//========================================================================

Matrix::MatrixRow::MatrixRow(double* row, size_t max_columns) :
						row_ (row), max_column_ (max_columns)
{}

double& Matrix::MatrixRow::operator[] (size_t column)
{
	assert(column < max_column_);
	return row_ [column];
}

const double& Matrix::MatrixRow::operator[] (size_t column) const
{
	assert(column < max_column_);
	return row_ [column];
}

//========================================================================

Matrix::Matrix(std::pair<size_t, size_t> shape, const std::vector<double>& data) :
			matrix_ (nullptr), shape_ (shape)
{
	if (data.size() != shape.first*shape.second)
	{
		throw std::logic_error("Wrong size of data array!");
	}

	matrix_ = new double [data.size()];
	for (size_t i = 0; i < shape.first; i++)
	{
		for (size_t j = 0; j < shape.second; j++)
		{
			matrix_ [i*shape.second + j] = data [i*shape.second + j];
		}
	}

	DEBUG("New object was constructed from shape and data");
}

//Создание столбца
Matrix::Matrix(const std::vector<double>& data) : Matrix ({data.size(), 1}, data)
{}

Matrix::Matrix(std::pair<size_t, size_t> shape, double fill_value) :
	Matrix (shape, std::vector<double> (shape.first*shape.second, fill_value))
{}

Matrix::Matrix(const Matrix& matrix) : shape_(matrix.shape_), matrix_(nullptr)
{
	CreateAndCopy_(shape_.first*shape_.second, matrix.matrix_);

	DEBUG("New object was constructed with copy constructor");
}

void Matrix::CreateAndCopy_(size_t size, const double* data)
{
	matrix_ = new double[size];
	memcpy(matrix_, data, size * sizeof(double));
}

Matrix& Matrix::operator= (const Matrix& arg)
{
	shape_ = std::pair<size_t, size_t>(arg.shape_);

	delete[] matrix_;
	CreateAndCopy_(shape_.first*shape_.second, arg.matrix_);
	
	DEBUG("operator= for l-value reference");
	return *this;
}

//========================================================================

Matrix Matrix::operator+ (const Matrix& arg) const
{
	if (shape_ != arg.shape_)
	{
		throw std::logic_error("Cannot sum this dimentions!");
	}

	Matrix result(*this);
	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		result.matrix_[i] += arg.matrix_[i];
	}

	return result;
}

Matrix Matrix::operator- () const
{
	Matrix result(*this);
	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		result.matrix_[i] = -result.matrix_[i];
	}

	return result;
}

Matrix Matrix::operator- (const Matrix& arg) const
{
	return (*this) + (-arg);
}

Matrix Matrix::operator* (const Matrix& arg) const
{
	if (shape_.second != arg.shape_.first)
	{
		throw std::logic_error("Cannot multiple this dimentions!");
	}

	Matrix result({ shape_.first, arg.shape_.second }, 0);
	for (size_t i = 0; i < shape_.first; i++)
	{
		for (size_t j = 0; j < arg.shape_.second; j++)
		{
			for (size_t k = 0; k < shape_.second; k++)
			{
				result.matrix_ [i*arg.shape_.second+j] += matrix_ [i*shape_.second+k]*
														  arg.matrix_ [k*arg.shape_.second+j];
			}
		}
	}

	return result;
}

Matrix Matrix::operator* (double arg) const
{
	Matrix result(*this);
	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		result.matrix_ [i] *= arg;
	}

	return result;
}

Matrix& Matrix::operator+= (const Matrix& arg)
{
	*this = *this + arg;
	return *this;
}

Matrix& Matrix::operator-= (const Matrix& arg)
{
	*this = *this - arg;
	return *this;
}

Matrix& Matrix::operator*= (const Matrix& arg)
{
	*this = *this * arg;
	return *this;
}

Matrix& Matrix::operator*= (double arg)
{
	*this = *this * arg;
	return *this;
}

bool Matrix::operator== (const Matrix& arg) const
{
	if (shape_ != arg.shape_)
	{
		throw std::logic_error("Cannot compare this dimentions!");
	}

	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		if (Abs(double (matrix_[i] - arg.matrix_[i])) > Constants::epsiol)
		{
			return false;
		}
	}

	return true;
}

bool Matrix::operator!= (const Matrix& arg) const
{
	return !(*this == arg);
}

Matrix::MatrixRow Matrix::operator[] (size_t row)
{
	assert(row < shape_.first);
	return Matrix::MatrixRow(matrix_+row*shape_.second, shape_.second);
}

const Matrix::MatrixRow Matrix::operator[] (size_t row) const
{
	assert(row < shape_.first);
	return Matrix::MatrixRow(matrix_ + row*shape_.second, shape_.second);
}

//========================================================================

Matrix::~Matrix()
{
	DEBUG("Destructor of matrix was called!");

	delete[] matrix_;
}

double Abs(double arg)
{
	return arg >= 0 ? arg : -arg;
}