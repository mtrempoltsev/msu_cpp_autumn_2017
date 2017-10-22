#include <iostream>
#include <vector>
#include <cassert>

class MatrixRow{
public:
    MatrixRow(size_t row_size, size_t col_size, size_t row, double* data):
        row_size_(row_size),
        col_size_(col_size),
        row_(row),
        data_(data){};
    ~MatrixRow(){};
    double& operator[](size_t col);
    const double& operator[](size_t col) const;
private:
    size_t row_size_;
    size_t col_size_;
    size_t row_;
    double* data_;
};

class Matrix{
public:
    Matrix(size_t row_size, size_t col_size):
        row_size_(row_size),
        col_size_(col_size),
        data_(new double[row_size * col_size]){};
    ~Matrix(){
        delete []data_;
    }
    MatrixRow operator[](size_t row);
    const MatrixRow operator[](size_t row) const;
    void set_value(double value);
    Matrix& operator*=(const std::vector<double> v);
    Matrix& operator*=(const double num);
    bool operator==(const Matrix &matr) const;
    bool operator!=(const Matrix &matr) const;
    size_t get_row_size() const;
    size_t get_col_size() const;
    friend std::ostream& operator<<(std::ostream& out, const Matrix& matr);
private:
    size_t row_size_;
    size_t col_size_;
    double* data_;
};
