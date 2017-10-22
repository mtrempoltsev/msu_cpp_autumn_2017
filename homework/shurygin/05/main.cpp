#include <iostream>
#include "Matrix.h"

void check(bool value)
{
	if (!value)
		std::cout << "error" << std::endl;
}

void checkGetSet()
{	
	Matrix<double> m(2, 3);	
	m[0][0] = 1;
	m[0][1] = 2;
	m[0][2] = 3;
	m[1][0] = 4;
	m[1][1] = 5;
	m[1][2] = 6;
	
	check(m[0][0] == 1);
	check(m[0][1] == 2);
	check(m[0][2] == 3);
	check(m[1][0] == 4);
	check(m[1][1] == 5);
	check(m[1][2] == 6);
	Matrix<double> m1(m); // copy
	check(m1[0][1] == 2);
	Matrix<double> m2(1, 1);
	m2 = m1; // operator=
	check(m2[0][1] == 2);	
	m[1][2] = 100;

	check(m[1][2] == 100);
	int a = m.GetCols();
	int b = m.GetRows();

	check(a == 3);
	check(b == 2);
	m *= 2;
	check(m[1][0] == 8);                      /*1 2 3
											    4 5 6*/
	std::vector<double> v = { 1, 2, 3 };
	m *= v;									/* 11
												32*/
	check(m[0][0] == 28);
	check(m[1][0] == 628);
	Matrix<double> m3 = std::move(m); // move
	check(m3[0][0] == 28);
	Matrix<double> m4(1, 1);
	m4 = std::move(m3); //move operator=
	check(m4[0][0] == 28);

	Matrix<int> m5(2, 2);
	m5[0][0] = 1;
	m5[0][1] = 0;
	m5[1][1] = 1;
	m5[1][0] = 0;
	std::vector<int> v2 = { 1, 1 };
	m5 *= v2;
	check(m5[0][0] == 1);
}

int main()
{
	checkGetSet();

}
