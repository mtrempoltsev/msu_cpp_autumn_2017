#include "matrix.hpp"

double& MatrixRow::operator[](size_t col){
    if (col >= col_size_)
        assert(!"index out of range");
    return data_[row_ * col_size_ + col];
}

const double& MatrixRow::operator[](size_t col) const{
    if (col >= col_size_)
        assert(!"index out of range");
    return data_[row_ * col_size_ + col];
}

size_t Matrix::get_row_size() const{
    return row_size_;
}

size_t Matrix::get_col_size() const{
    return col_size_;
}

void Matrix::set_value(double value){
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
            data_[i * col_size_ + j] = value;
}

MatrixRow Matrix::operator[](size_t row){
    if (row >= row_size_)
        assert(!"index out of range");
    return MatrixRow(row_size_, col_size_, row, data_);
}

const MatrixRow Matrix::operator[](size_t row) const{
    if (row >= row_size_)
        assert(!"index out of range");
    return MatrixRow(row_size_, col_size_, row, data_);
}

Matrix& Matrix::operator*=(const std::vector<double> v){
    if (v.size() != row_size_)
        assert(!"unmatched dimensions");
    
    double* new_data = new double[row_size_];
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
    
Matrix& Matrix::operator*=(const double num){
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
            data_[i * col_size_ + j] *= num;
    return *this;
}
        
bool Matrix::operator==(const Matrix &matr) const{
    if (matr.row_size_ != row_size_ || matr.col_size_ != col_size_)
        return 0;
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
            if (data_[i * col_size_ + j] != matr.data_[i * col_size_ + j])
                return 0;
    return 1;
}
     
bool Matrix::operator!=(const Matrix &matr) const{
    if (matr.row_size_ != row_size_ || matr.col_size_ != col_size_)
        return 1;
    for (size_t i = 0; i < row_size_; ++i)
        for (size_t j = 0; j < col_size_; ++j)
        if (data_[i * row_size_ + j] != matr.data_[i * row_size_ + j])
                return 1;
    return 0;
}
        
std::ostream& operator<<(std::ostream& out, const Matrix& matr){
    for (size_t i = 0; i < matr.row_size_; ++i){
        for (size_t j = 0; j < matr.col_size_; ++j){
            out << matr[i][j] << " ";
        }
        out << std::endl;
    }
    return out;
}

