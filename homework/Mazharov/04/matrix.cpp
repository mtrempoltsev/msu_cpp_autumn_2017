//
// Created by Ivan on 15.10.2017.
//

#include "matrix.h"
#include <assert.h>

Matrix::Matrix(unsigned rows, unsigned cols) {
    data.resize(rows);
    for (auto i = 0; i < rows; ++i)
        data[i].resize(cols);
    n_cols = cols;
    n_rows = rows;
}
Matrix::Matrix(const Matrix &parent) {
    data = parent.data;
    n_rows = parent.n_rows;
    n_cols = parent.n_cols;
}

unsigned Matrix::get_cols() const {
    return n_cols;
}
unsigned Matrix::get_rows() const {
    return n_rows;
}

std::vector<double> &Matrix::operator[](const unsigned row) {
    if (row >= n_rows)
        assert(!"index out of range");
    return data[row];
}
const std::vector<double> &Matrix::operator[](const unsigned row) const {
    if (row >= n_rows)
        assert(!"index out of range");
    return data[row];
}

std::vector<double> Matrix::operator*(const std::vector<double> multiplier) {
    if (multiplier.size() != n_cols)
        assert(!"index out of range");
    std::vector<double> result(n_rows);
    for (auto i = 0; i < n_rows; ++i) {
        for (auto j = 0; j < n_cols; ++j) {
            result[i] += data[i][j] * multiplier[j];
        }
    }
    return result;
}
Matrix Matrix::operator*(const double &multiplier) {
    Matrix result(n_rows, n_cols);
    for (auto i = 0; i < n_rows; ++i) {
        for (auto j = 0; j < n_cols; ++j) {
            result[i][j] = data[i][j] * multiplier;
        }
    }
    return result;
}
bool Matrix::operator==(const Matrix &right) {
    if ( (n_rows != right.n_rows) | (n_cols != right.n_cols))
        return 0;
    for (auto i = 0; i < n_rows; ++i) {
        for (auto j = 0; j < n_cols; ++j) {
            if (data[i][j] != right[i][j])
                return 0;
        }
    }
    return 1;
}
bool Matrix::operator!=(const Matrix &right) {
    return !(*this == right);
}