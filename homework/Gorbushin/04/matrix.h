#pragma once
#include <vector>

class ProxyMatrix {
public:
    // Constructor from array (in fact - row of matrix) and size of this row
    ProxyMatrix (double*, size_t);

    // get elem by index
    const double & operator[] (size_t) const;
    double & operator[] (size_t);

    ~ProxyMatrix();
private:
    size_t _size;
    double *_array;
};

class Matrix {
public:
    // Empty constructor
    Matrix();
    // By dimension
    Matrix(size_t, size_t);
    // Copy constructor
    Matrix(const Matrix &);

    // Assigment opertor
    Matrix operator=(const Matrix &);
    // For output matrix
	friend std::ostream & operator<<(std::ostream &, const Matrix &);
    // Get [i][j] element
    const ProxyMatrix operator[] (size_t) const;
    ProxyMatrix operator[] (size_t);

    // Multiply by number
    Matrix operator*= (double);
    Matrix operator* (double);

    // Multiply by vector
    Matrix operator*= (const std::vector<double> &);
    Matrix operator* (const std::vector<double> &);
    
    // Compare operator
    bool operator== (Matrix &);
    bool operator!= (Matrix &);

    // Getters
    size_t cols() const;
    size_t rows() const;
    ~Matrix();
private:
    size_t _rows, _cols;
    double *_array;
};
