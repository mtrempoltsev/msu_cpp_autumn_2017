#pragma once
#include <vector>
#include <cassert>
#include "Row.h"

template <class T>
class Matrix
{
public:
	Matrix(std::size_t rows, std::size_t cols) : rows_(rows), cols_(cols)
	{
		for (std::size_t i = 0; i < rows_; ++i)
		{
			Row<T> r(cols);
			matrix_.push_back(r);
		}
	}
	Matrix(const Matrix& m)
	{
		rows_ = m.rows_;
		cols_ = m.cols_;
		for (size_t i = 0; i < m.matrix_.size(); ++i)
		{
			Row<T> r(m.matrix_[i]);
			matrix_.push_back(r);
		}
	}
	Matrix& operator=(const Matrix& m)
	{
		if (this == &m)
		{
			return *this;
		}
		rows_ = m.rows_;
		cols_ = m.cols_;
		matrix_.clear();
		for (size_t i = 0; i < m.matrix_.size(); ++i)
		{
			Row<T> r(m.matrix_[i]);
			matrix_.push_back(r);
		}
		return *this;
	}
	Matrix(Matrix&& m)
	{
		rows_ = std::move(m.rows_);
		cols_ = std::move(m.cols_);
		for (size_t i = 0; i < m.matrix_.size(); ++i)
		{
			Row<T> r = std::move(m.matrix_[i]);
			matrix_.push_back(r);
		}
	}
	Matrix& operator=(Matrix&& m)
	{
		if (this == &m)
		{
			return *this;
		}
		rows_ = std::move(m.rows_);
		cols_ = std::move(m.cols_);
		matrix_.clear();
		for (size_t i = 0; i < m.matrix_.size(); ++i)
		{
			Row<T> r = std::move(m.matrix_[i]);
			matrix_.push_back(r);
		}
		return *this;
	}
	std::size_t GetRows() const { return rows_; }
	std::size_t GetCols() const { return cols_; }
	Row<T>& operator[](std::size_t i)
	{
		assert(i < matrix_.size());
		return matrix_[i];
	}
	Matrix operator*=(T a)
	{
		for (std::size_t i = 0; i < rows_; ++i)
			for (std::size_t j = 0; j < cols_; ++j)
				matrix_[i][j] *= a;
		return *this;
	}
	Matrix operator*=(std::vector<T> v)
	{
		assert(v.size() == cols_);
		Matrix m(rows_, 1);
		for (std::size_t i = 0; i < rows_; ++i)
		{
			T s = 0;
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
	bool operator==(Matrix m) const
	{
		if (rows_ != m.GetRows() || cols_ != m.GetCols())
			return false;
		for (std::size_t i = 0; i < rows_; ++i)
			for (std::size_t j = 0; j < cols_; ++j)
				if (matrix_[i][j] != m[i][j])
					return false;
		return true;
	}
	bool operator!=(Matrix m) const
	{
		return !((*this) == m);
	}
	~Matrix() {};

private:
	std::size_t rows_;
	std::size_t cols_;
	std::vector<Row<T>> matrix_;
};
