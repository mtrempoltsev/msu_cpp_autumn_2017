#pragma once
#include <iostream>
#include <vector>
#include <cassert>

using TItem = double;
using m_vector = std::vector<TItem>;

// std::vector<T> --- это вектор столбец, т.е. размерность (N, 1)
class TMatrix {
public:
    TMatrix(const size_t& szCol, const size_t& szRow, const TItem& initVal = 0);
    ~TMatrix();

    const size_t& GetSizeRow() const;
    const size_t& GetSizeCol() const;
    const m_vector& operator[](const size_t& pos) const;
    m_vector& operator[](const size_t& pos);
    bool operator==(const TMatrix& anotherMatrix) const;
    bool operator!=(const TMatrix& anotherMatrix) const;
    m_vector operator*=(const m_vector& vec);
    TMatrix operator*=(const TItem& val);

    friend std::ostream& operator<<(std::ostream& out, const TMatrix& matrix);
private:
    const size_t _szCol;
    const size_t _szRow;
    std::vector<m_vector> _matrix;
};