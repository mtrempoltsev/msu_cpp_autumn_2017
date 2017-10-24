#include <iostream>
#include <signal.h>
#include "Matrix.cpp"
#include "Row.cpp"
#include <vector>
#include <cassert>


void check(bool value)
{
	if (!value)
		std::cout << "failed!" << std::endl;
	else std::cout << "succeed!" << std::endl;
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
	Matrix<double> m1(m); 
	check(m1[0][1] == 2);
	Matrix<double> m2(1, 1);
	m2 = m1; 
	check(m2[0][1] == 2);	
	m[1][2] = 100;

	check(m[1][2] == 100);
	int a = m.get_columns();
	int b = m.get_rows();

	check(a == 3);
	check(b == 2);
	m *= 2;
	check(m[1][0] == 8);                      
	std::vector<double> v = { 1, 2, 3 };
	m *= v;									
	check(m[0][0] == 28);
	check(m[1][0] == 628);
	Matrix<double> m3 = std::move(m); 
	check(m3[0][0] == 28);
	Matrix<double> m4(1, 1);
	m4 = std::move(m3); 
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



int main() {
	checkGetSet();
	return 0;
}



