#include <iostream>
#include <signal.h>
#include "Matrix.cpp"
#include <vector>
#include <cassert>

extern "C" void sig(int s) {
	throw "OUT OF RANGE!\n";
}

void check(bool value, const char* test)
{
	if (!value)
		std::cout << "test " << test << " failed!" << std::endl;
	else std::cout << "test " << test << " succeed!" << std::endl;
}

void checkGetSet()
{
	Matrix m(2, 2);
	Matrix m1(2, 2);
	std::vector<double> v = { 9,10 };
	check(m.get_rows() == 2, "m.get_rows == 2");
	check(m.get_columns() == 2, "m.get_columns == 2");
	m[0][0] = 1;
	m[0][1] = 2;
	m[1][0] = 3;
	m[1][1] = 4;
	m1[0][0] = 2;
	m1[0][1] = 4;
	m1[1][0] = 6;
	m1[1][1] = 8;
	check(m[0][0] == 1, "m[0][0]==1");
	check(m[0][1] == 2, "m[0][0]==2");
	check(m[1][0] == 3, "m[0][0]==3");
	check(m[1][1] == 4, "m[0][0]==4");
	check(m != m1, "m != m1");
	m *= 2;
	check(m[0][0] == 2, "m[0][0]==2");
	check(m[0][1] == 4, "m[0][0]==4");
	check(m[1][0] == 6, "m[0][0]==6");
	check(m[1][1] == 8, "m[0][0]==8");
	check(m == m1, "m == m1");
	m *= v;
	check(m.get_rows() == 2, "m.get_rows == 2");
	check(m.get_columns() == 1, "m.get_columns == 1");
	check(m[0][0] == 58, "m[0][0]==58");
	check(m[1][0] == 134, "m[1][0]==134");
	
	try {
		//Matrix(0, 0);	
		Matrix m2(2, 2);
		Matrix m3(3, 3);
		std::vector<double> v1{ 1, 2, 3, 4 };
		//m2[0][2];
		//m2[2][0];	
		//m2 == m3;	
		//m2 != m3;
		//m3 *= v1;
		//Тут должен вызваться assert
	}
	catch (const char* msg) {
		std::cout << msg;
	}
}

int main() {
	signal(SIGABRT, &sig);
	checkGetSet();	
	return 0;
}



