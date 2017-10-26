// Vasilii Bodnariuk

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>
#include <sys/types.h>

enum matrix_errors {
    ERR_ROW_OUT_OF_RANGE = 0,
    ERR_COL_OUT_OF_RANGE,
    ERR_DIMS_MISMATCH,
};

template <typename elem_type>
class Elem {
public:
    Elem(elem_type* pointer) {
        _pointer = pointer;
    }

    elem_type operator=(const elem_type value) {
        *_pointer = value;
        return value;
    }

    operator const elem_type& () const {
            return *_pointer;
    }private:
    elem_type* _pointer;
};

template <typename elem_type>
class Row {
public:
    Row(elem_type* start, size_t row_size) {
        _start = start;
        _row_size = row_size;
    }

    Elem<elem_type> operator[](size_t i) {
        if(i < _row_size) {
            return Elem<elem_type>(_start + i);
        } else {
            throw ERR_ROW_OUT_OF_RANGE;
        }
    }
private:
    size_t _row_size;
    elem_type* _start;
};

template <typename elem_type>
class Matrix {
public:
    Matrix(size_t rows, size_t cols) {
        _rows = rows;
        _cols = cols;
        _values = new elem_type[rows * cols];

    }

    Matrix(Matrix&& other) {
        this->_values = other._values;
        this->_cols = other._cols;
        this->_rows = other._rows;

        other._values = NULL;
    }

    ~Matrix() {
        delete[] this->_values;
        this->_values = NULL;
    }

    size_t rows() {
        return _rows;
    }

    size_t cols() {
        return _cols;
    }

    Matrix& operator= (Matrix&& other) {
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

    Matrix& operator*(std::vector<elem_type> v) {
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

    Matrix& operator*=(std::vector<elem_type> v) {
        *this = std::move((*this) * v);
        return *this;
    }

    Matrix& operator*=(elem_type num) {
        *this = std::move((*this) * num);
        return *this;
    }

    Matrix& operator*(elem_type num) {
        Matrix* result = new Matrix(_rows, _cols);
        for (size_t i = 0; i < _rows; ++i) {
            for (size_t j = 0; j < _cols; ++j) {
                (*result)[i][j] = (*this)[i][j] * num;
            }
        }
        return *result;
    }

    bool operator==(Matrix& other) {
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

    bool operator!=(Matrix& other) {

        return !(*this == other);
    }

    Row<elem_type> operator[](size_t i) {
        if(i < _rows) {
            return Row<elem_type>(_values + i * _cols, _cols);
        } else {
            throw ERR_ROW_OUT_OF_RANGE;
        }
    }

private:
    size_t _rows;
    size_t _cols;
    elem_type* _values;
};
