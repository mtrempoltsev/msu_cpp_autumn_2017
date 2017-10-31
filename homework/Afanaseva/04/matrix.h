#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <exception>

#include <vector>
#include <cstdio>
#include <cstring>
#include <math.h>

#include "matrixcolumn.h"


using namespace std;

bool almost_equal(double a, double b, double epsilon = 1e-7)
{
    double maximum = max(1., max(abs(a), abs(b)));
    if (abs(a - b) < epsilon * maximum)
        return true;
    return false;
}

class Matrix
{
private:
    double* data_; // указатель на начало хранения элементов матрицы
    size_t rows_; // количество строк в матрице
    size_t cols_; // количество столбцов в матрице

public:
    /* Конструкторы для создания матрицы:
     *      по числу строк и столбцов
     *      по другой матрице (конструктор копирования)
     * Деструктор */

    Matrix (size_t rows, size_t cols, double default_value = 0)
        : rows_(rows)
        , cols_(cols)
    {
        if(rows <= 0 || cols <= 0)
            throw "Matrix creation error: unsupport matrix size.";

        data_ = new double[rows * cols];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows * cols; i++)
            data_[i] = default_value;
    }

    Matrix (size_t rows, size_t cols, double* data)
        : rows_(rows)
        , cols_(cols)
    {
        if(rows <= 0 || cols <= 0)
            throw "Matrix creation error: unsupport matrix size.";

        if(data == nullptr)
            throw "Matrix creation error: input data empty.";

        data_ = new double[rows * cols];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows * cols; i++)
            data_[i] = data[i];
    }

    Matrix (const Matrix& other)
    {
        this->rows_ = other.rows_;
        this->cols_ = other.cols_;

        this->data_ = new double[rows_ * cols_];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows_ * cols_; i++)
           data_[i] = other.data_[i];
    }

    ~Matrix()
    {
        delete[] data_;
    }

    /* Функции:
     *      для получения элемента
     *      размера матрицы */

    const double get_element(size_t i, size_t j) const
    {
	return (*this)[i][j]; // i - номер столбца, j - номер строки
    }

    double set_element(size_t i, size_t j, double value)
    {
	(*this)[i][j] = value;
	return (*this)[i][j]; // i - номер столбца, j - номер строки
    }

    size_t get_rows_size() const
    {
        return cols_;
    }

    size_t  get_column_size() const
    {
        return rows_;
    }

    /* Операторы:
            получения столбца
            сравнения и неравенства
            присваивания
            */

    const MatrixColumn operator[](size_t i) const // i - номер столбца
    {
        if(i >= cols_)
            throw "Matrix error: column index out of range";

        double* column_i = data_ + i * rows_;
        return MatrixColumn(rows_, column_i);
    }

    MatrixColumn operator[](size_t i) // i - номер столбца
    {
	if(i >= cols_)
	    throw "Matrix error: column index out of range";

	double* column_i = data_ + i * rows_;
	return MatrixColumn(rows_, column_i);
    }


    bool operator==(const Matrix& other) const
    {
        if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
            return false;
        for (size_t i = 0; i < rows_ * cols_; i++)
           if (!almost_equal(this->data_[i], other.data_[i]))
               return false;

        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }


    Matrix& operator=(const Matrix& other)
    {
        if (this == &other)
            return (*this);

        this->rows_ = other.rows_;
        this->cols_ = other.cols_;

        delete[] this->data_;

        this->data_ = new double[rows_ * cols_];
        if (data_ == nullptr)
            throw "Matrix assignment error: memory allocation error.";

        for (size_t i = 0; i < rows_ * cols_; i++) {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    /* Умножение матрицы (всех элементов матрицы) на число с созданием нового экземпляра
     *      и с операцией присвоения результата текущему экземпляру класса
     * Умножение матрицы на вектор-столбец (слева) с созданием нового экземпляра
     *      и с операцией присвоения результата текущему экземпляру класса
     */

    Matrix& operator*=(double multiplicator)
    {
        for (size_t i = 0; i < rows_ * cols_; i++)
        {
            this->data_[i] *= multiplicator;
        }
        return (*this);
    }

    Matrix operator*(double multiplicator)
    {
        Matrix result (*this);
        for (size_t i = 0; i < rows_ * cols_; i++)
        {
            result.data_[i] *= multiplicator;
        }
        return result;
    }

    Matrix operator*(const std::vector<double>& vector_right)
    {
        if (vector_right.size() != cols_)
        {
            throw "Multiplication error: incorrect vector size.";
        }

        Matrix result(rows_, 1);

        MatrixColumn result_column = result[0];

        for (size_t j = 0; j < rows_; j++)
        {
            result_column[j] = 0;
            for (size_t i = 0; i < cols_; i++)
            {
                result_column[j] += (*this)[i][j] * vector_right[i];
            }
        }
        return result;
    }

    Matrix& operator*=(const std::vector<double>& vector_right)
    {
        if (vector_right.size() != cols_)
        {
            throw "Multiplication error: incorrect vector size.";
        }

        Matrix result(rows_, 1);
        result = (*this) * vector_right;

        (*this) = result;
        return (*this);
    }
};

// Функция для вывода матрицы в командную строку.
ostream& operator<<(ostream& os, const Matrix& m)
{
    os << endl << "-----------------" << endl << endl;
    auto rows = m.get_column_size();
    auto cols = m.get_rows_size();
    for (size_t j = 0; j < rows; j++)
    {
        for (size_t i = 0; i < cols; i++)
        {
            os << m.get_element(i, j) << " ";
        }
        os <<  endl;
    }
    os << endl << "-----------------" << endl << endl;
    //os << endl;
    //os << "Rows: " << m.get_column_size() << " Cols: " << m.get_rows_size() << endl;
    return os;
}

#endif // MATRIX_H
