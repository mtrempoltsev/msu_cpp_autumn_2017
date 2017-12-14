#include "row.hpp"
#include <vector>
#include <cassert>

template <class T>
class Matrix
{
	std::vector<Row<T>> vec;
public:
	Matrix(size_t, size_t);
	Matrix(const Matrix<T>&);
	Matrix(Matrix<T>&&);

	Matrix<T>& operator= (const Matrix<T>&);
	Matrix<T>& operator= (Matrix<T>&&);

	Row<T>& operator[] (size_t);
	const Row<T>& operator[] (size_t) const;
	Matrix& operator*= (T);
	Matrix& operator*= (const std::vector<T>&);
	size_t getRows() const {return vec.size();}
	size_t getCols() const {return vec[0].getLength();}
	bool operator == (const Matrix&) const;
	bool operator != (const Matrix& m) const {return !(this->operator==(m));}
};

template <class T>
Matrix<T>::Matrix(size_t rows, size_t cols)
{
	if (rows == 0 || cols == 0) {
		assert(!"zero rows or columns");
	}
	vec.resize(rows, Row<T>(cols));
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& mtrx)
{
	vec.resize(mtrx.getRows());
	auto mtrxIt = mtrx.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++mtrxIt) {
		*it = *mtrxIt;
	}
}

template <class T>
Matrix<T>::Matrix(Matrix<T>&& mtrx)
{
	vec = mtrx.vec;
}

template <class T> Matrix<T>&
Matrix<T>::operator= (const Matrix<T>& mtrx)
{
	vec.clear();
	vec.resize(mtrx.getRows());
	auto mtrxIt = mtrx.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++mtrxIt) {
		*it = *mtrxIt;
	}
	return *this;
}

template <class T> Matrix<T>&
Matrix<T>::operator= (Matrix<T>&& mtrx)
{
	vec = mtrx.vec;
	return *this;
}

template <class T> Row<T>&
Matrix<T>::operator[] (size_t index)
{
	if (index >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[index];
}

template <class T> const Row<T>&
Matrix<T>::operator[] (size_t index) const
{
	if (index >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[index];
}

template <class T> Matrix<T>&
Matrix<T>::operator *= (T coef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->multByNumber(coef);
	}
	return *this;
}

template <class T> Matrix<T>&
Matrix<T>::operator *= (const std::vector<T>& vecCoef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->multByVector(vecCoef);
	}
	return *this;
}

template <class T> bool
Matrix<T>::operator == (const Matrix& mtrx) const
{
	if (getRows() != mtrx.getRows() || getCols() != mtrx.getCols()) {
		return false;
	}
	auto it2 = mtrx.vec.cbegin();
	for (auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
		if (!(*it1 == *it2)) {
			return false;
		}
	}
	return true;
}







