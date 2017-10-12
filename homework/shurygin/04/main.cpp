#include <iostream>
#include "Matrix.h"

void check(bool value)
{
	if (!value)
		std::cout << "error" << std::endl;
}

void checkGetSet()
{
	Matrix m(2, 3);
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
	
}

int main()
{
	checkGetSet();

}
