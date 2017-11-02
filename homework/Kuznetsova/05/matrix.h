#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
template <typename T>
class Matrix {
   public:
    // proxy class for Matrix [][] overload, works with selected row
    class ProxyRows {
       public:
        ProxyRows(T* ptr, const size_t row, const size_t size)
            : ptr_(ptr), row_(row), size_(size) {}

        T& operator[](size_t i) {
            if (size_ <= i) {
                assert(!"index out of range");
            }
            return ptr_[row_ * size_ + i];
        }

       private:
        T* ptr_;
        const size_t row_;
        const size_t size_;
    };

    Matrix(const size_t rows, const size_t columns);

    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    Matrix(Matrix&& other);
    Matrix& operator=(Matrix&& other);

    ~Matrix();

    size_t get_rows_number();
    size_t get_columns_number();

    Matrix& operator*=(T scalar);

    std::vector<T> operator*(std::vector<T>& vector);  // multiply
                                                       // matrix with
                                                       // vector
                                                       // vector1 =
                                                       // (matrix *=
                                                       // vector)
    Matrix& operator*=(std::vector<T>& vector);

    bool operator==(const Matrix& other);

    bool operator!=(const Matrix& other);

    // part of [][] overload, returns proxy class working with selected row
    ProxyRows operator[](size_t i) {
        if (rows_ <= i) {
            assert(!"index out of range");
        }
        return ProxyRows(ptr_, i, columns_);
    }

    void print_matrix() {
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < columns_; j++) {
                printf("%lf ", ptr_[i * columns_ + j]);
            }
        }
        printf("\n");
    }

   private:
    size_t rows_;
    size_t columns_;
    T* ptr_;
};

template <typename T>
Matrix<T>::Matrix(const size_t rows, const size_t columns)
    : rows_(rows), columns_(columns) {
    ptr_ = new T[columns_ * rows_];
}

// Copy constructor
// Matrix<T> matrix2 = matrix1;
template <typename T>
Matrix<T>::Matrix(const Matrix& other)
    : rows_(other.rows_), columns_(other.columns_) {
    ptr_ = new T[columns_ * rows_];
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            ptr_[i * columns_ + j] = other.ptr_[i * columns_ + j];
        }
    }
}

// Copy operator
// matrix2 = matrix1;
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix& other) {
    if (this == &other) return *this;

    delete[] ptr_;
    rows_ = other.rows_;
    columns_ = other.columns_;
    ptr_ = new T[other.columns_ * other.rows_];
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            ptr_[i * columns_ + j] = other.ptr_[i * columns_ + j];
        }
    }

    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            ptr_[i * columns_ + j] = other.ptr_[i * columns_ + j];
        }
    }
    return *this;
}

// Move constructor
// Matrix<T> matrix2 = std::move(matrix1);
template <typename T>
Matrix<T>::Matrix(Matrix&& other) {
    rows_ = other.rows_;
    columns_ = other.columns_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
}

// Move operator
// matrix2 = std::move(matrix1);
template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix&& other) {
    if (this == &other) return *this;
    rows_ = other.rows_;
    columns_ = other.columns_;
    delete[] ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = nullptr;
    return *this;
}

template <typename T>
Matrix<T>::~Matrix() {
    delete[] ptr_;
}

template <typename T>
size_t Matrix<T>::get_rows_number() {
    return rows_;
}

template <typename T>
size_t Matrix<T>::get_columns_number() {
    return columns_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator*=(T scalar) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            ptr_[i * columns_ + j] *= scalar;
        }
    }
    return *this;
}

// multiply matrix with vector (vector1 = matrix * vector)
template <typename T>
std::vector<T> Matrix<T>::operator*(std::vector<T>& vector) {
    if (columns_ != vector.size()) {
        assert(!"incorrect multiplication: can't match sizes");
    }
    std::vector<T> result(rows_);
    auto result_it = result.begin();
    for (size_t i = 0; ((i < rows_) && (result_it != result.end()));
         i++, result_it++) {
        T sum = 0;
        auto it = vector.begin();
        for (size_t j = 0; (j < columns_) && (it != vector.end()); j++, it++) {
            sum += ptr_[i * columns_ + j] * (*it);
        }
        (*result_it) = sum;
    }
    return result;
}

// multiply matrix with vector (matrix *= vector)
template <typename T>
Matrix<T>& Matrix<T>::operator*=(std::vector<T>& vector) {
    if (columns_ != vector.size()) {
        assert(!"incorrect multiplication: can't match sizes");
    }
    Matrix tmp(*this);
    this->columns_ = 1;
    for (size_t i = 0; i < tmp.rows_; i++) {
        T sum = 0;
        auto it = vector.begin();
        for (size_t j = 0; (j < tmp.columns_) && (it != vector.end());
             j++, it++) {
            sum += tmp.ptr_[i * tmp.columns_ + j] * (*it);
        }
        ptr_[i] = sum;
    }

    return *this;
}
template <typename T>
bool Matrix<T>::operator==(const Matrix& other) {
    if (rows_ != other.rows_) return false;
    if (columns_ != other.columns_) return false;

    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            if (ptr_[i * columns_ + j] != other.ptr_[i * columns_ + j]) {
                return false;
            }
        }
    }
    return true;
}
template <typename T>
bool Matrix<T>::operator!=(const Matrix& other) {
    return !(*this == other);
}
