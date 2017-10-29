#ifndef MATRIX_ROW_CPP
#define MATRIX_ROW_CPP

#include "../include/matrix_row.hpp"

// OPERATORS BEGINS
// <-------------------------
double& MatrixRow::operator[](int _ncol) {
	if (_ncol >= ncols) {
		cout << "Error" << endl;

		exit(1);
	}

	return data[_ncol];
}

const double& MatrixRow::operator[](int _ncol) const {
	if (_ncol >= ncols) {
		cout << "Error" << endl;

		exit(1);
	}

	return data[_ncol];
}
// >-------------------------
// OPERATORS ENDS

#endif
