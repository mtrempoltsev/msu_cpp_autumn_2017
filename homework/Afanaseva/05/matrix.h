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



template <class T>
class Matrix
{
private:
    T* data_; // указатель на начало хранения элементов матрицы
    size_t rows_; // количество строк в матрице
    size_t cols_; // количество столбцов в матрице

public:
    /* Конструкторы и операторы перемещения и копирования*/
    void is_not_moved() const
    {
        if(data_ == nullptr)
            throw "Matrix error: data has been removed.";
    }

    Matrix<T> (Matrix<T>&& movied) // конструктор перемещения
    {
        movied.is_not_moved();

        this->rows_ = movied.rows_;
        this->cols_ = movied.cols_;
        this->data_ = movied.data_;

        movied.data_ = nullptr;
        movied.cols_ = 0;
        movied.data_ = 0;
    }

    Matrix<T>& operator=(Matrix<T>&& movied) // оператор перемещения
    {
        if (this == &movied)
            return *this;

        movied.is_not_moved();

        delete[] this->data_;

        this->rows_ = movied.rows_;
        this->cols_ = movied.cols_;
        this->data_ = movied.data_;

        movied.data_ = nullptr;
        movied.cols_ = 0;
        movied.data_ = 0;

        return *this;
    }


    Matrix<T> (const Matrix<T>& copied) // конструктор копирования
    {
        copied.is_not_moved();

        this->rows_ = copied.rows_;
        this->cols_ = copied.cols_;

        this->data_ = new T[rows_ * cols_];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows_ * cols_; i++)
           data_[i] = copied.data_[i];
    }

    Matrix<T>& operator=(const Matrix<T>& copied) // оператор копирования
    {
        if (this == &copied)
            return *this;

        copied.is_not_moved();

        this->rows_ = copied.rows_;
        this->cols_ = copied.cols_;

        delete[] this->data_;

        this->data_ = new T[rows_ * cols_];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows_ * cols_; i++)
           data_[i] = copied.data_[i];

        return *this;
    }

    /* Конструкторы для создания матрицы:
     *      по числу строк и столбцов
     *      по заданному набору значений
     * Деструктор */

    Matrix<T> (size_t rows, size_t cols, T default_value = 0)
        : rows_(rows)
        , cols_(cols)
    {
        if(rows <= 0 || cols <= 0)
            throw "Matrix creation error: unsupport matrix size.";

        data_ = new T[rows * cols];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows * cols; i++)
            data_[i] = default_value;
    }

    Matrix<T> (size_t rows, size_t cols, T* data)
        : rows_(rows)
        , cols_(cols)
    {
        if(rows <= 0 || cols <= 0)
            throw "Matrix creation error: unsupport matrix size.";

        if(data == nullptr)
            throw "Matrix creation error: input data empty.";

        data_ = new T[rows * cols];
        if (data_ == nullptr)
            throw "Matrix creation error: memory allocation error.";

        for (size_t i = 0; i < rows * cols; i++)
            data_[i] = data[i];
    }

    ~Matrix<T>()
    {
        delete[] data_;
    }

    /* Функции:
     *      для получения элемента
     *      размера матрицы */


    T set_element(size_t i, size_t j, T value)
    {
	(*this)[i][j] = value;
	return (*this)[i][j]; // i - номер столбца, j - номер строки
    }

    const T get_element(size_t i, size_t j) const
    {
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

    MatrixColumn<T> operator[](size_t i) const // i - номер столбца
    {
        if(i >= cols_)
            throw "Matrix error: column index out of range";

        T* column_i = data_ + i * rows_;
        return MatrixColumn<T>(rows_, column_i);
    }

    bool operator==(const Matrix<T>& other) const
    {
        if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
            return false;
        for (size_t i = 0; i < rows_ * cols_; i++)
           if (!almost_equal(this->data_[i], other.data_[i]))
               return false;

        return true;
    }

    bool operator!=(const Matrix<T>& other) const
    {
        return !(*this == other);
    }

    /* Умножение матрицы (всех элементов матрицы) на число с созданием нового экземпляра
     *      и с операцией присвоения результата текущему экземпляру класса
     * Умножение матрицы на вектор-столбец (слева) с созданием нового экземпляра
     *      и с операцией присвоения результата текущему экземпляру класса
     */

    Matrix<T>& operator*=(T multiplicator)
    {
        for (size_t i = 0; i < rows_ * cols_; i++)
        {
            this->data_[i] *= multiplicator;
        }
        return (*this);
    }

    Matrix<T> operator*(T multiplicator)
    {
        Matrix<T> result (*this);
        for (size_t i = 0; i < rows_ * cols_; i++)
        {
            result.data_[i] *= multiplicator;
        }
        return result;
    }

    Matrix<T> operator*(const std::vector<T>& vector_right)
    {
        if (vector_right.size() != cols_)
        {
            throw "Multiplication error: incorrect vector size.";
        }

        Matrix<T> result(rows_, 1);

        MatrixColumn<T> result_column = result[0];

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

    Matrix<T>& operator*=(const std::vector<T>& vector_right)
    {
        if (vector_right.size() != cols_)
        {
            throw "Multiplication error: incorrect vector size.";
        }

        Matrix<T> result(rows_, 1);
        result = (*this) * vector_right;

        (*this) = result;
        return (*this);
    }
};

// Функция для вывода матрицы в командную строку.
template <class T>
ostream& operator<<(ostream& os, const Matrix<T>& m)
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
