#include <iostream>
#include <vector>
#include <assert.h>

//  описание самого класса
template<class T>
class Matrix
{
private:

    int col = 0;
    int row = 0;

    std::vector<std::vector<T> > matr_;

    // прокси класс строки в матрице для оператора [], содержит указатель на начало строки в матрице и размер строки
    class Matrix_row
    {
    public:
        Matrix_row(typename std::vector<T>::iterator row_begin, int size): row_begin_(row_begin), size_(size) {};

        T& operator[](int ind)
        {
            if (ind >= size_)
                assert(!"index out of range");
            return *(row_begin_ + ind);
        }
    private:
        const typename std::vector<T>::iterator row_begin_;
        const int size_;
    };
public:
    Matrix(int rows, int cols): col(cols), row(rows)
    {
        matr_.resize(row);
        for (int i = 0; i < row; i++)
            matr_[i].resize(col);
    }

    Matrix(const Matrix<T>& copied)
    {
        if (this == &copied)
            return;

        col = copied.get_ncol();
        row = copied.get_nrow();
        matr_ = copied.matr_;
    }

    Matrix& operator=(const Matrix<T>& copied)
    {
        if (this == &copied)
            return *this;

        row = copied.get_nrow();
        col = copied.get_ncol();
        matr_.clear();
        matr_ = copied.matr_;
        return *this;
    }

    Matrix(Matrix<T>&& movied)
    {
        if (this == &movied)
            return;

        col = movied.col;
        row = movied.row;
        movied.row = movied.col = 0;
        matr_ = std::move(movied.matr_);
    }

    Matrix& operator=(Matrix<T>&& movied)
    {
        if (this == &movied)
            return *this;

        col = movied.col;
        row = movied.row;
        movied.row = movied.col = 0;
        matr_.clear();
        matr_ = std::move(movied.matr_);
        return *this;
    }

    Matrix_row operator[](int ind)
    {
        if (ind >= row)
            assert(!"index out of range");

        return Matrix_row(matr_[ind].begin(), col);
    }

    const int get_nrow() const
    {
        return row;
    }

    const int get_ncol() const
    {
        return col;
    }

    Matrix operator*(T mul) const
    {
        Matrix<T> res(row, col);

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                res[i][j] = matr_[i][j] * mul;

        return res;
    }

    std::vector<T> operator*(const std::vector<T>& vec) const
    {
        if (vec.size() != col)
            throw "wrong size of vector in multiply";
        std::vector<T> res(row);

        for (int i = 0; i < row; i++)
        {
            T temp = 0;
            for (int j = 0; j < col; j++)
                temp += matr_[i][j] * vec[j];
            res[i] = temp;
        }

        return res;
    }

    bool operator==(const Matrix<T>& right) const
    {
        if (row != right.row || col != right.col)
            throw "wrong sizes in compare";

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                if (matr_[i][j] != right.matr_[i][j])
                    return false;
        return true;
    }

    bool operator!=(const Matrix<T>& right) const
    {
        return !(*this==right);
    }

};


//     тесты
template<class T>
class test
{
    void check(bool value)
    {
        if (!value)
            std::cout << "error" << std::endl;
    }

    void checkGetSize()
    {
        Matrix<T> m(2, 3);
        m[0][0] = 1;
        m[0][1] = 1;
        check(m.get_ncol() == 3);
        check(m.get_nrow() == 2);
    }

    void checkVectorMul()
    {
        Matrix<T> m(2, 3);
        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;
        std::vector<T> v = {1, 2, 3};
        std::vector<T> res = m * v;
        check(res[0] == 14);
        check(res[1] == 32);
    }

    void checkNumMul()
    {
        Matrix<T> m1(2, 3);
        m1[0][0] = 1;
        m1[0][1] = 2;
        m1[0][2] = 3;
        m1[1][0] = 4;
        m1[1][1] = 5;
        m1[1][2] = 6;
        Matrix<T> m2 = m1 * 3;

        for (size_t i = 0; i < 2; i++)
            for (size_t j = 0; j < 3; j++)
                check(m1[i][j] * 3 == m2[i][j]);
    }

    void checkGetSet()
    {
        Matrix<T> m(2, 3);
        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;

        check(m[0][0] == 1);
        check(m[0][1] == 2);
        check(m[0][2] == 3);
        check(m[1][0] == 4);
        check(m[1][1] == 5);
        check(m[1][2] == 6);

        m[1][2] = 100;

        check(m[1][2] == 100);
    }

    void checkMovesCopies()
    {
        Matrix<T> m(2, 3);
        m[0][0] = 1;
        m[0][1] = 2;
        m[0][2] = 3;
        m[1][0] = 4;
        m[1][1] = 5;
        m[1][2] = 6;

        Matrix<T> m1(m);
        check(m == m1);
        m1 = m;
        check(m == m1);
        Matrix<T> m2(std::move(m));
        check(m1 == m2);
        m = m1;
        m2 = std::move(m);
        check(m1 == m2);
    }
public:
    void do_test()
    {
        checkGetSize();
        checkVectorMul();
        checkNumMul();
        checkGetSet();
        checkMovesCopies();
    }
};


int main(){
    test<double> t1;
    try
    {
        t1.do_test();
    }
    catch (const char* ms){
        std::cout << ms << std::endl;
    }

    test<int> t2;
    try
    {
        t2.do_test();
    }
    catch (const char* ms){
        std::cout << ms << std::endl;
    }
    return 0;
}

