#include <iostream>
#include <vector>

template<class T>
class MatrixRow
{
public:
    MatrixRow<T>(size_t rowSize, size_t col, T* data):rowSize_(rowSize), col_(col), data_(data)
    {
    }
    T& operator[](size_t row)
    {
        if (row >= rowSize_)
        {
            throw -1;                        // index out of range
        }
        return data_[col_ * rowSize_ + row];
    }
private:
    size_t  rowSize_,
            col_;
    T* data_;
};

template<class T>
class Matrix
{
public:
    Matrix(size_t row, size_t col):data_(col * row), rowSize_(row), colSize_(col)
    {
    }
    MatrixRow<T> operator[](size_t column)
    {
        if (column >= colSize_)
        {
            throw -1;
        }
        return MatrixRow<T>(rowSize_, column, data_.data());
    }
    size_t getNumRows() const
    {
        return rowSize_;
    }
    size_t getNumCols() const
    {
        return colSize_;
    }
    bool operator==(const Matrix<T>& other) const
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


    Matrix(const Matrix& copied)
    {
        if (this == &copied)
            return;

        rowSize_ = copied.rowSize_;
        colSize_ = copied.colSize_;
        data_ = copied.data_;
    }

    Matrix& operator=(const Matrix& copied)
    {
        if (this == &copied)
            return *this;

        data_.clear();
        data_  = copied.data_;
        rowSize_ = copied.rowSize_;
        colSize_ = copied.colSize_;
        return *this;
    }

    Matrix(Matrix&& movied)
    {
        if (this == &movied)
            return;

        rowSize_ = std::move(movied.rowSize_);
        colSize_ = std::move(movied.colSize_);
        data_ = std::move(movied.data_);
    }

    Matrix& operator=(Matrix&& movied)
    {
        if (this == &movied)
            return *this;

        data_.clear();
        rowSize_ = std::move(movied.rowSize_);
        colSize_ = std::move(movied.colSize_);
        data_ = std::move(movied.data_);
        return *this;
    }


    std::vector<T> operator*(const std::vector<T>& vect) const
    {
        if (vect.size() != colSize_)
        {
            throw -3;                           // vector size is incorrect
        }

        std::vector<T> result(rowSize_);
        for (size_t i = 0; i < rowSize_; i++)
        {
            result[i] = 0;
            for (size_t j = 0; j < colSize_; j++)
            {
                result[i] += data_[j * rowSize_ + i] * vect[j];
            }
        }
        return result;
    }
private:
    std::vector<T> data_;
    size_t rowSize_,
           colSize_;
};

void check(bool value) {
    if (!value)
    {
        throw -2;                   // error
    }
}

void check_Shape()
{
    Matrix<double> m(2, 3);
    check(m.getNumRows() == 2);
    check(m.getNumCols() == 3);
}

void check_GetSet()
{
    Matrix<int> m(2, 3);

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

void check_Copying()
{
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[1][0] = 2;
    m[2][0] = 3;
    m[0][1] = 4;
    m[1][1] = 5;
    m[2][1] = 6;

    Matrix<double> m1 = m;
    check(m == m1);

    Matrix<double> m2(2, 3);
    m2 = m;
    check(m == m2);
}

void check_Moving()
{
    Matrix<double> m(2, 3);
    m[0][0] = 1;
    m[1][0] = 2;
    m[2][0] = 3;
    m[0][1] = 4;
    m[1][1] = 5;
    m[2][1] = 6;

    Matrix<double> m1 = m;
    Matrix<double> m2(std::move(m));
    check(m1 == m2);

    Matrix<double> m3(2, 3);
    m3 = std::move(m2);
    check(m3 == m1);
}

void check_MultByNum()
{
    Matrix<double> m(2, 3);
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
    Matrix<double> m(2, 3);

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
    Matrix<int> m1(2, 3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[2][0] = 3;
    m1[0][1] = 4;
    m1[1][1] = 5;
    m1[2][1] = 6;

    Matrix<int> m2(2, 3);
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
    Matrix<int> m1(2, 3);
    m1[0][0] = 1;
    m1[1][0] = 2;
    m1[2][0] = 3;
    m1[0][1] = 4;
    m1[1][1] = 5;
    m1[2][1] = 6;

    Matrix<int> m2(2, 3);
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
        check_Copying();
        check_Moving();
        check_MultByNum();
        check_MultByVect();
        check_IsEqual();
        check_IsNotEqual();
    }
    catch(int i)
    {
        if (i == -1)
        {
            std::cout << "Index out of range!" << std::endl;
        }
        else if (i == -2)
        {
            std::cout << "Error!" << std::endl;
        }
        else
        {
            std::cout << "vector size is incorrect!" << std::endl;
        }
        return 1;
    }
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}
