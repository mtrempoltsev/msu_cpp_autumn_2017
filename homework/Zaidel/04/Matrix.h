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


    Matrix operator*=(double a)
    {
        for (size_t i = 0; i < W*H; ++i)
        {
            data[i] *= a;
        }
        return (*this);
    }

    std::vector<double> to_vector()
    {
        return std::vector<double>(data, data + sizeof(data)/sizeof(double));
    }


    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);

    friend Matrix operator*=(Matrix& mat, const std::vector<double>& vec_rhs);

    friend Matrix operator*=(Matrix& mat, double a);

    friend Matrix operator*(const Matrix& mat, double a);
    friend Matrix operator*(const Matrix& mat, const std::vector<double>& vec_rhs);
    friend Matrix operator*(const std::vector<double>& vec_lhs, const Matrix& mat);

    Matrix operator=(const Matrix& other)
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


Matrix operator*(const Matrix& mat, double a)
{
    Matrix res (mat);

    for (size_t i = 0; i < mat.W*mat.H; ++i)
    {
       res.data[i] *= a;
    }
    return res;
}

Matrix operator*=(Matrix& mat, double a)
{
    mat = mat * a;
    return mat;
}


Matrix operator*(const Matrix& mat, const std::vector<double>& vec_rhs)
{
    if (vec_rhs.size() != mat.W) {
        throw std::exception();
    }

    Matrix res(1, mat.H);

    for (size_t j = 0; j < mat.H; ++j) {
        res[0][j] = 0;
        for (size_t i = 0; i < mat.W; ++i) {

            res[0][j] += vec_rhs[i] * mat[i][j];

        }
    }

    return res;
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

Matrix operator*=(Matrix& mat, const std::vector<double>& vec_rhs) {

    mat = mat * vec_rhs;
    return mat;
}

//Matrix operator=(const Matrix &other) {
//    this->W = other.W;
//    this->H = other.H;
//
//    delete[] this->data;
//
//    this->data = new double[W*H];
//
//    for (size_t i = 0; i < W * H; ++i) {
//        data[i] = other.data[i];
//    }
//
//    return *this;
//}

#endif //MATRIXCLASS_MATRIX_H
