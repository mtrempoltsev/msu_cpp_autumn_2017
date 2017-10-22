#include "row.hpp"
#include <vector>
#include <cassert>

class Matrix
{
	std::vector<Row> vec;
public:
	Matrix(std::size_t, std::size_t);
	Row& operator[] (std::size_t);
	Matrix& operator*= (double);
	Matrix& operator*= (const std::vector<double>&);
	std::size_t getRows() const {return vec.size();}
	std::size_t getCols() const {return vec[0].getLength();}
	bool operator == (const Matrix&) const;
	bool operator != (const Matrix& m) const {return !(this->operator==(m));}
};

Matrix::Matrix(std::size_t rows, std::size_t cols)
{
	if (rows == 0 || cols == 0) {
		assert(!"zero rows or columns");
	}
	vec.resize(rows, Row(cols));
}

Row&
Matrix::operator[] (std::size_t index)
{
	if (index >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[index];
}

Matrix&
Matrix::operator *= (double coef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->multByNumber(coef);
	}
	return *this;
}

Matrix&
Matrix::operator *= (const std::vector<double>& vecCoef)
{
	for (auto it = vec.begin(); it != vec.end(); ++it) {
		it->multByVector(vecCoef);
	}
	return *this;
}

bool
Matrix::operator == (const Matrix& mtrx) const
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







