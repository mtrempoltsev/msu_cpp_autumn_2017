#include <iostream>
#include <vector>
#include <assert.h>

class Matrix
{
private:

    size_t ncol_ = 0, nrow_ = 0;

    std::vector<std::vector<double> > matr_;

    // прокси класс строки в матрице для оператора [], содержит указатель на начало строки в матрице и размер строки
    class Matrix_row
    {
    public:
        Matrix_row(std::vector<double>::iterator row_begin, size_t size): row_begin_(row_begin), size_(size) {};

        double& operator[](size_t ind)
        {
            if (ind >= size_)
                assert(!"index out of range");
            return *(row_begin_ + ind);
        }
    private:
        const std::vector<double>::iterator row_begin_;
        const size_t size_;
    };
public:
    Matrix(size_t rows, size_t cols): ncol_(cols), nrow_(rows)
    {
        matr_.resize(nrow_);
        for (size_t i = 0; i < nrow_; i++)
            matr_[i].resize(ncol_);
    }

    Matrix(const Matrix& right)
    {
        ncol_ = right.get_ncol();
        nrow_ = right.get_nrow();
        for (size_t i = 0; i < nrow_; i++)
            for (size_t j = 0; j < ncol_; j++)
                matr_[i][j] = right.matr_[i][j];
    }

    Matrix_row operator[](size_t ind)
    {
        if (ind >= nrow_)
            assert(!"index out of range");

        return Matrix_row(matr_[ind].begin(), ncol_);
    }

    const size_t get_nrow() const
    {
        return nrow_;
    }

    const size_t get_ncol() const
    {
        return ncol_;
    }

    Matrix operator*(double mul) const
    {
        Matrix res(nrow_, ncol_);

        for (size_t i = 0; i < nrow_; i++)
            for (size_t j = 0; j < ncol_; j++)
                res[i][j] = matr_[i][j] * mul;

        return res;
    }

    std::vector<double> operator*(const std::vector<double>& vec) const
    {
        if (vec.size() != ncol_)
            assert(!"wrong size of vector in multiply");
        std::vector<double> res(nrow_);

        for (size_t i = 0; i < nrow_; i++)
        {
            double temp = 0;
            for (size_t j = 0; j < ncol_; j++)
                temp += matr_[i][j] * vec[j];
            res[i] = temp;
        }

        return res;
    }

    bool operator==(Matrix& right) const
    {
        if (nrow_ != right.nrow_ || ncol_ != right.ncol_)
            assert(!"wrong sizes in compare");

        for (size_t i = 0; i < nrow_; i++)
            for (size_t j = 0; j < ncol_; j++)
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

std::ostream& operator<<(std::ostream& stream, Matrix& matrix) {
    for (size_t i = 0; i < matrix.nrow_; i++) {
        for (size_t j = 0; j < matrix.ncol_; j++)
            stream << matrix[i][j] << ' ';
        stream << std::endl;
    }
    return stream;
}

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
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

    for (size_t i = 0; i < 2; i++)
        for (size_t j = 0; j < 3; j++)
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
