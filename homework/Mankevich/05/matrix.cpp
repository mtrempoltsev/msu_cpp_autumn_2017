#include <iostream>
#include <vector>
#include <cassert>
#include <stdexcept>

template <class T> 
class MatrixRow{
public:
    MatrixRow(size_t col_size, T* data):
        col_size_(col_size),
        data_(data){};
    ~MatrixRow(){};
    T& operator[](size_t col);
    const T& operator[](size_t col) const;
private:
    size_t col_size_;
    T* data_;
};

template <class T>
class Matrix{
public:
    Matrix(size_t row_size, size_t col_size):
        row_size_(row_size),
        col_size_(col_size),
        data_(new T[row_size * col_size]){};
    ~Matrix(){
        if (data_ != nullptr)
            delete []data_;
    }
    Matrix(const Matrix<T>& m);
    Matrix(Matrix<T>&& m);
    MatrixRow<T> operator[](size_t row);
    const MatrixRow<T> operator[](size_t row) const;
    void set_value(T value);
    Matrix<T>& operator=(const Matrix<T>& matr);
    Matrix<T>& operator=(Matrix<T>&& movied);
    Matrix<T>& operator*=(const std::vector<T>& v);
    Matrix<T>& operator*=(const T& num);
    bool operator==(const Matrix<T> &matr) const;
    bool operator!=(const Matrix<T> &matr) const;
    size_t get_row_size() const;
    size_t get_col_size() const;
    template <class M>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<M>& matr);
private:
    size_t row_size_;
    size_t col_size_;
    T* data_;
};

template <class T>
Matrix<T>::Matrix(const Matrix<T>& m){
    row_size_ = m.row_size_;
    col_size_ = m.col_size_;
    data_ = new T[col_size_ * row_size_];
    for (size_t i = 0; i < col_size_ * row_size_; ++i)
        data_[i] = m.data_[i];
}

template <class T>
Matrix<T>::Matrix(Matrix<T>&& m){
    row_size_ = m.row_size_;
    col_size_ = m.col_size_;
    m.col_size_ = 0;
    m.row_size_ = 0;
    data_ = m.data_;
    m.data_ = nullptr;
}

template <class T>
T& MatrixRow<T>::operator[](size_t col){
    if (col >= col_size_)
        throw std::invalid_argument("index out of range");
    return data_[col];
}

template <class T>
const T& MatrixRow<T>::operator[](size_t col) const{
    if (col >= col_size_)
        throw std::invalid_argument("index out of range");
    return data_[col];
}

template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m){
    if (this == &m)
        return *this;
    delete []data_;
    row_size_ = m.row_size_;
    col_size_ = m.col_size_;
    data_ = new T[col_size_ * row_size_];
    for (size_t i = 0; i < col_size_ * row_size_; ++i)
        data_[i] = m.data_[i];
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& movied){
    if (this == &movied)
        return *this;
    delete []data_;
    row_size_ = movied.row_size_;
    col_size_ = movied.col_size_;
    movied.col_size_ = 0;
    movied.row_size_ = 0;
    data_ = movied.data_;
    movied.data_ = nullptr;
    return *this;
}

template <class T>
size_t Matrix<T>::get_row_size() const{
    return row_size_;
}

template <class T>
size_t Matrix<T>::get_col_size() const{
    return col_size_;
}

template <class T>
void Matrix<T>::set_value(T value){
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
            data_[i * col_size_ + j] = value;
}

template <class T>
MatrixRow<T> Matrix<T>::operator[](size_t row){
    if (row >= row_size_)
        throw std::invalid_argument("index out of range");
    return MatrixRow<T>(col_size_, &data_[col_size_ * row]);
}

template <class T>
const MatrixRow<T> Matrix<T>::operator[](size_t row) const{
    if (row >= row_size_)
        throw std::invalid_argument("index out of range");
    return MatrixRow<T>(col_size_, &data_[col_size_ * row]);
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const std::vector<T>& v){
    if (v.size() != row_size_)
        throw std::invalid_argument("unmatched dimensions");
    
    T* new_data = new T[row_size_];
    for (size_t i = 0; i < row_size_; ++i){
        new_data[i] = 0;
        for (size_t j = 0; j < col_size_; ++j)
            new_data[i] += data_[i * col_size_ + j] * v[j];
    
    }
    delete []data_;
    data_ = new_data;
    col_size_ = 1;
    return *this;
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T& num){
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
            data_[i * col_size_ + j] *= num;
    return *this;
}

template <class T>
bool Matrix<T>::operator==(const Matrix<T> &matr) const{
    if (matr.row_size_ != row_size_ || matr.col_size_ != col_size_)
        return 0;
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
            if (data_[i * col_size_ + j] != matr.data_[i * col_size_ + j])
                return 0;
    return 1;
}

template <class T>
bool Matrix<T>::operator!=(const Matrix<T> &matr) const{
    if (matr.row_size_ != row_size_ || matr.col_size_ != col_size_)
        return 1;
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
        if (data_[i * row_size_ + j] != matr.data_[i * row_size_ + j])
                return 1;
    return 0;
}

template <class T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matr){
    for (size_t i = 0; i < matr.row_size_; ++i){
        for (size_t j = 0; j < matr.col_size_; ++j){
            out << matr[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

