#include "Matrix.h"



template<typename T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{	
	n_rows = rows;
	n_cols = cols;
	A = new T* [n_rows];
    for(size_t i = 0; i < n_rows; i++)
    {
        A[i] = new T [n_cols];
    }
}

template<typename T>
Matrix<T>::~Matrix()
{	
	for(size_t i = 0; i < n_rows; i++)
    {	
        delete[] A[i];
    }
    delete[] A;  
}

template<typename T>
size_t Matrix<T>::get_n_rows()
{
	return n_rows;
}

template<typename T>
size_t Matrix<T>::get_n_cols()
{
	return n_cols;
}

template<typename T>
Matrixrow<T> Matrix<T>::operator[](size_t row)
{	
	assert(row < n_rows && row >= 0);
	return Matrixrow<T>(A[row], n_cols);
}

template<typename T>
Matrix<T> Matrix<T>::operator*(T value)
{	
	Matrix C(n_rows, n_cols);
	for(size_t i = 0; i < n_rows; i++)
	{
		for(size_t j = 0; j < n_cols; j++)
		{
			C[i][j] = A[i][j] * value;
		}
	}
	return C;
}

template<typename T>
bool Matrix<T>::operator==(Matrix<T>& B) 
{	
	if (n_rows != B.get_n_rows())
	{
		return false;
	}
	if (n_cols != B.get_n_cols()) 
	{
		return false;
	}

    for (size_t i = 0; i < n_rows; ++i)
    {
    	for (size_t j = 0; j < n_cols; ++j)
    	{
    		if (A[i][j] != B[i][j])
    		{
    			return false;	
    		} 
    	}
    }
                
    return true;
}

template<typename T>
bool Matrix<T>::operator!=(Matrix<T>& B) 
{	
	if (n_rows != B.get_n_rows()) 
	{
		return true;
	}
	if (n_cols != B.get_n_cols()) 
	{
		return true;
	}

    for (size_t i = 0; i < n_rows; ++i)
    {
    	for (size_t j = 0; j < n_cols; ++j)
    	{
    		if (A[i][j] != B[i][j])
    		{
    			return true;
    		}
    	}
    }
                
    return false;
}

template<typename T>
vector<T> Matrix<T>::operator*(vector<T> v)
{
	assert(v.size() == n_cols);
	vector<T> res(n_rows);


	for(size_t i = 0; i < n_rows; i++)
	{	
		res[i] = 0;
		for(size_t j = 0; j < n_cols; j++)
		{
			res[i] += A[i][j] * v[j];
		}
	}

	return res;
}

template<typename T>
Matrixrow<T>::Matrixrow(T* row, size_t col_size)
{
	Arow = row;
	size = col_size;
}

template<typename T>
T& Matrixrow<T>::operator[](size_t col)
{	
	assert(col < size && col >= 0);
	return Arow[col];
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& copied)
{	
	n_rows = copied.n_rows;
	n_cols = copied.n_cols;
	A = new T* [n_rows];
    for(size_t i = 0; i < n_rows; i++)
    {	
        A[i] = new T [n_cols];
    }

    for(size_t i = 0; i < n_rows; i++)
    {
        std::copy(copied.A[i], copied.A[i] + n_cols, A[i]);
    }

}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& movied)
{
	n_rows = movied.n_rows;
	n_cols = movied.n_cols;
	A = movied.A;

	movied.A = nullptr;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& copied)
{
	if (this == &copied)
	{
        return *this;
	}

	for(size_t i = 0; i < n_rows; i++)
    {	
        delete[] A[i];
    }
    delete[] A; 

	n_rows = copied.n_rows;
	n_cols = copied.n_cols;
	A = new T* [n_rows];
    for(size_t i = 0; i < n_rows; i++)
    {	
        A[i] = new T [n_cols];
    }

    for(size_t i = 0; i < n_rows; i++)
    {
        std::copy(copied.A[i], copied.A[i] + n_cols, A[i]);
    }

    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& movied)
{
	if (this == &movied)
	{
            return *this;
	}

	for(size_t i = 0; i < n_rows; i++)
    {	
        delete[] A[i];
    }
    delete[] A; 

    n_rows = movied.n_rows;
    n_cols = movied.n_cols;
    A = movied.A;

    movied.A = nullptr;

   	return *this;
}