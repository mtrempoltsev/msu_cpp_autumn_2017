#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

template<typename T>
class Matrix
{
public:
    class vec{
    public:
        vec();
        vec(unsigned int);
        vec(const vec&);
        ~vec();
        vec& operator=(const vec&);
        T& operator[](unsigned int i);
        const T& operator[](unsigned int i) const;
    private:
        unsigned int rows;
        T* values;
    };
public:
    Matrix(unsigned int, unsigned int);
    Matrix(const Matrix&);
    Matrix(Matrix&& movied);

    Matrix& operator=(const Matrix&);
    Matrix& operator=(Matrix&& movied);

    Matrix::vec& operator[](unsigned int i);
    const Matrix::vec& operator[](unsigned int i) const;

    Matrix operator*(T) const;
    std::vector<T> operator*(const std::vector<T>&) const;
    Matrix& operator*=(T);

    bool operator==(const Matrix&) const;
    bool operator!=(const Matrix&) const;

    unsigned int getRowsNum() const;
    unsigned int getColumnsNum() const;

    virtual ~Matrix();
private:

    unsigned int rows;
    unsigned int columns;
    vec* values;
};

#include <cstdlib>
#include <exception>

//****************help class vec realisation*******************

template<typename T>
Matrix<T>::vec::vec(unsigned int rows){
    this->rows = rows;
    values = new T[rows];
}

template<typename T>
Matrix<T>::vec::vec(){
    this->rows = 0;
    values = NULL;
}

template<typename T>
Matrix<T>::vec::vec(const Matrix<T>::vec& v){
    this->rows = v.rows;
    for(int i = 0; i < this->rows; ++i){
        values[i] = v[i];
    }
}

template<typename T>
typename Matrix<T>::vec& Matrix<T>::vec::operator=(const Matrix<T>::vec& v){
    this->rows = v.rows;
    if(this == &v)
        return *this;
    if(values != NULL)
        delete[] values;
    values = new T[rows];
    for(int i = 0; i < this->rows; ++i){
        values[i] = v[i];
    }
    return *this;
}

template<typename T>
T& Matrix<T>::vec::operator[](unsigned int i){
    if(i >= rows){
        throw std::exception();
    }
    return values[i];
}

template<typename T>
const T& Matrix<T>::vec::operator[](unsigned int i) const{
    if(i >= rows){
        throw std::exception();
    }
    return values[i];
}

template<typename T>
Matrix<T>::vec::~vec()
{
    delete[] values;
}

//****************Matrix realisation***************************

template<typename T>
Matrix<T>::Matrix(unsigned int columns, unsigned  int rows)
{
    this->columns = columns;
    this->rows = rows;
    values = new vec[columns];
    for(int i = 0;i < columns; ++i){
        values[i] = vec(rows);
    }
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& m){
    rows = m.getRowsNum();
    columns = m.getColumnsNum();
    //new vec[3];
    values = new vec[columns];
    for(unsigned int i = 0; i < columns; ++i){
        values[i] = vec(rows);
        for(unsigned int j = 0; j < rows; ++j){
            values[i][j] = m[i][j];
        }
    }
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& movied){
    rows = movied.rows;
    columns = movied.columns;
    values = movied.values;

    movied.values = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& movied){
    if (this == &movied)
        return *this;
    delete[] values;
    rows = movied.rows;
    columns = movied.columns;
    values = movied.values;

    movied.values = nullptr;
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m){
    if(&m == this)
        return *this;
    rows = m.getRowsNum();
    columns = m.getColumnsNum();
    delete[] values;
    values = new vec[columns];
    for(unsigned int i = 0; i < columns; ++i){
        values[i] = m[i];
    }
    return *this;
}

template<typename T>
typename Matrix<T>::vec& Matrix<T>::operator[](unsigned int i){
    if(i >= columns){
        throw std::exception();
    }
    return values[i];
}

template<typename T>
const typename Matrix<T>::vec& Matrix<T>::operator[](unsigned int i) const{
    if(i >= columns){
        throw std::exception();
    }
    return values[i];
}

template<typename T>
unsigned int Matrix<T>::getRowsNum() const{
    return rows;
}

template<typename T>
unsigned int Matrix<T>::getColumnsNum() const{
    return columns;
}

template<typename T>
bool Matrix<T>::operator==(const Matrix<T>& m) const{
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

template<typename T>
bool Matrix<T>::operator!=(const Matrix<T>& m) const{
    return !(*this == m);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T k) const{
    Matrix res = *this;
    for(unsigned int i = 0; i < columns; ++i){
        for(unsigned int j = 0; j < rows; ++j){
            res[i][j] *= k;
        }
    }
    return res;
}

template<typename T>
std::vector<T> Matrix<T>::operator*(const std::vector<T>& v) const{

    if(v.size() != columns){
        throw std::exception();
    }
    std::vector<T> res;
    for(unsigned int i = 0; i < rows; ++i){
        double summ = 0;
        for(unsigned int j = 0; j < columns; ++j){
            summ += (*this)[j][i] * v[j];
        }
        res.push_back(summ);
    }
    return res;
}

template<typename T>
Matrix<T>& Matrix<T>::operator*=(T k){
    for(unsigned int i = 0; i < columns; ++i){
        for(unsigned int j = 0; j < rows; ++j){
            (*this)[i][j] *= k;
        }
    }
    return *this;
}

template<typename T>
Matrix<T>::~Matrix()
{
    delete[] values;
}
#endif // MATRIX_H
