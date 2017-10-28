#include <assert.h>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <vector>

using namespace std;

/*
 * proxy class with checks for correct indexing
 */
template<typename T>
struct custom_vector {


    custom_vector<T>(size_t size) : data(size), size(size) {}

    custom_vector<T>(vector<T> v) : data(v), size(v.size()) {}

    operator vector<T>() const { return data; }

    operator vector<T> &() { return data; }

    T &operator[](size_t x) {
        if ((x < 0) || (x >= size)){
            throw out_of_range("Exception: index out of range");
        }
        return data[x];
    }

    T operator[](size_t x) const {
        if ((x < 0) || (x >= size)){
            throw out_of_range("Exception: index out of range");
        }
        return data[x];
    }

    vector<T> operator+(vector<T> v) const {
        vector<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = v[i] + data[i];
        }
        return result;
    }

    custom_vector operator*(T x) const {
        vector<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = data[i] * x;
        }
        return result;
    }

    custom_vector operator*(vector<T> v) const {
        if (v.size() != size){
            throw invalid_argument("Exception: wrong dimensions");
        }
        vector<T> result(size);
        for (size_t i = 0; i < size; ++i) {
            result[i] = v[i] + data[i];
        }
        return result;
    }

    custom_vector operator-(vector<T> v) const {
        return (*this) * (-1);
    }

    custom_vector operator/(T x) const {
        if (x == 0){
            throw overflow_error("Exception: zero division");
        }
        return (*this) * (1.0 / x);
    }

    bool operator==(custom_vector v) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != v[i])
                return false;
        }
        return true;
    }

    bool operator!=(custom_vector v) const {
        return !(*this == v);
    }

private:

    vector<T> data;
    size_t size;
};

template<typename T>
custom_vector<T> operator*(T x, custom_vector<T> v) {
    return v * x;
}


template<typename T>
struct Matrix {

    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols),
                                       data(rows, custom_vector<T>(cols)) {}

    Matrix(const Matrix &other) : rows(other.getRows()), cols(other.getCols()),
                                  data(rows, custom_vector<T>(cols)) {

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                data[i][j] = other[i][j];
        }
    }

    Matrix(Matrix &&other) : rows(other.getRows()), cols(other.getCols()),
                             data(rows, custom_vector<T>(cols)) {

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                data[i][j] = std::move(other[i][j]);
        }
    }

    Matrix &operator=(const Matrix &other) {
        rows = other.getRows();
        cols = other.getCols();
        vector<custom_vector<T>> result(rows, custom_vector<T>(cols));
        data = result;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                data[i][j] = other[i][j];
        }
        return *this;
    }

    Matrix &operator=(Matrix &&other) {
        rows = other.getRows();
        cols = other.getCols();
        vector<custom_vector<T>> result(rows, custom_vector<T>(cols));
        data = result;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                data[i][j] = std::move(other[i][j]);
        }
        return *this;
    }

    custom_vector<T> &operator[](size_t i) {
        if ((i < 0) || (i >= rows)){
            throw out_of_range("Exception: index out of range");
        }
        return data[i];
    }

    custom_vector<T> operator[](size_t i) const {
        if ((i < 0) || (i >= rows)){
            throw out_of_range("Exception: index out of range");
        }
        return data[i];
    }

    size_t getRows() const { return rows; }

    size_t getCols() const { return cols; }

    Matrix operator*(T x) const {
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] * x;
        }
        return result;
    }

    Matrix operator/(T x) const {
        if (x == 0){
            throw overflow_error("Exception: zero division");
        }
        return (*this * (1 / x));
    }

    Matrix operator+(Matrix<T> other) const {
        if ((rows != other.getRows()) || (cols != other.getCols())){
            throw invalid_argument("Exception: wrong dimensions");
        }
        Matrix result(rows, cols);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j)
                result[i][j] = data[i][j] + other[i][j];
        }
        return result;
    }

    Matrix operator-(Matrix<T> other) const {
        return (*this + (other * (-1)));
    }

    Matrix operator-() const {
        return (*this * (-1));
    }

    vector<T> operator*(vector<T> v) const {
        if (v.size() != cols){
            throw invalid_argument("Exception: wrong dimensions");
        }
        vector<T> result(rows);
        for (size_t i = 0; i < rows; ++i) {
            T x = 0;
            for (size_t j = 0; j < cols; ++j) {
                x += data[i][j] * v[j];
            }
            result[i] = x;
        }
        return result;
    }

    Matrix operator*(Matrix<T> other) const {
        if (cols != other.getRows()){
            throw invalid_argument("Exception: wrong dimensions");
        }
        Matrix result(rows, other.getCols());
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < other.getCols(); ++j) {
                T x = 0;
                for (size_t t = 0; t < cols; ++t) {
                    x += data[i][t] * other[t][j];
                }
                result[i][j] = x;
            }
        }
        return result;
    }

    Matrix Transpose() const {
        Matrix result(cols, rows);
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                result[j][i] = data[i][j];
            }
        }
        return result;
    }

    bool operator==(Matrix const other) const {
        if ((rows != other.getRows()) || (cols != other.getCols())){
            throw invalid_argument("Exception: wrong dimensions");
        }
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                if (data[i][j] != other[i][j])
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
    vector<custom_vector<T>> data;
};

template<typename T>
Matrix<T> operator*(double x, Matrix<T> m) {
    return m * x;
}

template<typename T>
vector<T> operator*(vector<T> v, Matrix<T> m) {
    return m.Transpose() * v;
}
