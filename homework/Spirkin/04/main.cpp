#include <iostream>
#include <vector>
#include <assert.h>

class Matrix
{
private:

    int col = 0;
    int row = 0;
    std::vector<std::vector<double> > matr_;

    // прокси класс строки в матрице для оператора [], содержит указатель на начало строки в матрице и размер строки
    class Matrix_row
    {
    public:
        Matrix_row(std::vector<double>::iterator row_begin, int  size): row_begin_(row_begin), size_(size) {};

        double& operator[](int  ind)
        {
            if (ind >= size_)
                assert(!"index out of range");
            return *(row_begin_ + ind);
        }
    private:
        const std::vector<double>::iterator row_begin_;
        const int  size_;
    };
public:
    Matrix(int  rows, int  cols): col(cols), row(rows)
    {
        matr_.resize(row);
        for (int  i = 0; i < row; i++)
            matr_[i].resize(col);
    }

    Matrix(const Matrix& right)
    {
        col = right.get_ncol();
        row = right.get_nrow();
        for (int  i = 0; i < row; i++)
            for (int  j = 0; j < col; j++)
                matr_[i][j] = right.matr_[i][j];
    }

    Matrix_row operator[](int  ind)
    {
        if (ind >= row)
            assert(!"index out of range");

        return Matrix_row(matr_[ind].begin(), col);
    }

    const int  get_nrow() const
    {
        return row;
    }

    const int  get_ncol() const
    {
        return col;
    }

    Matrix operator*(double mul) const
    {
        Matrix res(row, col);

        for (int  i = 0; i < row; i++)
            for (int  j = 0; j < col; j++)
                res[i][j] = matr_[i][j] * mul;

        return res;
    }

    std::vector<double> operator*(const std::vector<double>& vec) const
    {
        if (vec.size() != col)
            assert(!"wrong size of vector in multiply");
        std::vector<double> res(row);

        for (int  i = 0; i < row; i++)
        {
            double temp = 0;
            for (int  j = 0; j < col; j++)
                temp += matr_[i][j] * vec[j];
            res[i] = temp;
        }

        return res;
    }

    bool operator==(Matrix& right) const
    {
        if (row != right.row || col != right.col)
            assert(!"wrong sizes in compare");

        for (int  i = 0; i < row; i++)
            for (int  j = 0; j < col; j++)
                if (matr_[i][j] != right[i][j])
                    return false;
        return true;
    }

    bool operator!=(Matrix& right) const
    {
        return !(*this==right);
    }

    friend std::ostream& operator<<(std::ostream& stream, Matrix& matrix);

};



void check(bool value)
{
    if (!value){
      std::cout << "error" << std::endl;
      exit(1);
    }
}

void checkGetSize()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 1;
    check(m.get_ncol() == 3);
    check(m.get_nrow() == 2);
}

void checkVectorMul()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    std::vector<double> v = {1, 2, 3};
    std::vector<double> res = m * v;
    check(res[0] == 14);
    check(res[1] == 32);
}

void checkNumMul()
{
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[0][2] = 3;
    m1[1][0] = 4;
    m1[1][1] = 5;
    m1[1][2] = 6;
    Matrix m2 = m1 * 3;

    for (int  i = 0; i < 2; i++)
        for (int  j = 0; j < 3; j++)
            check(m1[i][j] * 3 == m2[i][j]);
}

void checkGetSet()
{
    Matrix m(2, 3);
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

int main(int argc, char* argv[])
{
    checkGetSize();
    checkVectorMul();
    checkNumMul();
    checkGetSet();
    return 0;
}

