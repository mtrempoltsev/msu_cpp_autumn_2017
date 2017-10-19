#include <iostream>
#include <assert.h>
#include <math.h>
#include <vector>

using namespace std;

/*
 * proxy class with checks for correct indexing
 */
struct custom_vector {

    // precision for comparing elements of vectors
    static double constexpr comparative_precision = 0.0000001;


    custom_vector(size_t size) : data(size), size(size) {}

    custom_vector(vector<double> v) : data(v), size(v.size()) {}

    operator vector<double>() const { return data; }

    operator vector<double> &() { return data; }

    double &operator[](size_t x) {
        assert((x >= 0) && (x < size));
        return data[x];
    }

    double operator[](size_t x) const {
        assert((x >= 0) && (x < size));
        return data[x];
    }

    vector<double> operator+(vector<double> v) const {
        vector<double> result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = v[i] + data[i];
        }
        return result;
    }

    custom_vector operator*(double x) const {
        vector<double> result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = data[i] * x;
        }
        return result;
    }

    custom_vector operator*(vector<double> v) const {
        assert(v.size() == size);
        vector<double> result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = v[i] + data[i];
        }
        return result;
    }

    custom_vector operator-(vector<double> v) const {
        return (*this) * (-1);
    }

    custom_vector operator/(double x) const {
        assert(x != 0);
        return (*this) * (1.0 / x);
    }

    bool operator==(custom_vector v) const {
        for (size_t i = 0; i < size; ++i) {
            if (fabs(data[i] - v[i]) > comparative_precision)
                return false;
        }
        return true;
    }

    bool operator!=(custom_vector v) const {
        return !(*this == v);
    }

private:

    vector<double> data;
    size_t size;
};

custom_vector operator*(double x, custom_vector v) {
    return v * x;
}


struct Matrix {

    static double constexpr comparative_precision = 0.0000001;


    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols),
                                       data(rows, custom_vector(cols)) {

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                data[i][j] = 0;
        }
    }

    custom_vector &operator[](size_t i) {
        assert((i >= 0) && (i < rows));
        return data[i];
    }

    custom_vector operator[](size_t i) const {
        assert((i >= 0) && (i < rows));
        return data[i];
    }

    size_t getRows() const { return rows; }

    size_t getCols() const { return cols; }

    Matrix operator*(double x) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] * x;
        }
        return result;
    }

    Matrix operator/(double x) const {
        assert(x != 0);
        return (*this * (1 / x));
    }

    Matrix operator+(Matrix other) const {
        assert(rows == other.getRows());
        assert(cols == other.getCols());
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] + other[i][j];
        }
        return result;
    }

    Matrix operator-(Matrix other) const {
        return (*this + (other * (-1)));
    }

    Matrix operator-() const {
        return (*this * (-1));
    }

    vector<double> operator*(vector<double> v) const {
        assert(v.size() == cols);
        vector<double> result(rows);
        for (size_t i = 0; i < rows; ++i) {
            double x = 0;
            for (size_t j = 0; j < cols; ++j) {
                x += data[i][j] * v[j];
            }
            result[i] = x;
        }
        return result;
    }

    Matrix operator*(Matrix other) const {
        assert(cols == other.getRows());
        Matrix result(rows, other.getCols());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.getCols(); ++j) {
                double x = 0;
                for (size_t t = 0; t < cols; ++t) {
                    x += data[i][t] * other[t][j];
                }
                result[i][j] = x;
            }
        }
        return result;
    }

    Matrix T() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result[j][i] = data[i][j];
            }
        }
        return result;
    }

    bool operator==(Matrix const other) const {
        assert(rows == other.getRows());
        assert(cols == other.getCols());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (fabs(data[i][j] - other[i][j]) > comparative_precision)
                    return false;
            }
        }
        return true;
    }

    bool operator!=(Matrix const other) const {
        return !(*this == other);
    }

private:
    size_t rows;
    size_t cols;
    vector<custom_vector> data;
};

Matrix operator*(double x, Matrix m) {
    return m * x;
}

vector<double> operator*(vector<double> v, Matrix m) {
    return m.T() * v;
}
