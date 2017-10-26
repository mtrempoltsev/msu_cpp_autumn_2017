#pragma once
#ifndef MATRIX_HPP
#define MATRIX_HPP

//========================================================================

#include "Matrix.h"

//========================================================================

#define INDEX_ASSERT(x) if (!(x)) {	throw std::logic_error("Index is out of the bounds!"); }

//========================================================================

template<typename T>
Matrix<T>::MatrixRow::MatrixRow(T* row, size_t max_columns) : row_ (row), max_column_ (max_columns)
{}

template<typename T>
T& Matrix<T>::MatrixRow::operator[] (size_t column)
{
	INDEX_ASSERT(column < max_column_);
	return row_ [column];
}

template<typename T>
const T& Matrix<T>::MatrixRow::operator[] (size_t column) const
{
	INDEX_ASSERT(column < max_column_);
	return row_ [column];
}

//========================================================================

template<typename T>
int Matrix<T>::memory_allocated_ = 0;

template<typename T>
void Matrix<T>::AllocateMatrix_(size_t size)
{
	matrix_ = new T [size];
	memory_allocated_++;
}

template<typename T>
Matrix<T>::Matrix(std::pair<size_t, size_t> shape, const std::vector<T>& data) : matrix_ (nullptr), shape_ (shape)
{
	if (data.size() != shape.first*shape.second)
	{
		throw std::logic_error("Wrong size of data array!");
	}

	AllocateMatrix_(data.size());

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
template<typename T>
Matrix<T>::Matrix(const std::vector<T>& data) : Matrix ({data.size(), 1}, data)
{}

template<typename T>
Matrix<T>::Matrix(std::pair<size_t, size_t> shape, T fill_value) :
	Matrix (shape, std::vector<T> (shape.first*shape.second, fill_value))
{}

template<typename T>
Matrix<T>::Matrix(size_t rows, size_t columns, T fill_value) : Matrix({rows, columns}, fill_value)
{}


template<typename T>
Matrix<T>::Matrix(const Matrix& matrix) : shape_(matrix.shape_), matrix_(nullptr)
{
	CreateAndCopy_(shape_.first*shape_.second, matrix.matrix_);

	DEBUG("New object was constructed with copy constructor");
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& matrix) : shape_(matrix.shape_), matrix_(matrix.matrix_)
{
	matrix.matrix_ = nullptr;

	DEBUG("New object was constructed with moving constructor");
}

template<typename T>
void Matrix<T>::CreateAndCopy_(size_t size, const T* data)
{
	AllocateMatrix_(size);

	memcpy(matrix_, data, size * sizeof(T));
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (const Matrix<T>& arg)
{
	if (&arg == this) { return *this; }

	shape_ = std::pair<size_t, size_t>(arg.shape_);

	FreeMatrix_();

	CreateAndCopy_(shape_.first*shape_.second, arg.matrix_);
	
	DEBUG("operator= for l-value reference (data delited!)");
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator= (Matrix<T>&& arg)
{
	if (&arg == this) { return *this; }

	shape_ = arg.shape_;

	FreeMatrix_();

	matrix_ = arg.matrix_;
	arg.matrix_ = nullptr;
	
	DEBUG("operator= for r-value reference (data delited!)");
	return *this;
}

//========================================================================

template<typename T>
Matrix<T> Matrix<T>::operator+ (const Matrix<T>& arg) const
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

template<typename T>
Matrix<T> Matrix<T>::operator- () const
{
	Matrix result(*this);
	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		result.matrix_[i] = -result.matrix_[i];
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator- (const Matrix<T>& arg) const
{
	return (*this) + (-arg);
}

template<typename T>
Matrix<T> Matrix<T>::operator* (const Matrix<T>& arg) const
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
				result.matrix_ [i*arg.shape_.second+j] += matrix_ [i*shape_.second+k]*arg.matrix_ [k*arg.shape_.second+j];
			}
		}
	}

	return result;
}

template<typename T>
Matrix<T> Matrix<T>::operator* (T arg) const
{
	Matrix result(*this);
	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		result.matrix_ [i] *= arg;
	}

	return result;
}

template<typename T>
Matrix<T>& Matrix<T>::operator+= (const Matrix<T>& arg)
{
	*this = *this + arg;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator-= (const Matrix<T>& arg)
{
	*this = *this - arg;
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*= (const Matrix<T>& arg)
{
	*this = (*this * arg);
	return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*= (T arg)
{
	*this = *this * arg;
	return *this;
}
template<typename T>
bool Matrix<T>::operator== (const Matrix<T>& arg) const
{
	if (shape_ != arg.shape_)
	{
		throw std::logic_error("Cannot compare this dimentions!");
	}

	size_t size = shape_.first*shape_.second;
	for (size_t i = 0; i < size; i++)
	{
		if (Abs(T (matrix_[i] - arg.matrix_[i])) > Constants::epsiol)
		{
			return false;
		}
	}

	return true;
}

template<typename T>
bool Matrix<T>::operator!= (const Matrix<T>& arg) const
{
	return !(*this == arg);
}

template<typename T>
typename Matrix<T>::MatrixRow Matrix<T>::operator[] (size_t row)
{
	INDEX_ASSERT(row < shape_.first);
	return Matrix::MatrixRow(matrix_+row*shape_.second, shape_.second);
}

template<typename T>
const typename Matrix<T>::MatrixRow Matrix<T>::operator[] (size_t row) const
{
	INDEX_ASSERT(row < shape_.first);
	return Matrix::MatrixRow(matrix_ + row*shape_.second, shape_.second);
}

//========================================================================

template<typename T>
void Matrix<T>::FreeMatrix_()
{
	delete[] matrix_;
	memory_allocated_--;
}

template<typename T>
Matrix<T>::~Matrix()
{
	DEBUG("Destructor of matrix was called!");

	if (matrix_ != nullptr)
	{ 
		FreeMatrix_();

		DEBUG("Data delited!");
		return;
	}
	else
	{
		DEBUG("But no data was delited!");
	}
}

//========================================================================

template<typename T>
T Abs(T arg)
{
	return arg >= 0 ? arg : -arg;
}

//========================================================================

#endif