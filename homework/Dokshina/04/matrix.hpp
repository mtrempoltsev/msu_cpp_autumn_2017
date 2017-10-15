#pragma once

#include <iostream>
#include <initializer_list>
#include <vector>

using namespace std;

class MatrixRow {
public:
    MatrixRow(double* ptr, size_t _cols);
    double& operator[](size_t j);
private:
    double *row;
    size_t cols_num;
};

class Matrix {
public:
    Matrix(size_t _rows = 1, size_t _cols = 1);
    Matrix(const Matrix& other);
    Matrix(initializer_list<double> store);
    ~Matrix();
    size_t get_rows_num();
    size_t get_cols_num();
    MatrixRow operator[](size_t i);
    bool operator==(const Matrix& other);
    bool operator!=(const Matrix& other);
    Matrix& operator*=(double a);
    Matrix& operator*=(vector<double> a);
    friend ostream& operator<<(ostream& out, const Matrix& value);

private:
    size_t rows_num;
    size_t cols_num;
    double* values;
};
