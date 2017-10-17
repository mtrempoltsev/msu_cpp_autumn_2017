#include "TMatrix.h"


TMatrix::TMatrix(const size_t& szCol, const size_t& szRow, const TItem& initVal) 
    : _szCol(szCol), _szRow(szRow) {
    _matrix.resize(szCol, m_vector(szRow, initVal));
}

TMatrix::~TMatrix() {

}

const size_t& TMatrix::GetSizeRow() const {
    return this->_szRow;
}

const size_t& TMatrix::GetSizeCol() const {
    return this->_szCol;
}

const m_vector& TMatrix::operator[](const size_t& pos) const {
    if (pos >= this->_szCol)
        assert(!"index out of range");
    return this->_matrix[pos];
}

m_vector& TMatrix::operator[](const size_t& pos) {
    if (pos >= this->_szCol)
        assert(!"index out of range");
    return this->_matrix[pos];
}

bool TMatrix::operator==(const TMatrix& anotherMatrix) const {
    if (this->_szRow != anotherMatrix.GetSizeRow() 
        || this->_szCol != anotherMatrix.GetSizeCol())
        return false;
    for (size_t i = 0; i < this->_szCol; ++i) {
        for (size_t j = 0; j < this->_szRow; ++j) {
            if (this->_matrix[i][j] != anotherMatrix[i][j])
                return false;
        }
    }
    return true;
}

bool TMatrix::operator!=(const TMatrix& anotherMatrix) const {
    return !(*this == anotherMatrix);
}

m_vector TMatrix::operator*=(const m_vector& vec) {
    if (vec.size() != this->_szCol)
        assert(!"unmatched dimensions");
    m_vector tmp(this->_szRow, TItem(0));
    for (size_t i = 0; i < this->_szRow; ++i) {
        for (size_t j = 0; j < this->_szCol; ++j) {
            tmp[i] += this->_matrix[j][i] * vec[j];
        }
    }
    return tmp;
}

TMatrix TMatrix::operator*=(const TItem& val) {
    TMatrix tmp(this->_szCol, this->_szRow);
    for (size_t i = 0; i < this->_szCol; ++i) {
        for (size_t j = 0; j < this->_szRow; ++j) {
            tmp[i][j] = this->_matrix[i][j] * val;
        }
    }
    return tmp;
}

std::ostream& operator<<(std::ostream& out, const TMatrix& matrix) {
    for (size_t i = 0; i < matrix._szRow; ++i) {
        for (size_t j = 0; j < matrix._szCol; ++j) {
            out << matrix._matrix[j][i] << " ";
        }
        out << std::endl;
    }
    out << "*************************************" << std::endl;
    return out;
}