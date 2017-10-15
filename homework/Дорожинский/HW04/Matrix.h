#pragma once
#include <vector>
#include "Slice.h"
#include <stdexcept>

class Matrix {
public:
	size_t getColsN() const;
	size_t getRowsN() const;
	double at(size_t row, size_t col) const;

	Slice operator[](size_t row);
	const Slice operator[](size_t row) const;
	Matrix& operator=(const Matrix& other);
	Matrix operator*(double val) const;
	Matrix& operator*=(double val);
	std::vector<double> operator*(const std::vector<double>& vec) const;
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;

	Matrix(size_t rows, size_t cols);
	Matrix(const Matrix& other);
	Matrix(std::initializer_list<std::initializer_list<double>> list);
	Matrix() = delete;
	~Matrix();
private:
	const size_t cols;
	const size_t rows;

	double** content;
};