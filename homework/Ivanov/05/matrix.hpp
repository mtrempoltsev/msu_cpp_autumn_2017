#include "proxy.hpp"
#include <vector>
#include <cassert>

template <class T>
class Matrix
{
	std::vector<Proxy<T>> vec;
public:
	Matrix(size_t, size_t);
	Matrix(const Matrix<T>&);
	Matrix(Matrix<T>&&);

	Proxy<T>& operator[] (size_t);
	const Proxy<T>& operator[] (size_t) const;
	Matrix& operator*= (T);
	Matrix& operator*= (const std::vector<T>&);
	size_t rows() const {return vec.size();}
	size_t columns() const {return vec[0].len();}
	bool operator==(const Matrix&) const;
	bool operator!=(const Matrix& m) const {return !(this->operator==(m));}
	Matrix<T>& operator= (const Matrix<T>&);
	Matrix<T>& operator= (Matrix<T>&&);
};

template <class T>
Matrix<T>::Matrix(size_t Proxys, size_t cols)
{
	if (Proxys == 0 || cols == 0) {
		assert(!"zero Proxys or rows");
	}
	vec.resize(Proxys, Proxy<T>(cols));
}

template <class T>
Matrix<T>::Matrix(const Matrix<T>& m)
{
	vec.resize(m.rows());
	auto mIt = m.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++mIt) {
		*it = *mIt;
	}
}

template <class T>
Matrix<T>::Matrix(Matrix<T>&& m)
{
	vec = m.vec;
}

template <class T> Matrix<T>&
Matrix<T>::operator= (const Matrix<T>& m)
{
	vec.clear();
	vec.resize(m.rows());
	auto mIt = m.vec.cbegin();
	for (auto it = vec.begin(); it != vec.end(); ++it, ++mIt) {
		*it = *mIt;
	}
	return *this;
}

template <class T> Matrix<T>&
Matrix<T>::operator= (Matrix<T>&& m)
{
	vec = m.vec;
	return *this;
}

template <class T> Proxy<T>&
Matrix<T>::operator[] (size_t index)
{
	if (index >= vec.size()) {
		assert(!"Error");
	}
	return vec[index];
}

template <class T> const Proxy<T>&
Matrix<T>::operator[] (size_t index) const
{
	if (index >= vec.size()) {
		assert(!"Error");
	}
	return vec[index];
}

template <class T> Matrix<T>&
Matrix<T>::operator *= (T coef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->mulnum(coef);
	}
	return *this;
}

template <class T> Matrix<T>&
Matrix<T>::operator *= (const std::vector<T>& vecCoef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->mulvec(vecCoef);
	}
	return *this;
}

template <class T> bool
Matrix<T>::operator == (const Matrix& m) const
{
	if (rows() != m.rows() || columns() != m.columns()) {
		return false;
	}
	auto it2 = m.vec.cbegin();
	for (auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
		if (!(*it1 == *it2)) {
			return false;
		}
	}
	return true;
}







