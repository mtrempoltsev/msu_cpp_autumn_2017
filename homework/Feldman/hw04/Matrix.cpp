#include "Matrix.h"
#include <cassert>


#include <cassert>

using namespace std;
Matrix::Matrix(int rows_, int columns_) :rows(rows_), columns(columns_) {
	assert(rows_ > 0 && columns_ > 0);
	for (size_t i = 0; i < rows; ++i) {
		matrix.push_back(Row(columns,0.0));
	}
}

Matrix::~Matrix()
{
}


unsigned int Matrix::get_rows() {
	return rows;
}

unsigned int Matrix::get_columns() {
	return columns;
}

Row& Matrix::operator[] (unsigned int row) {
	assert(row < rows);
	return matrix[row];
}

Matrix& Matrix::operator*= (int val) {
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			matrix[i][j] *= val;
		}
	}
	return *this;
}

bool Matrix::operator== (Matrix& val) {
	assert(rows == val.get_rows() && columns == val.get_columns());
	for (size_t i = 0; i < rows; ++i) {
		for (size_t j = 0; j < columns; ++j) {
			if (matrix[i][j] != val[i][j])
				return false;
		}
	}
	return true;
}

bool Matrix::operator!= (Matrix& val) {
	return !(*this == val);
}


Matrix& Matrix::operator*=(std::vector<double> src) {
	assert(src.size() == columns);
	std::vector<Row> result;
	for (size_t i = 0; i < rows; ++i) {
		double sum = 0;
		for (size_t j = 0; j < columns; ++j) {
			sum += matrix[i][j] * src[j];
		}
		result.push_back(Row(1,sum));
	}
	matrix = result;
	columns = 1;

	return *this;
}
