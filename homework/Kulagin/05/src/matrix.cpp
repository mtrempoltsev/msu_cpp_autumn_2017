#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "../include/matrix.hpp"

// GETTERS BEGINS
template <class T>
int Matrix<T>::get_nrows() const {
	return nrows;
}

template <class T>
int Matrix<T>::get_ncols() const {
	return ncols;
}
// GETTERS ENDS

// OPERATORS BEGINS
template <class T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& _matrix) {
	if (this == &_matrix) {
		return (*this);
	}

	nrows = _matrix.nrows;
	ncols = _matrix.ncols;

	data.clear();

	for (int i = 0; i < nrows; i++) {
		data.push_back(_matrix.data[i]);
	}

	return (*this);
}

template <class T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& _matrix) {
	if (this == &_matrix) {
		return (*this);
	}

	nrows = move(_matrix.nrows);
	ncols = move(_matrix.ncols);

	data.clear();

	for (int i = 0; i < nrows; ++i) {
		data.push_back(move(_matrix.data[i]));
	}

	return (*this);
}

template <class T>
bool Matrix<T>::operator==(Matrix<T>& _matrix) const {
	if (nrows != _matrix.nrows || ncols != _matrix.ncols) {
		return false;
	}

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			if (data[i][j] != _matrix.data[i][j]) {
				return false;
			}
		}
	}

	return true;
}

template <class T>
bool Matrix<T>::operator!=(Matrix<T>& _matrix) const {
	return !(*this == _matrix);
}

template <class T>
MatrixRow<T>& Matrix<T>::operator[](const int _nrow) {
	if (_nrow < 0 || _nrow >= nrows) {
		cout << "Error: row index " << _nrow << " is out of range" << endl;

		exit(1);
	}

	return data[_nrow];
}

template <class T>
Matrix<T>& Matrix<T>::operator+=(const T k) {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] += k;
		}
	}

	return (*this);
}

template <class T>
Matrix<T>& Matrix<T>::operator-=(const T k) {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] -= k;
		}
	}

	return (*this);
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const T k) {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] *= k;
		}
	}

	return (*this);
}

template <class T>
Matrix<T>& Matrix<T>::operator*=(const vector<T> v) {
	if (ncols != (int)v.size()) {
		cout << "Error: cannot multiply matrix by vector (size mismatch)" << endl;

		exit(1);
	}

	Matrix<T> _matrix(nrows, 1);

	for (int i = 0; i < nrows; i++) {
		double elem = 0;

		for (int j = 0; j < ncols; j++) {
			elem += data[i][j] * v[j];
		}

		_matrix[i][0] = elem;
	}

	data.clear();

	return (*this = _matrix);
}

template <class T>
Matrix<T>& Matrix<T>::operator/=(const T k) {
	if (k == 0) {
		cout << "Error: division by zero" << endl;

		exit(1);
	}

	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			data[i][j] /= k;
		}
	}

	return (*this);
}
// OPERATORS ENDS

template <class T>
void Matrix<T>::print() const {
	for (int i = 0; i < nrows; i++) {
		for (int j = 0; j < ncols; j++) {
			cout << data[i][j] << "\t";
		}

		cout << endl;
	}
}

#endif
