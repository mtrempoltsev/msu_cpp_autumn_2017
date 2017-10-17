#include <iostream>
#include <vector>
#include <cassert>

class MatrixRow
{
public:
    MatrixRow(size_t rowSize, size_t col, double* data):rowSize_(rowSize), col_(col), data_(data)
    {
    }
    double& operator[](size_t row)
    {
        if (row >= rowSize_)
        {
            assert(!"index out of range");
        }
        return data_[col_ * rowSize_ + row];
    }
private:
    size_t  rowSize_,
            col_;
    double* data_;
};
class Matrix
{
public:
    Matrix(size_t row, size_t col):data_(col * row), rowSize_(row), colSize_(col)
    {
    }
    MatrixRow operator[](size_t column)
    {
        if (column >= colSize_)
        {
            assert(!"index out of range");
        }
        return MatrixRow(rowSize_, column, data_.data());
    }
    size_t getNumRows() const
    {
        return rowSize_;
    }
    size_t getNumCols() const
    {
        return colSize_;
    }
    bool operator==(const Matrix& other) const
    {
        if (rowSize_ != other.getNumRows() || colSize_ != other.getNumCols())
        {
            return false;
        }
        else
        {
            auto iterator_other = other.data_.begin();
            for (auto iter = data_.begin(); iter < data_.end(); iter++, iterator_other++) {
                if (*iter != *iterator_other)
                {
                    return false;
                }
            }
        }
        return true;
    }
    bool operator!=(const Matrix& matrix) const
    {
        return !(*this == matrix);
    }
    Matrix& operator*=(const double number)
    {
        for (auto iter = data_.begin(); iter < data_.end(); iter++)
        {
            *iter *= number;
        }
        return *this;
    }
    std::vector<double> operator*(const std::vector<double>& vect) const
    {
        if (vect.size() != colSize_) {
            assert(!"vector size is incorrect!");
        }

        std::vector<double> result(rowSize_);
        for (size_t i = 0; i < rowSize_; i++)
        {
            result[i] = 0;
            for (size_t j = 0; j < colSize_; j++) {
                result[i] += data_[j * rowSize_ + i] * vect[j];
            }
        }

        return result;
    }
private:
    std::vector<double> data_;
    size_t rowSize_,
           colSize_;
};

void check(bool value) {
    if (!value)
    {
        std::cout << "error" << std::endl;
        throw -1;
    }
}

void check_Shape()
{
    Matrix m(2, 3);
    check(m.getNumRows() == 2);
    check(m.getNumCols() == 3);
}

void check_GetSet()
{
    Matrix m(2, 3);

    m[0][0] = 1;
    m[1][0] = 2;
    m[2][0] = 3;
    m[0][1] = 4;
    m[1][1] = 5;
    m[2][1] = 6;

    check(m[0][0] == 1);
    check(m[1][0] == 2);
    check(m[2][0] == 3);
    check(m[0][1] == 4);
    check(m[1][1] == 5);
    check(m[2][1] == 6);

    m[2][1] = 100;

    check(m[2][1] == 100);
}

void check_MultByNum()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[1][0] = 2;
    m[2][0] = 3;
    m[0][1] = 4;
    m[1][1] = 5;
    m[2][1] = 6;

    m *= 1.5;

    check(m[0][0] == 1.5);
    check(m[1][0] == 3);
    check(m[2][0] == 4.5);
    check(m[0][1] == 6);
    check(m[1][1] == 7.5);
    check(m[2][1] == 9);

}

void check_MultByVect()
{
    std::vector<double> v = {1, 2, 3};
    Matrix m(2, 3);
    m[0][0] = 1;
    m[1][0] = 2;
    m[2][0] = 3;
    m[0][1] = 4;
    m[1][1] = 5;
    m[2][1] = 6;
    std::vector<double> result = m * v;

    check(result[0] == 14);
    check(result[1] == 32);
}

void check_IsEqual()
{
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[2][0] = 3;
    m1[0][1] = 4;
    m1[1][1] = 5;
    m1[2][1] = 6;

    Matrix m2(2, 3);
    m2[0][0] = 1;
    m2[1][0] = 2;
    m2[2][0] = 3;
    m2[0][1] = 4;
    m2[1][1] = 5;
    m2[2][1] = 6;

    check(m1 == m2);
}

void check_IsNotEqual()
{
    Matrix m1(2, 3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[2][0] = 3;
    m1[0][1] = 4;
    m1[1][1] = 5;
    m1[2][1] = 6;

    Matrix m2(2, 3);
    m2[0][0] = 0;
    m2[1][0] = 2;
    m2[2][0] = 3;
    m2[0][1] = 4;
    m2[1][1] = 5;
    m2[2][1] = 6;

    check(m1 != m2);
}
int main(int argc, char* argv[])
{
    try
    {
        check_Shape();
        check_GetSet();
        check_MultByNum();
        check_MultByVect();
        check_IsEqual();
        check_IsNotEqual();
    }
    catch(int)
    {
        return 1;
    }
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
