#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "../include/matrix.hpp"

// GETTERS BEGINS
int Matrix::get_nrows() const {
	return nrows;
}

int Matrix::get_ncols() const {
	return ncols;
}
// GETTERS ENDS

// OPERATORS BEGINS
// <-------------------------
MatrixRow& Matrix::operator[](const int _nrow) {
	if (_nrow >= nrows) {
		cout << "Err" << endl;

		exit(1);
	};

	return data[_nrow];
}

Matrix Matrix::operator*=(double a) {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] *= a;
		}
	}
	return *this;
}

Matrix Matrix::operator*=(std::vector<double> v) {
	// assert(v.size() == ncols);
	Matrix m(nrows, 1);
	for (std::size_t i = 0; i < nrows; ++i)
	{
		double s = 0.0;
		for (std::size_t j = 0; j < ncols; ++j)
		{
			s += data[i][j] * v[j];
		}
		m[i][0] = s;
	}
	data.clear();
	*this = m;
	return *this;
}

bool Matrix::operator==(Matrix m) const {
	if (nrows != m.get_nrows() || ncols != m.get_ncols())
		return false;
	for (std::size_t i = 0; i < nrows; ++i)
		for (std::size_t j = 0; j < ncols; ++j)
			if (data[i][j] != m[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(Matrix m) const {
	return !((*this) == m);
}
// >-------------------------
// OPERATORS ENDS

#endif
