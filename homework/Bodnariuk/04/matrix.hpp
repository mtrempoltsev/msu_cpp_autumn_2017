// Vasilii Bodnariuk

#include <vector>
#include <stdio.h>
#include <sys/types.h>

enum matrix_errors {
    ERR_ROW_OUT_OF_RANGE = 0,
    ERR_COL_OUT_OF_RANGE,
    ERR_DIMS_MISMATCH,
};

class Elem {
public:
    Elem(double* pointer);
    double operator=(const double value);
    operator const double& () const;
private:
    double* _pointer;
};

class Row {
public:
    Row(double* start, size_t row_size);
    Elem operator[](size_t i);
private:
    size_t _row_size;
    double* _start;
};

class Matrix {
public:
    Matrix(size_t rows, size_t cols);
    ~Matrix();
    size_t rows();
    size_t cols();
    Row operator[](size_t i);
    Matrix& operator=(Matrix other);

    Matrix& operator*(std::vector<double> v);
    Matrix& operator*=(std::vector<double> a);

    Matrix& operator*(double num);
    Matrix& operator*=(double num);

    bool operator==(Matrix& other);
    bool operator!=(Matrix& other);

private:
    size_t _rows;
    size_t _cols;
    double* _values;
};

Matrix operator* (std::vector<double> v, Matrix& m);
Matrix operator* (double num, Matrix& m);
