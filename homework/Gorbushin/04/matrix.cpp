#include <vector>
#include <iostream>
#include <cassert> 
#include "matrix.h"

// ProxyMatrix class implementation
ProxyMatrix::ProxyMatrix (double *array, size_t size) {
    _array = array;
    _size = size;
}
const double & ProxyMatrix::operator[] (size_t j) const {
    if (j >= _size) {
        assert(!"index out of range");
    }

    return _array[j];
}
double & ProxyMatrix::operator[] (size_t j) {
    if (j >= _size) {
        assert(!"index out of range");
    }

    return _array[j];
}
ProxyMatrix::~ProxyMatrix() {}


// Matrix class implementation
Matrix::Matrix(): _rows(0), _cols(0), _array(nullptr) {}
Matrix::Matrix(size_t r, size_t c): _rows(r), _cols(c) {
    _array = new double[r * c];
}
Matrix::Matrix(const Matrix & copy_from) {
    _rows = copy_from._rows;
    _cols = copy_from._cols;
    _array = new double[_rows * _cols];
    for (size_t i = 0; i < _rows * _cols; i++) {
        _array[i] = copy_from._array[i];
    }
}
Matrix Matrix::operator=(const Matrix & move_from) {
    if (this != &move_from) {
        delete _array;
    }
    _rows = move_from._rows;
    _cols = move_from._cols;
    _array = new double[_rows * _cols];
    for (size_t i = 0; i < _rows * _cols; i++) {
        _array[i] = move_from._array[i];
    }
    return *this;
}
std::ostream & operator<<(std::ostream & out, const Matrix & matrix) {
    for (size_t i = 0; i < matrix._rows; i++) {
        for (size_t j = 0; j < matrix._cols; j++) {
            out << matrix._array[i * matrix._cols + j] << " ";
        }
        out << std::endl;
    }
    return out;
}
const ProxyMatrix Matrix::operator[] (size_t row_num) const {
    if (row_num >= _rows) {
        assert(!"index out of range");
    }
 
    return ProxyMatrix(_array + (row_num * _cols), _cols);
}

ProxyMatrix Matrix::operator[] (size_t row_num) {
    if (row_num >= _rows) {
        assert(!"index out of range");
    }

    return ProxyMatrix(_array + (row_num * _cols), _cols);
}

Matrix Matrix::operator*= (double k) {
    for (size_t i = 0; i < _rows * _cols; i++) {
        this->_array[i] *= k;
    }
    return *this;
}

Matrix Matrix::operator* (double k) {
    Matrix res(*this);
    res *= k;
    return res;
}

Matrix Matrix::operator*= (const std::vector<double> &v) {
    if (_cols != v.size()) {
        assert(!"Dimension of vector is not equal columns in matrix");
    }

    double * new_array = new double[_rows];
    for (size_t i = 0; i < _rows; i++) {
        double to_add = 0;
        for (size_t j = 0; j < _cols; j++) {
            to_add += _array[i * _cols + j] * v[j];
        }
        new_array[i] = to_add;
    }
    delete _array;
    _array = new_array;
    _cols = 1;
    return *this;
}

Matrix Matrix::operator* (const std::vector<double> &v) {
    if (_cols != v.size()) {
        assert(!"Dimension of vector is not equal columns in matrix");
    }

    Matrix res(*this);
    res *= v;
    return res;
}

bool Matrix::operator== (Matrix & matrix) {
    if (_cols != matrix._cols || _rows != matrix._rows) {
        return false;
    }

    for (size_t i = 0; i < _rows * _cols; i++) {
        if (_array[i] != matrix._array[i]) {
            return false;
        }
    }
    return true;
}

bool Matrix::operator!= (Matrix & matrix) {
    return !(*this == matrix);
}

size_t Matrix::cols() const {
    return _cols;
}
size_t Matrix::rows() const {
    return _rows;
}
Matrix::~Matrix() {
    delete _array;
}
