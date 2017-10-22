//
// Created by peter on 17.10.17.
//

#ifndef MATRIXCLASS_MATRIX_H
#define MATRIXCLASS_MATRIX_H

#include <cstdio>
#include <exception>
#include <vector>
#include <cstring>
#include <ostream>

class MatrixColumn
{
public:
    MatrixColumn(size_t h,   double*& data):
            H(h), col_data(data)
    { }

    // j - строка
    double& operator[](size_t j) const
    {
        if(j >= H)
            throw std::exception();

        return col_data[j];
    }

private:
    size_t H;
    double* col_data;
};

class Matrix
{
public:

    // i - колонка
    // j - строка
    MatrixColumn operator[](size_t i)  const
    {
        if(i >= W)
            throw std::exception();

        double* col_i = data + i*H;

        auto res  = MatrixColumn(H, col_i);
        return res;
    }


    Matrix(size_t w, size_t h)
            :W(w),
             H(h)
    {
        if(W==0 || H == 0)
        {
            throw std::exception();
        }

        data = new double[W*H];
        memset(data, 0, W*H);
    }


    Matrix(const Matrix& other)
    {
        this->W = other.W;
        this->H = other.H;

        this->data = new double[W*H];

        for (size_t i = 0; i < W * H; ++i) {
           data[i] = other.data[i];
        }
    }


    ~Matrix()
    {
        delete[] data;
    }

    // i - колонка
    // j - строка
    double get(size_t i, size_t j) const
    {
        return (*this)[i][j];
    }

    size_t getWidth()
    {
        return W;
    }

    size_t  getHeight()
    {
        return H;
    }


    bool operator==(const Matrix& other) const
    {
        if(this->W != other.W  || this->H != other.H)
            return false;

        for (size_t i = 0; i < W*H; ++i)
        {
            if(this->data[i] != other.data[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }


    std::vector<double> to_vector()
    {
        return std::vector<double>(data, data + sizeof(data)/sizeof(double));
    }


    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);


   // умножение матрицы на число
    Matrix operator*(double a)
    {
        Matrix res (*this);

        for (size_t i = 0; i < res.W*res.H; ++i)
        {
            res.data[i] *= a;
        }
        return res;
    }

   // умножение матрицы на число и запись результаа ту же матрицу
    Matrix& operator*=(double a)
    {
        for (size_t i = 0; i < W*H; ++i)
        {
            data[i] *= a;
        }
        return (*this);
    }


    // умножение матрицы на столбец, и запись результата в ту же матрицу
    Matrix& operator*=(const std::vector<double>& vec_rhs) {

        if (vec_rhs.size() != W) {
            throw std::exception();
        }

        Matrix res(1, H);

        for (size_t j = 0; j < H; ++j) {
            res[0][j] = 0;
            for (size_t i = 0; i < W; ++i) {

                res[0][j] += vec_rhs[i] * (*this)[i][j];

            }
        }

        delete this->data;

        *this = res;

        return (*this);
    }


    // умножение матрицы на столбец
    Matrix operator*( const std::vector<double>& vec_rhs)  const
    {
        if (vec_rhs.size() != W) {
            throw std::exception();
        }

        Matrix res(1, H);

        for (size_t j = 0; j < H; ++j) {
            res[0][j] = 0;
            for (size_t i = 0; i < W; ++i) {

                res[0][j] += vec_rhs[i] * (*this)[i][j];

            }
        }

        return res;
    }




    // Умножение строки на матрицу
    // не получится определить внутри класса так как тогда будет конфликт с умножением на столбец
    friend Matrix operator*(const std::vector<double>& vec_lhs, const Matrix& mat);

    Matrix& operator=(const Matrix& other)
    {
        this->W = other.W;
        this->H = other.H;

        delete[] this->data;

        this->data = new double[W*H];

        for (size_t i = 0; i < W * H; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }



    static Matrix ones(size_t S)
    {
        Matrix res(S,S);

        for(size_t i = 0; i<S; ++i)
        {
            res[i][i] = 1;
        }

        return res;
    }




private:


    double* data;

    // ширина - количество колонок
    size_t  W;
    // высота - количество строк
    size_t  H;

};

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    os<<std::endl;
    os<<"-----------"<<std::endl;

    for (size_t j = 0; j < m.H; ++j)
    {
        for (size_t i = 0; i < m.W; ++i) {
            os << m[i][j] << " ";
        }
        os << std::endl;
    }
    os<<"-----------"<<std::endl;
    return os;
}


Matrix operator*(const std::vector<double>& vec_lhs, const Matrix& mat)
{

    if (vec_lhs.size() != mat.H) {
        throw std::exception();
    }

    Matrix res(mat.W, 1);

    for (size_t i = 0; i < mat.W; ++i) {
        res[i][0] = 0;
        for (size_t j = 0; j < mat.H; ++j) {
            res[i][0] += vec_lhs[j] * mat[i][j];
        }
    }

    return res;
}

#endif //MATRIXCLASS_MATRIX_H
