#include "Matrix.h"
#include <string>
#include <iostream>

Matrix::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
	if ((rows == 0) || (cols == 0)) {
		throw std::runtime_error(std::string("[Matrix]: can not create matrix of size [") + \
			std::to_string(rows) + std::string(", ") + std::to_string(cols) + std::string("]"));
	}

	content = new double*[rows];

    for (size_t i = 0; i < rows; i++) {
        content[i] = new double[cols];
    }
}

Matrix::Matrix(const Matrix& other) : Matrix(other.getRowsN(), other.getColsN()) {
	for (size_t row = 0; row < rows; ++row) {
		for (size_t col = 0; col < cols; ++col) {
			content[row][col] = other.content[row][col];
		}
	}
}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> list) : Matrix(list.size(), list.begin()->size()) {
	for(auto rowIt = list.begin(); rowIt != list.end(); ++rowIt) {
		if (rowIt->size() != cols) {
			throw std::runtime_error("[Matrix]: each row should have the same amount of elements");
		}
		
		for(auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
			content[rowIt - list.begin()][colIt - rowIt->begin()] = *colIt;
		}
	}
}

Matrix::~Matrix() {
	for (size_t i = 0; i < rows; ++i) {
		delete[] content[i];
	}
	delete[] content;
}



Matrix& Matrix::operator=(const Matrix& other) {
	if (this == &other) {
		return *this;
	}

	if ((other.getRowsN() != rows) || (other.getColsN() != cols)) {
		throw std::runtime_error("[Matrix]: dimensions don't match");
	}

	for (size_t row = 0; row < rows; ++row) {
		for (size_t col = 0; col < cols; ++col) {
			content[row][col] = other.content[row][col];
		}
	}
	return *this;
}

Slice Matrix::operator[](size_t row) {
	if (row >= rows) {
		throw std::runtime_error(std::string("[Matrix]: invalid index: ") + std::to_string(row));
	}
	return Slice(content, row, cols);
}

const Slice Matrix::operator[](size_t row) const {
	if (row >= rows) {
		throw std::runtime_error(std::string("[Matrix]: invalid index: ") + std::to_string(row));
	}
	return Slice(content, row, cols);
}

Matrix Matrix::operator*(double val) const {
	Matrix res(*this);
	for (size_t row = 0; row < rows; ++row) {
		for (size_t col = 0; col < cols; ++col) {
			res.content[row][col] = content[row][col] * val;
		}
	}
	return res;
}

Matrix& Matrix::operator*=(double val) {
	for (size_t row = 0; row < rows; ++row) {
		for (size_t col = 0; col < cols; ++col) {
			content[row][col] *= val;
		}
	}

	return *this;
}

std::vector<double> Matrix::operator*(const std::vector<double>& vec) const {
	if (vec.size() != cols) {
		throw std::runtime_error("[Matrix]: vector should have number of elements equal to the number of columns in matrix");
	}

	std::vector<double> res(rows);
	double element;

	for (size_t row = 0; row < rows; ++row) {
		element = 0;
		for (size_t col = 0; col < cols; ++col) {
			element += content[row][col] * vec[col];
		}
		res[row] = element;
	}

	return res;
}

bool Matrix::operator==(const Matrix& other) const {
	if ((other.getRowsN() != rows) || (other.getColsN() != cols)) {
		return false;
	}

	for (size_t row = 0; row < rows; ++row) {
		for (size_t col = 0; col < cols; ++col) {
			if (other.content[row][col] != content[row][col]) {
				return false;
			}
		}
	}
	return true;
}

bool Matrix::operator!=(const Matrix& other) const {
	return !(*this == other);
}



double Matrix::at(size_t row, size_t col) const {
	if ((row >= rows) || (col >= cols)) {
		throw std::runtime_error(std::string("[Matrix]: invalid index: [") + \
			std::to_string(row) + std::string(", ") + std::to_string(col) + std::string("]"));
	}
	return content[row][col];
}

size_t Matrix::getColsN() const {
	return cols;
}

size_t Matrix::getRowsN() const {
	return rows;
}