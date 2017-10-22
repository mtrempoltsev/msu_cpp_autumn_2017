#include <iostream>
#include <vector>

template<class T>
class Matrix
{
private:

    size_t ncol_ = 0, nrow_ = 0;

    std::vector<std::vector<T> > matr_;

    // прокси класс строки в матрице для оператора [], содержит указатель на начало строки в матрице и размер строки
    class Matrix_row
    {
    public:
        Matrix_row(typename std::vector<T>::iterator row_begin, size_t size): row_begin_(row_begin), size_(size) {};

        T& operator[](size_t ind)
        {
            if (ind >= size_)
                throw "index out of range";
            return *(row_begin_ + ind);
        }
    private:
        const typename std::vector<T>::iterator row_begin_;
        const size_t size_;
    };
public:
    Matrix(size_t rows, size_t cols): ncol_(cols), nrow_(rows)
    {
        matr_.resize(nrow_);
        for (size_t i = 0; i < nrow_; i++)
            matr_[i].resize(ncol_);
    }

    Matrix(const Matrix<T>& copied)
    {
        if (this == &copied)
            return;

        ncol_ = copied.get_ncol();
        nrow_ = copied.get_nrow();
        matr_ = copied.matr_;
    }

    Matrix& operator=(const Matrix<T>& copied)
    {
        if (this == &copied)
            return *this;

        nrow_ = copied.get_nrow();
        ncol_ = copied.get_ncol();
        matr_.clear();
        matr_ = copied.matr_;
        return *this;
    }

    Matrix(Matrix<T>&& movied)
    {
        if (this == &movied)
            return;

        ncol_ = movied.ncol_;
        nrow_ = movied.nrow_;
        movied.nrow_ = movied.ncol_ = 0;
        matr_ = std::move(movied.matr_);
    }

    Matrix& operator=(Matrix<T>&& movied)
    {
        if (this == &movied)
            return *this;

        ncol_ = movied.ncol_;
        nrow_ = movied.nrow_;
        movied.nrow_ = movied.ncol_ = 0;
        matr_.clear();
        matr_ = std::move(movied.matr_);
        return *this;
    }

    Matrix_row operator[](size_t ind)
    {
        if (ind >= nrow_)
            throw "index out of range";

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

    Matrix operator*(T mul) const
    {
        Matrix<T> res(nrow_, ncol_);

        for (size_t i = 0; i < nrow_; i++)
            for (size_t j = 0; j < ncol_; j++)
                res[i][j] = matr_[i][j] * mul;

        return res;
    }

    std::vector<T> operator*(const std::vector<T>& vec) const
    {
        if (vec.size() != ncol_)
            throw "wrong size of vector in multiply";
        std::vector<T> res(nrow_);

        for (size_t i = 0; i < nrow_; i++)
        {
            T temp = 0;
            for (size_t j = 0; j < ncol_; j++)
                temp += matr_[i][j] * vec[j];
            res[i] = temp;
        }

        return res;
    }

    bool operator==(const Matrix<T>& right) const
    {
        if (nrow_ != right.nrow_ || ncol_ != right.ncol_)
            throw "wrong sizes in compare";

        for (size_t i = 0; i < nrow_; i++)
            for (size_t j = 0; j < ncol_; j++)
                if (matr_[i][j] != right.matr_[i][j])
                    return false;
        return true;
    }

    bool operator!=(const Matrix<T>& right) const
    {
        return !(*this==right);
    }

    friend std::ostream& operator<<(std::ostream& stream, Matrix<T>& matrix) {
        for (size_t i = 0; i < matrix.nrow_; i++) {
            for (size_t j = 0; j < matrix.ncol_; j++)
                stream << matrix[i][j] << ' ';
            stream << std::endl;
        }
        return stream;
    }

};
