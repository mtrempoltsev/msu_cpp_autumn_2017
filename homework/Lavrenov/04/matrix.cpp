#include "matrix.h"
#include <cstdlib>
#include <exception>

Matrix::Matrix(unsigned int columns, unsigned  int rows)
{
    this->columns = columns;
    this->rows = rows;
    values = new vec[columns];
    for(int i = 0;i < columns; ++i){
        values[i] = vec(rows);
    }
}

Matrix::Matrix(const Matrix& m){
    rows = m.getRowsNum();
    columns = m.getColumnsNum();
    values = new vec[columns];
    for(unsigned int i = 0; i < columns; ++i){
        values[i] = vec(rows);
        for(unsigned int j = 0; j < rows; ++j){
            values[i][j] = m[i][j];
        }
    }
}

Matrix::vec::vec(unsigned int rows){
    this->rows = rows;
    values = new double[rows];
}

Matrix::vec::vec(){
    values = NULL;
}

Matrix::vec::vec(const Matrix::vec& v){
    this->rows = v.rows;
    for(int i = 0; i < this->rows; ++i){
        values[i] = v[i];
    }
}

Matrix::vec& Matrix::vec::operator=(const Matrix::vec& v){
    this->rows = v.rows;
    if(values != NULL)
        delete[] values;
    values = new double[rows];
    for(int i = 0; i < this->rows; ++i){
        values[i] = v[i];
    }
    return *this;
}

Matrix::~Matrix()
{
    delete[] values;
}

Matrix::vec::~vec()
{
    delete[] values;
}

Matrix::vec& Matrix::operator[](unsigned int i){
    if(i >= columns){
        throw std::exception();
    }
    return values[i];
}

double& Matrix::vec::operator[](unsigned int i){
    if(i >= rows){
        throw std::exception();
    }
    return values[i];
}

const Matrix::vec& Matrix::operator[](unsigned int i) const{
    if(i >= columns){
        throw std::exception();
    }
    return values[i];
}

const double& Matrix::vec::operator[](unsigned int i) const{
    if(i >= rows){
        throw std::exception();
    }
    return values[i];
}

unsigned int Matrix::getRowsNum() const{
    return rows;
}

unsigned int Matrix::getColumnsNum() const{
    return columns;
}

bool Matrix::operator==(const Matrix& m) const{
    if(this->columns != m.columns)
        return false;
    if(this->rows != m.rows)
        return false;
    for(unsigned int i = 0; i < columns; ++i){
        for(unsigned int j = 0; j < rows; ++j){
            if((*this)[i][j] != m[i][j])
                return false;
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& m) const{
    return !(*this == m);
}

Matrix Matrix::operator*(double k) const{
    Matrix res = *this;
    for(unsigned int i = 0; i < columns; ++i){
        for(unsigned int j = 0; j < rows; ++j){
            res[i][j] *= k;
        }
    }
    return res;
}

std::vector<double> Matrix::operator*(const std::vector<double>& v) const{

    if(v.size() != columns){
        throw std::exception();
    }
    std::vector<double> res;
    for(unsigned int i = 0; i < rows; ++i){
        double summ = 0;
        for(unsigned int j = 0; j < columns; ++j){
            summ += (*this)[j][i] * v[j];
        }
        res.push_back(summ);
    }
    return res;
}

Matrix& Matrix::operator*=(double k){
    for(unsigned int i = 0; i < columns; ++i){
        for(unsigned int j = 0; j < rows; ++j){
            (*this)[i][j] *= k;
        }
    }
    return *this;
}

void Matrix::setToIdentity(){
    for(unsigned int i = 0; i < columns; ++i){
        for(unsigned int j = 0; j < rows; ++j){
            if(i == j){
                (*this)[i][j] = 1;
            }else{
                (*this)[i][j] = 0;
            }
        }
    }
}
