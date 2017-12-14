#include "matrix.hpp"
#include <iostream>

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
    
    m[1][2] = 100;
    
    check(m[1][2] == 100);
}

void checkFirst(Matrix<double>& m)
{
	check(m[0][0] == 100);
	check(m[0][1] == 500);
	check(m[0][2] == -1000);
	check(m[1][0] == 200);
	check(m[1][1] == 1000);
	check(m[1][2] == -2000);
	check(m[2][0] == 300);
	check(m[2][1] == 1500);
	check(m[2][2] == -3000);
}

void checkSecond(Matrix<double>& m)
{
	check(m[0][0] == 10);
	check(m[0][1] == 20);
	check(m[0][2] == 30);
	check(m[1][0] == 40);
	check(m[1][1] == 50);
	check(m[1][2] == 60);
	check(m[2][0] == 70);
	check(m[2][1] == 80);
	check(m[2][2] == 90);
}

int
main()
{
	checkGetSet();
	Matrix<double> m1(3, 3), m2(3, 3);
	m1[0][0] = 1; m2[0][0] = 1;
	m1[0][1] = -100; m2[0][1] = -100;
	if (m1 != m2) {
		std::cout << "error2" << std::endl;
	}

	std::vector<double> d = {100, 500, -1000};
	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j)
		m1[i][j] = i + 1;

	checkFirst(m1 *= d);

	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j)
		m2[i][j] = 3*i + j + 1;

	checkSecond(m2 *= 10);

	for (int i = 0; i < 3; ++i)
	for (int j = 0; j < 3; ++j)
		m2[i][j] = 3*i + j + 1;

	{
		Matrix<double> m3(3, 3);

		for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			m3[i][j] = 3*i + j + 1;

		m1 = m3;
	}

	check(m1 == m2);
	return 0;
}
