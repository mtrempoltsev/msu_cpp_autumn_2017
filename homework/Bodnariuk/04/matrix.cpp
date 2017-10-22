// Vasilii Bodnariuk

#include "matrix.hpp"
#include <stdio.h>
#include <iostream>
#include <string.h>

Elem::Elem(double* pointer) {
    _pointer = pointer;
}

double Elem::operator=(const double value) {
    *_pointer = value;
    return value;
}

Elem::operator const double& () const {
        return *_pointer;
}

Row::Row(double* start, size_t row_size) {
    _start = start;
    _row_size = row_size;
}

Elem Row::operator[](size_t i) {
    if(i >= 0 && i < _row_size) {
        return Elem(_start + i);
    } else {
        throw ERR_ROW_OUT_OF_RANGE;
    }
}

Matrix::Matrix(size_t rows, size_t cols) {
    _rows = rows;
    _cols = cols;
    _values = new double[rows * cols];

}

Matrix::~Matrix() {
    delete[] this->_values;
    this->_values = NULL;
}

size_t Matrix::rows() {
    return _rows;
}

size_t Matrix::cols() {
    return _cols;
}

Matrix& Matrix::operator= (Matrix other) {
    if (this == &other) {
        return *this;

    }
    delete[] this->_values;

    this->_values = other._values;
    this->_cols = other._cols;
    this->_rows = other._rows;

    other._values = NULL;
    return *this;
}

Matrix& Matrix::operator*(std::vector<double> v) {
    auto vec_len = v.size();
    if (_cols != 1) {
        throw ERR_DIMS_MISMATCH;
    }

    Matrix* result = new Matrix(_rows, vec_len);
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < vec_len; ++j) {
            (*result)[i][j] = (*this)[i][0] * v[i];
        }
    }
    return *result;
}

Matrix& Matrix::operator*=(std::vector<double> v) {
    *this = (*this) * v;
    return *this;
}

Matrix& Matrix::operator*=(double num) {
    *this = (*this) * num;
    return *this;
}

Matrix& Matrix::operator*(double num) {
    Matrix* result = new Matrix(_rows, _cols);
    for (size_t i = 0; i < _rows; ++i) {
        for (size_t j = 0; j < _cols; ++j) {
            (*result)[i][j] = (*this)[i][j] * num;
        }
    }
    return *result;
}

bool Matrix::operator==(Matrix& other) {
    bool rows_ok = (this->_rows == other._rows);
    bool cols_ok = (this->_cols == other._cols);
    if(rows_ok && cols_ok) {
        for(size_t i = 0; i < this->_rows * this->_cols; ++i) {
            if(this->_values[i] != other._values[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

bool Matrix::operator!=(Matrix& other) {

    return !(*this == other);
}

Row Matrix::operator[](size_t i) {
    if(i >= 0 && i < _rows) {
        return Row(_values + i * _cols, _cols);
    } else {
        throw ERR_ROW_OUT_OF_RANGE;
    }
}

Matrix operator* (std::vector<double> v, Matrix& m) {
    auto cols = m.cols();
    auto rows = m.rows();
    auto vec_len = v.size();
    if(rows != 1) {
        throw ERR_DIMS_MISMATCH;
    }
    Matrix* result = new Matrix(vec_len, cols);
    for (size_t i = 0; i < vec_len; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            (*result)[i][j] = v[i] * m[0][j];
        }
    }
    return *result;
}

Matrix operator* (double num, Matrix& m) {
    return m * num;
}
