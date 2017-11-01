#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "../src/matrix_row.cpp"


template <class T>
class Matrix {

public:
	// CONSTRUCTOR BEGINS
	Matrix(int _nrows, int _ncols) : nrows(_nrows), ncols(_ncols) {
		if (nrows <= 0) {
			cout << "Error: cannot initialize matrix with " << nrows << " rows" << endl;

			exit(1);
		}

		if (ncols <= 0) {
			cout << "Error: cannot initialize matrix with " << ncols << " columns" << endl;

			exit(1);
		}

		for (int i = 0; i < nrows; i++) {
			data.push_back(MatrixRow<T>(ncols));
		}
	}

	Matrix(const Matrix& _matrix) : nrows(_matrix.nrows), ncols(_matrix.ncols) {
		for (int i = 0; i < nrows; i++) {
			data.push_back(_matrix.data[i]);
		}
	}

	Matrix(Matrix&& _matrix) {
		nrows = move(_matrix.nrows);
		ncols = move(_matrix.ncols);

		for (int i = 0; i < nrows; i++) {
			data.push_back(_matrix.data[i]);
		}
	}
	// CONSTRUCTOR ENDS

	// GETTERS BEGINS
	int get_nrows() const;
	int get_ncols() const;
	// GETTERS ENDS

	// OPERATORS BEGINS
	Matrix& operator=(const Matrix& _matrix);
	Matrix& operator=(Matrix&& _matrix);

	bool operator==(Matrix&) const;
	bool operator!=(Matrix&) const;

	MatrixRow<T>& operator[](const int _nrow);

	Matrix& operator+=(const T k);
	Matrix& operator-=(const T k);

	Matrix& operator*=(const T k);
	Matrix& operator*=(const vector<T> v);

	Matrix& operator/=(const T k);
	// OPERATORS ENDS

	void print() const;

	// DESTRUCTOR BEGINS
	~Matrix() {
		data.clear();
	};
	// DESTRUCTOR ENDS

private:
	int nrows;
	int ncols;

	vector<MatrixRow<T> > data;
};

#endif
