#ifndef MATRIXCOLUMN_H
#define MATRIXCOLUMN_H

#include <cstdio>

template <class T>
class MatrixColumn
{
public:
    MatrixColumn(size_t size, T*& data)
        : rows_(size)
        , data_(data)
    {}

    const T operator[](size_t j) const
    {
	if(j >= rows_)
	    throw "Column error: index out of range";

	return data_[j];
    }

    T& operator[](size_t j)
    {
	if(j >= rows_)
	    throw "Column error: index out of range";

	return data_[j];
    }

private:
    size_t rows_; //количество элементов в столбце (== количество строк в матрице)
    T* data_; //элемменты столбца
};

#endif // MATRIXCOLUMN_H
