#ifndef MATRIX_ROW_HPP
#define MATRIX_ROW_HPP

#include <vector>

using namespace std;


template<class T>
class MatrixRow {

public:
	// CONSTRUCTOR BEGINS
	MatrixRow(int _ncols): ncols(_ncols) {
		if (ncols <= 0) {
			cout << "Error: cannot initialize matrix_row with " << ncols << " columns" << endl;

			exit(1);
		}

		data.resize(ncols);
	}

	MatrixRow(const MatrixRow& _row) : ncols(_row.ncols) {
		data = _row.data;
	}

	MatrixRow(MatrixRow&& _row) {
		ncols = move(_row.ncols);

		data = move(_row.data);
	}
	// CONSTRUCTOR ENDS

	T& operator[](const int _ncol);

	const T& operator[](const int _ncol) const;

	// DESTRUCTOR BEGINS
	~MatrixRow() {
		data.clear();
	};
	// DESTRUCTOR ENDS

private:
	vector<T> data;

	int ncols;
};

#endif
