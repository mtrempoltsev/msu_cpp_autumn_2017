#include "matrix.h"
Matrix::Matrix(const size_t rows, const size_t columns)
    : rows_(rows), columns_(columns) {
    ptr_ = new double[columns_ * rows_];
}
Matrix::Matrix(const Matrix& other) : rows_(other.rows_), columns_(other.columns_) {
    ptr_ = new double[columns_ * rows_];
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            ptr_[i * columns_ + j] =other.ptr_[i * columns_ + j];
        }
    }
}
Matrix::~Matrix() { delete[] ptr_; }

size_t Matrix::get_rows_number() { return rows_; }

size_t Matrix::get_columns_number() { return columns_; }

Matrix& Matrix::operator*=(double scalar) {
    for (size_t i = 0; i < rows_; i++) {
        for (size_t j = 0; j < columns_; j++) {
            ptr_[i * columns_ + j] *= scalar;
        }
    }
    return *this;
}

// multiply matrix with vector (vector1 = matrix * vector)
std::vector<double> Matrix::operator*(std::vector<double>& vector) {
    if (columns_ != vector.size()) {
        assert(!"incorrect multiplication: can't match sizes");
    }
    std::vector<double> result(rows_);
    auto result_it = result.begin();
    for (size_t i = 0; ((i < rows_) && (result_it != result.end()));
         i++, result_it++) {
        double sum = 0;
        auto it = vector.begin();
        for (size_t j = 0; (j < columns_) && (it != vector.end()); j++, it++) {
            sum += ptr_[i * columns_ + j] * (*it);
        }
        (*result_it) = sum;
    }
    return result;
}

// multiply matrix with vector (matrix *= vector)
Matrix& Matrix::operator*=(std::vector<double>& vector) {
    if (columns_ != vector.size()) {
        assert(!"incorrect multiplication: can't match sizes");
    }
    Matrix tmp(*this);
    this -> columns_ = 1;
    for (size_t i = 0; i < tmp.rows_;
         i++) {
        double sum = 0;
        auto it = vector.begin();
        for (size_t j = 0; (j < tmp.columns_) && (it != vector.end()); j++, it++) {
            sum += tmp.ptr_[i * tmp.columns_ + j] * (*it);
        }
        ptr_[i] = sum;
    }
    
    
    return *this;
}

bool Matrix::operator==(const Matrix& other) {
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

bool Matrix::operator!=(const Matrix& other) { return !(*this == other); }
