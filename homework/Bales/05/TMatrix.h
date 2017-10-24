#pragma once
#include <iostream>
#include <vector>

// std::vector<T> --- это вектор столбец, т.е. размерность (N, 1)
template<class T>
class TMatrix {
public:
    TMatrix(const size_t& szCol, const size_t& szRow, const T& initVal = 0);
    TMatrix(const TMatrix<T>& copyMatrix);
    TMatrix(TMatrix<T>&& moveMatrix);
    ~TMatrix() {}

    const size_t& GetSizeRow() const;
    const size_t& GetSizeCol() const;
    TMatrix<T>& operator=(const TMatrix& copyMatrix);
    TMatrix<T>& operator=(TMatrix&& moveMatrix);
    const std::vector<T>& operator[](const size_t& pos) const;
    std::vector<T>& operator[](const size_t& pos);
    bool operator==(const TMatrix<T>& compareMatrix) const;
    bool operator!=(const TMatrix<T>& compareMatrix) const;
    std::vector<T> operator*=(const std::vector<T>& vec);
    TMatrix<T> operator*=(const T& val) const;

    friend std::ostream& operator<<(std::ostream& out, const TMatrix<T>& matrix) {
        for (size_t i = 0; i < matrix._szRow; ++i) {
            for (size_t j = 0; j < matrix._szCol; ++j) {
                out << matrix._matrix[j][i] << " ";
            }
            out << std::endl;
        }
        out << "*************************************" << std::endl;
        return out;
    }
private:
    size_t _szCol;
    size_t _szRow;
    std::vector<std::vector<T> > _matrix;
};


template<class T>
TMatrix<T>::TMatrix(const size_t& szCol, const size_t& szRow, const T& initVal) : 
    _szCol(szCol), 
    _szRow(szRow) {
    this->_matrix.resize(this->_szCol, std::vector<T>(this->_szRow, initVal));
}

template<class T>
TMatrix<T>::TMatrix(const TMatrix<T>& copyMatrix) :
    _szCol(copyMatrix._szCol),
    _szRow(copyMatrix._szRow),
    _matrix(copyMatrix._matrix) {
}

template<class T>
TMatrix<T>::TMatrix(TMatrix<T>&& moveMatrix) : 
    _szCol(moveMatrix._szCol), 
    _szRow(moveMatrix._szRow), 
    _matrix(std::move(moveMatrix._matrix)) {
    moveMatrix._szCol = moveMatrix._szRow = 0;
}

template<class T>
const size_t& TMatrix<T>::GetSizeRow() const {
    return this->_szRow;
}

template<class T>
const size_t& TMatrix<T>::GetSizeCol() const {
    return this->_szCol;
}

template<class T>
const std::vector<T>& TMatrix<T>::operator[](const size_t& pos) const {
    if (pos >= this->_szCol) {
        std::cerr << "Error: index out of range " << __LINE__ << std::endl;
        return this->_matrix.back();
    }
    return this->_matrix[pos];
}

template<class T>
std::vector<T>& TMatrix<T>::operator[](const size_t& pos) {
    if (pos >= this->_szCol) {
        std::cerr << "Error: index out of range " << __LINE__ << std::endl;
        return this->_matrix.back();
    }
    return this->_matrix[pos];
}

template<class T>
bool TMatrix<T>::operator==(const TMatrix<T>& compareMatrix) const {
    if (this->_szRow != compareMatrix._szRow
        || this->_szCol != compareMatrix._szCol)
        return false;
    for (size_t i = 0; i < this->_szCol; ++i) {
        for (size_t j = 0; j < this->_szRow; ++j) {
            if (this->_matrix[i][j] != compareMatrix[i][j])
                return false;
        }
    }
    return true;
}

template<class T>
bool TMatrix<T>::operator!=(const TMatrix<T>& compareMatrix) const {
    return !(*this == compareMatrix);
}

template<class T>
std::vector<T> TMatrix<T>::operator*=(const std::vector<T>& vec) {
    std::vector<T> res(this->_szRow, 0);
    if (vec.size() != this->_szCol) {
        std::cerr << "Error: unmatched dimensions " << __LINE__ << std::endl;
        return res;
    }
    for (size_t i = 0; i < this->_szRow; ++i) {
        for (size_t j = 0; j < this->_szCol; ++j) {
            res[i] += this->_matrix[j][i] * vec[j];
        }
    }
    return res;
}

template<class T>
TMatrix<T> TMatrix<T>::operator*=(const T& val) const {
    TMatrix<T> tmp(this->_szCol, this->_szRow);
    for (size_t i = 0; i < this->_szCol; ++i) {
        for (size_t j = 0; j < this->_szRow; ++j) {
            tmp[i][j] = this->_matrix[i][j] * val;
        }
    }
    return tmp;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator=(const TMatrix& copyMatrix) {
    this->_szCol = copyMatrix._szCol;
    this->_szRow = copyMatrix._szRow;
    this->_matrix = copyMatrix._matrix;
    return *this;
}

template<class T>
TMatrix<T>& TMatrix<T>::operator=(TMatrix&& moveMatrix) {
    this->_szCol = moveMatrix._szCol;
    this->_szRow = moveMatrix._szRow;
    this->_matrix = std::move(moveMatrix._matrix);
    moveMatrix._szCol = moveMatrix._szRow = 0;
    return *this;
}