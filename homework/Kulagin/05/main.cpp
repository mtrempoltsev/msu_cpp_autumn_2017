#include <iostream>

#include "src/matrix.cpp"

using namespace std;


void check(bool value) {
	if (!value) {
		cout << "error" << endl;

		exit(1);
	}
}

void checkGetSet() {
	Matrix<double> A(3, 4);
	A[0][0] = 1; A[0][1] =  2; A[0][2] =  3; A[0][3] =  4;
	A[1][0] = 5; A[1][1] =  6; A[1][2] =  7; A[1][3] =  8;
	A[2][0] = 9; A[2][1] = 10; A[2][2] = 11; A[2][3] = 12;

	Matrix<double> B(3, 4);
	B[0][0] = 1; B[0][1] =  2; B[0][2] =  3; B[0][3] =  4;
	B[1][0] = 5; B[1][1] =  6; B[1][2] =  7; B[1][3] =  8;
	B[2][0] = 9; B[2][1] = 10; B[2][2] = 11; B[2][3] = 12;

	// --------------------------------------------------------------------------------------------
	// 'equality' test
	check(A == B);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// 'get_nrows()' test
	check(A.get_nrows() == 3);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// 'get_ncols()' test
	check(A.get_ncols() == 4);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// 'fill matrix' test
	check(A[0][0] == 1 && A[0][1] ==  2 && A[0][2] ==  3 && A[0][3] ==  4);
	check(A[1][0] == 5 && A[1][1] ==  6 && A[1][2] ==  7 && A[1][3] ==  8);
	check(A[2][0] == 9 && A[2][1] == 10 && A[2][2] == 11 && A[2][3] == 12);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	A[1][2] = -3;
	// 'change matrix' test
	check(A[1][2] == -3);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	B[2][1] *= 2;
	// 'operator *= (T)' test
	check(B[2][1] == 20);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	Matrix<double> A_copy(A);

	// 'copy constructor' test
	check(A_copy[0][0] == 1 && A_copy[0][1] ==  2 && A_copy[0][2] ==  3 && A_copy[0][3] ==  4);
	check(A_copy[1][0] == 5 && A_copy[1][1] ==  6 && A_copy[1][2] == -3 && A_copy[1][3] ==  8);
	check(A_copy[2][0] == 9 && A_copy[2][1] == 10 && A_copy[2][2] == 11 && A_copy[2][3] == 12);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	Matrix<double> C(3, 4);
	C = A;

	// 'operator =' test
	check(C[0][0] == 1 && C[0][1] ==  2 && C[0][2] ==  3 && C[0][3] ==  4);
	check(C[1][0] == 5 && C[1][1] ==  6 && C[1][2] == -3 && C[1][3] ==  8);
	check(C[2][0] == 9 && C[2][1] == 10 && C[2][2] == 11 && C[2][3] == 12);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// 'operator *= (vector)' test
	vector<double> v = {1, 2, 3, 4};

	A *= v;

	check(A.get_nrows() == 3);
	check(A.get_ncols() == 1);

	check(A[0][0] ==  30);
	check(A[1][0] ==  40);
	check(A[2][0] == 110);
	// --------------------------------------------------------------------------------------------

	// --------------------------------------------------------------------------------------------
	// 'move' test
	Matrix<double> A_moved = std::move(A);

	check(A[0][0] ==  30);
	check(A[1][0] ==  40);
	check(A[2][0] == 110);
	// --------------------------------------------------------------------------------------------
}

int main() {
	checkGetSet();

	return 0;
}
