//
// Created by Ivan on 15.10.2017.
//

#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <ostream>
#include <vector>
#include <assert.h>

/*Matrix class. Supported operations:
 * Get number of cols/rows
 * Get element by index
 * Multiply by vector
 * Multiply by number
 * Matrix comparison*/

template<typename T>
class Matrix {
public:
    //Constructors
    Matrix() {
        data;
        n_cols = 0;
        n_rows = 0;
    };

    Matrix(unsigned rows, unsigned cols) {
        data.resize(rows);
        for (auto i = 0; i < rows; ++i)
            data[i].resize(cols);
        n_cols = cols;
        n_rows = rows;
    };

    Matrix(const Matrix &parent) {
        data = parent.data;
        n_rows = parent.n_rows;
        n_cols = parent.n_cols;
    };

    Matrix(Matrix &&moved) {
        data = moved.data;
        moved.data = std::vector<std::vector<T> >();
        n_rows = moved.n_rows;
        n_cols = moved.n_cols;
    }

    //Simple operations
    unsigned get_rows() const {
        return n_rows;
    };

    unsigned get_cols() const {
        return n_cols;
    };

    //Get an element (+ const version)
    std::vector<T> &operator[](unsigned row) {
        if (row >= n_rows)
            assert(!"index out of range");
        return data[row];
    };

    const std::vector<T> &operator[](unsigned row) const {
        if (row >= n_rows)
            assert(!"index out of range");
        return data[row];
    };

    //Overloaded operators
    Matrix &operator=(const Matrix &right) {
        if (this == &right)
            return *this;

        unsigned new_rows = right.get_rows();
        unsigned new_cols = right.get_cols();

        data.resize(new_rows);
        for (unsigned i = 0; i < data.size(); i++) {
            data[i].resize(new_cols);
        }

        for (unsigned i = 0; i < new_rows; i++) {
            for (unsigned j = 0; j < new_cols; j++) {
                data[i][j] = right[i][j];
            }
        }
        n_rows = new_rows;
        n_cols = new_cols;

        return *this;
    }

    Matrix &operator=(Matrix &&moved) {

        if (this == &moved) {
            return *this;
        }

        unsigned new_rows = moved.get_rows();
        unsigned new_cols = moved.get_cols();

        data.resize(new_rows);
        for (unsigned i = 0; i < data.size(); i++) {
            data[i].resize(new_cols);
        }

        for (unsigned i = 0; i < new_rows; i++) {
            for (unsigned j = 0; j < new_cols; j++) {
                data[i][j] = moved[i][j];
            }
        }

        moved.data = std::vector<std::vector<T> >();
        n_rows = new_rows;
        n_cols = new_cols;

        return *this;
    }

    std::vector<T> operator*(std::vector<T> multiplier) {
        if (multiplier.size() != n_cols)
            assert(!"index out of range");
        std::vector<T> result(n_rows);
        for (auto i = 0; i < n_rows; ++i) {
            for (auto j = 0; j < n_cols; ++j) {
                result[i] += data[i][j] * multiplier[j];
            }
        }
        return result;
    };

    Matrix operator*(const T &multiplier) {
        Matrix result(n_rows, n_cols);
        for (auto i = 0; i < n_rows; ++i) {
            for (auto j = 0; j < n_cols; ++j) {
                result[i][j] = data[i][j] * multiplier;
            }
        }
        return result;
    };

    bool operator==(const Matrix &right) {
        if ((n_rows != right.n_rows) | (n_cols != right.n_cols))
            return false;
        for (auto i = 0; i < n_rows; ++i) {
            for (auto j = 0; j < n_cols; ++j) {
                if (data[i][j] != right[i][j])
                    return false;
            }
        }
        return true;
    };

    bool operator!=(const Matrix &right) {
        return !(*this == right);
    };

private:
    std::vector<std::vector<T> > data;
    unsigned n_cols;
    unsigned n_rows;
};

#endif //MATRIX_MATRIX_H