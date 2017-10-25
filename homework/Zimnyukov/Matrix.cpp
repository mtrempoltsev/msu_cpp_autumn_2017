#include <iostream>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <stdio.h>
using namespace std;

//Proxy-class for [][] operation
template <typename T>
class Matrix_Row
{
private:
    T *row;
    size_t m;
public:

    Matrix_Row<T>(T* a, size_t cnt) {
        row = a;
        m = cnt;
    }

    T& operator[](size_t i) {
        if (i >= m) {
              assert(!"index out of range");
              exit(1);
        }
        return row[i];
    }
};

template <typename T>
class  Matrix
{
private:

    size_t n; //rows count
    size_t m; //columns count
    T **arr;

public:

    Matrix (int row, int col)
    {
        arr = (T **)malloc(row * sizeof(T*) + row * col * sizeof(T));
        T *buf;
        buf = (T*)(arr + row);
        for (int i = 0; i < row; ++i) {
            arr[i] = buf + i * col;
        }
        n = row;
        m = col;
    }

    size_t columns()
    {
        return m;
    }

    size_t rows()
    {
        return n;
    }

    Matrix<T>(const Matrix& mt)
    {
        int row = mt.n, col = mt.m;
        arr = (T **)malloc(row * sizeof(T*) + row * col * sizeof(T));
        T *buf;
        buf = (T*)(arr + row);
        for (int i = 0; i < row; ++i) {
            arr[i] = buf + i * col;
        }
        n = row;
        m = col;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                arr[i][j] = mt.arr[i][j];
            }
        }
    }

    Matrix<T>& operator=(Matrix& mt)
    {
        if (this == &mt)
            return *this;
        int row = mt.n, col = mt.m;
        free(arr);
        arr = (T **)malloc(row * sizeof(T*) + row * col * sizeof(T));
        T *buf;
        buf = (T*)(arr + row);
        for (int i = 0; i < row; ++i) {
            arr[i] = buf + i * col;
        }
        n = row;
        m = col;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                arr[i][j] = mt.arr[i][j];
            }
        }
        return *this;
    }

    Matrix(Matrix&& mt)
    {
        n = mt.n;
        m = mt.m;
        arr = mt.arr;
        mt.arr = nullptr;
    }

    Matrix& operator=(Matrix&& movied)
    {
        if (this == &movied)
            return *this;
        free(arr);
        arr = movied.arr;
        n = movied.n;
        m = movied.m;
        movied.arr = nullptr;
        return *this;
    }

    Matrix_Row<T> operator[](size_t i)
    {
        if (i >= n) {
              assert(!"index out of range");
              exit(1);
        }
        return Matrix_Row<T>(arr[i], m); //m for check if column index our of range
    }

    Matrix& operator*=(vector <T> &v)
    {
        if (m != v.size()) {
            assert(!"the vector has an unsuitable length"); //during matrix multiplication on vector from right, vector size must be equal to matrix colimn count
            exit(1);
        }
        Matrix res = Matrix(n, 1);
        for (size_t i = 0; i < n; ++i) {
            res[i][0] = 0;
            for (size_t j = 0; j < m; ++j){
                res[i][0] += arr[i][j] * v[j];
            }
        }

        int row = res.n, col = res.m;
        free(arr);
        arr = (T **)malloc(row * sizeof(T*) + row * col * sizeof(T));
        T *buf;
        buf = (T*)(arr + row);
        for (int i = 0; i < row; ++i) {
            arr[i] = buf + i * col;
        }
        n = row;
        m = col;
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                arr[i][j] = res.arr[i][j];
            }
        }
        return *this;
    }

    Matrix& operator*=(T k)
    {
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                arr[i][j] *= k;
            }
        }
        return *this;
    }

    int operator==(Matrix& mt)
    {
        if (n != mt.rows() || m != mt.columns())
            return 0;
        int flag = 1;
        for (size_t i = 0; i < n && flag; ++i) {
            for (size_t j = 0; j < m && flag; ++j) {
                flag = (arr[i][j] == mt[i][j]);
            }
        }
        return flag;
    }

    int operator!=(Matrix& mt)
    {
        return !(*this == mt);
    }

    //with_size - flag of outputing matrix sizes
    //format - format string for 1 element of matrix
    void print(int with_size, char *format)
    {
        if (with_size) {
            printf("%lu %lu\n", n, m);
        }
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                printf(format, arr[i][j]);
            }
            printf("\n");
        }
    }

    //print version with standart format of each element outputing
    void print(int with_size)
    {
        char c[] = "%lf ";
        print(with_size, c);
    }

    ~Matrix() {
        free(arr);
    }


};

