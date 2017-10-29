#ifndef MATRIXCOLUMN_H
#define MATRIXCOLUMN_H

#include <cstdio>

class MatrixColumn
{
public:
    MatrixColumn(size_t size, double*& data)
        : rows_(size)
        , data_(data)
    {}

    double& operator[](size_t j) const
    {
        if(j >= rows_)
            throw "Column error: index out of range";

        return data_[j];
    }

private:
    size_t rows_; //количество элементов в столбце (== количество строк в матрице)
    double* data_; //элемменты столбца
};

#endif // MATRIXCOLUMN_H
