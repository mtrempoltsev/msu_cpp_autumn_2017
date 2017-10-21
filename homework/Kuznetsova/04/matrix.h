#pragma once
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
class Matrix {
   public:
    // proxy class for Matrix [][] overload, works with selected row
    class ProxyRows {
       public:
        ProxyRows(double* ptr, const size_t row, const size_t size)
            : ptr_(ptr), row_(row), size_(size) {}

        double& operator[](size_t i) {
            if (size_ <= i) {
                assert(!"index out of range");
            }
            return ptr_[row_ * size_ + i];
        }

       private:
        double* ptr_;
        const size_t row_;
        const size_t size_;
    };

    Matrix(const size_t rows, const size_t columns);
   
    Matrix(const Matrix& other);    

    ~Matrix();

    size_t get_rows_number();
    size_t get_columns_number();

    Matrix& operator*=(double scalar);

    std::vector<double> operator*(std::vector<double>& vector);  // multiply
                                                                  // matrix with
                                                                  // vector
                                                                  // vector1 =
                                                                  // (matrix *=
                                                                  // vector)
    Matrix& operator*=(std::vector<double>& vector);

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
    double* ptr_;
};
