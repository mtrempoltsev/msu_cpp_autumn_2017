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

template <class T>
class MatrixColumn
{
public:
    MatrixColumn(size_t h,   T*& data):
            H(h), col_data(data)
    { }

    // j - строка
    T& operator[](size_t j) const
    {
        if(j >= H)
            throw std::exception();

        return col_data[j];
    }

private:
    size_t H;
    double* col_data;
};

template <class T>
class Matrix
{
public:

    // i - колонка
    // j - строка
    MatrixColumn<T> operator[](size_t i)  const
    {
        if(i >= W)
            throw std::exception();

        T* col_i = data + i*H;

        auto res  = MatrixColumn<T>(H, col_i);
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

        data = new T[W*H];
        memset(data, 0, W*H);
    }

    // copy constructor
    Matrix(const Matrix<T>& other):
            W(other.W),
            H(other.H)
    {

        if(other.isEmpty())
        {
            W=0;
            H=0;
            return;
        }

        this->data = new T[W*H];

        for (size_t i = 0; i < W * H; ++i) {
           data[i] = other.data[i];
        }
    }

    // move constructor
    Matrix(Matrix<T>&& moving):
            W(moving.W),
            H(moving.H)
    {
        this->data = moving.data;
        // Ставим указатель на данные в перемещаемой матрице как nullptr
        moving.data = nullptr;
        // устанавливаем размер перемещаемой матрицы 0
        moving.W =0;
        moving.H =0;
    }


    ~Matrix()
    {
        delete[] data;
    }

    // i - колонка
    // j - строка
    T get(size_t i, size_t j) const
    {
        if( i >= W || j>= H)
        {
            throw std::exception();
        }

        return (*this)[i][j];
    }

    size_t getWidth() const
    {
        return W;
    }

    size_t  getHeight() const
    {
        return H;
    }

    bool isEmpty() const
    {
        if(W ==0 || H ==0)
            return true;
        if(data == nullptr)
            return true;
        return false;
    }


    bool operator==(const Matrix<T>& other) const
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

    bool operator!=(const Matrix<T>& other) const
    {
        return !(*this == other);
    }


    std::vector<T> to_vector()  const
    {
        if(isEmpty())
        {
            return std::vector<T>();
        }
        return std::vector<T>(data, data + W*H);
    }



    template <class T1>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<T1>& m);


   // умножение матрицы на число
    Matrix<T> operator*(T a)
    {
        Matrix<T> res (*this);

        for (size_t i = 0; i < res.W*res.H; ++i)
        {
            res.data[i] *= a;
        }
        return res;
    }

   // умножение матрицы на число и запись результаа ту же матрицу
    Matrix<T>& operator*=(T a)
    {
        for (size_t i = 0; i < W*H; ++i)
        {
            data[i] *= a;
        }
        return (*this);
    }


    // умножение матрицы на столбец, и запись результата в ту же матрицу
    Matrix<T>& operator*=(const std::vector<T>& vec_rhs) {

        if (vec_rhs.size() != W) {
            throw std::exception();
        }

        Matrix<T> res(1, H);

        for (size_t j = 0; j < H; ++j) {
            res[0][j] = 0;
            for (size_t i = 0; i < W; ++i) {

                res[0][j] += vec_rhs[i] * (*this)[i][j];

            }
        }

        delete this->data;


        // copy res matrix values to this matrix

        this->W = res.W;
        this->H = res.H;

        this->data = new T[this->W * this->H];

        for (size_t i = 0; i < this->W * this->H; ++i) {
            this->data[i] = res.data[i];
        }

        return (*this);
    }


    // умножение матрицы на столбец
    Matrix<T> operator*( const std::vector<T>& vec_rhs)  const
    {
        if (vec_rhs.size() != W) {
            throw std::exception();
        }

        Matrix<T> res(1, H);

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
    template <class T1>
    friend Matrix<T1> operator*(const std::vector<T1>& vec_lhs, const Matrix<T1>& mat);

    // copy operator
    Matrix<T>& operator=(const Matrix<T>& other)
    {
        if (this == &other)
            return *this;

        this->W = other.W;
        this->H = other.H;

        delete[] this->data;

        this->data = new T[W*H];

        for (size_t i = 0; i < W * H; ++i) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // moving operator
    Matrix<T>& operator=(Matrix<T>&& movied)
    {
        if (this == &movied)
            return *this;

        delete[] data;
        data = movied.data;
        H = movied.H;
        W = movied.W;

        movied.data = nullptr;
        return *this;
    }



    static Matrix<T> ones(size_t S)
    {
        Matrix<T> res(S,S);

        for(size_t i = 0; i<S; ++i)
        {
            res[i][i] = static_cast<T>(1);
        }

        return res;
    }




private:


    T* data;

    // ширина - количество колонок
    size_t  W;
    // высота - количество строк
    size_t  H;

};

template <class D>
std::ostream& operator<<(std::ostream& os, const Matrix<D>& m)
{
    os<<"-----------"<<std::endl;

    if(m.isEmpty())
    {
        os<<" EMPTY "<<std::endl;
        os<<"-----------"<<std::endl;
        return os;
    }

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

template <class D>
Matrix<D> operator*(const std::vector<D>& vec_lhs, const Matrix<D>& mat)
{

    if (vec_lhs.size() != mat.H) {
        throw std::exception();
    }

    Matrix<D> res(mat.W, 1);

    for (size_t i = 0; i < mat.W; ++i) {
        res[i][0] = 0;

        for (size_t j = 0; j < mat.H; ++j) {
            res[i][0] += vec_lhs[j] * mat[i][j];
        }
    }

    return res;
}

#endif //MATRIXCLASS_MATRIX_H
