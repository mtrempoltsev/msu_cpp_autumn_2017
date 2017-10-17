//
// Created by Ivan on 15.10.2017.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <ostream>
#include <vector>

/*Matrix class. Supported operations:
 * Get number of cols/rows
 * Get element by index
 * Multiply by vector
 * Multiply by number
 * Matrix comparison*/

class Matrix {
public:
    //Constructors
    Matrix(unsigned rows, unsigned cols);
    Matrix(const Matrix &parent);

    //Simple operations
    unsigned get_rows() const;
    unsigned get_cols() const;

    //Get an element (+ const version)
    std::vector<double> &operator[](unsigned row);
    const std::vector<double> &operator[](unsigned row) const;

    //Overloaded operators
    std::vector<double> operator*(std::vector<double> multiplier);
    Matrix operator*(const double &multiplier);
    bool operator==(const Matrix &right);
    bool operator!=(const Matrix &right);

private:
    std::vector<std::vector<double> > data;
    unsigned n_cols;
    unsigned n_rows;
};

#endif //MATRIX_MATRIX_H