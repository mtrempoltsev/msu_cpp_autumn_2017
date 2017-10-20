#pragma once
#include "Slice.h"
#include <vector>
#include <stdexcept>
#include <iostream>

template <typename T>
class Matrix {
public:
    size_t getColsN() const {
        return cols;
    }

    size_t getRowsN() const {
        return rows;
    }    

    T at(size_t row, size_t col) const {
    	validate();

        if (content == nullptr) {
            throw std::runtime_error("[Matrix]: matrix has been moved from here");
        }
    
        if ((row >= rows) || (col >= cols)) {
            throw std::runtime_error(std::string("[Matrix]: invalid index: [") + \
                std::to_string(row) + std::string(", ") + std::to_string(col) + std::string("]"));
        }
        return content[row][col];
    }

    Slice<T> operator[](size_t row) {
        validate();
    
        if (row >= rows) {
            throw std::runtime_error(std::string("[Matrix]: invalid index: ") + std::to_string(row));
        }
        return Slice<T>(content[row], cols);
    }

    const Slice<T> operator[](size_t row) const {
        validate();
    
        if (row >= rows) {
            throw std::runtime_error(std::string("[Matrix]: invalid index: ") + std::to_string(row));
        }
        return Slice<T>(content[row], cols);
    }

    Matrix& operator=(const Matrix& other) {
        validate();
        other.validate();
    
        if (this == &other) {
            return *this;
        }
    
        if ((other.getRowsN() != rows) || (other.getColsN() != cols)) {
            throw std::runtime_error("[Matrix]: dimensions don't match");
        }
    
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                content[row][col] = other.content[row][col];
            }
        }
        return *this;
    }

    Matrix& operator=(Matrix&& other) {
        validate();
        other.validate();
    
        if (this == &other) {
            return *this;
        }
    
        if ((other.getRowsN() != rows) || (other.getColsN() != cols)) {
            throw std::runtime_error("[Matrix]: dimensions don't match");
        }
    
        deleteContent();
    
        content = other.content;
        other.content = nullptr;
        return *this;
    }

    Matrix operator*(const T& val) const {
        validate();
    
        Matrix res(*this);
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                res.content[row][col] = content[row][col] * val;
            }
        }
        return res;
    }

    Matrix& operator*=(const T& val) {
        validate();
    
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                content[row][col] *= val;
            }
        }
    
        return *this;
    }

    std::vector<T> operator*(const std::vector<T>& vec) const {
        validate();
    
        if (vec.size() != cols) {
            throw std::runtime_error("[Matrix]: vector should have number of elements equal to the number of columns in matrix");
        }
    
        std::vector<T> res(rows);
        T element;
    
        for (size_t row = 0; row < rows; ++row) {
            element = 0;
            for (size_t col = 0; col < cols; ++col) {
                element += content[row][col] * vec[col];
            }
            res[row] = element;
        }
    
        return res;
    }

    bool operator==(const Matrix& other) const {
        if ((other.getRowsN() != rows) || (other.getColsN() != cols)) {
            return false;
        }
    
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                if (other.content[row][col] != content[row][col]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }


    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
        if ((rows == 0) || (cols == 0)) {
            throw std::runtime_error(std::string("[Matrix]: can not create matrix of size [") + \
                std::to_string(rows) + std::string(", ") + std::to_string(cols) + std::string("]"));
        }
    
        content = new T*[rows];
    
        for (size_t i = 0; i < rows; i++) {
            content[i] = new T[cols];
        }
    }

    Matrix(const Matrix& other) : Matrix(other.getRowsN(), other.getColsN()) {
        other.validate();
    
        for (size_t row = 0; row < rows; ++row) {
            for (size_t col = 0; col < cols; ++col) {
                content[row][col] = other.content[row][col];
            }
        }
    }

    Matrix(Matrix&& other) : rows(other.rows), cols(other.cols) {
        other.validate();
    
        content = other.content;
        other.content = nullptr;
    }

    Matrix(std::initializer_list<std::initializer_list<double>> list) : Matrix(list.size(), list.begin()->size()) {
        for(auto rowIt = list.begin(); rowIt != list.end(); ++rowIt) {
            if (rowIt->size() != cols) {
                throw std::runtime_error("[Matrix]: each row should have the same amount of elements");
            }
            
            for(auto colIt = rowIt->begin(); colIt != rowIt->end(); ++colIt) {
                content[rowIt - list.begin()][colIt - rowIt->begin()] = *colIt;
            }
        }
    }

    Matrix() = delete;

    ~Matrix() {
        deleteContent();
    }
private:
    const size_t cols;
    const size_t rows;

    T** content;

    void deleteContent() {
        if (content != nullptr) {
            for (size_t i = 0; i < rows; ++i) {
                delete[] content[i];
            }
            delete[] content;
        }
    }

    void validate() const {
        if (content == nullptr) {
            throw std::runtime_error("[Matrix]: matrix has been moved from here");
        }
    }
};