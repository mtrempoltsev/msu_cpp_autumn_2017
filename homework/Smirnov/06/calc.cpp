/**
 Калькулятор.
 БНФ (скобки)
 expr = term | expr + term | expr - term 
 term = prim | term * prim | term / prim 
 prim = - number | number | name 
 number = [0,9]+
 name = [a-z.A-Z]+
 */
#include "calc.hpp"
#include <cmath>

const double eps = 1e-3;

bool is_equal(double a, double b)
{
	if (abs(a-b) < eps) return true;
	return false;
}

int main(int argc,char** argv)
{
	Calculator<double> calc_d;
	Calculator<int> calc_i;
	Calculator<long> calc_l;
	double test_d;
	long test_l;
	int test_i;

	//Test1
	const char* test1 = "2+(2.1*4.2)";
	test_d = calc_d.calculate(test1);
	std::cout << test1 << " = " << test_d << " - ";
	if (is_equal(test_d, 10.82))
	{
		std::cout << "OK" << std::endl;
	} 
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	//Test2
	const char* test2 = "300+(16*4)";
	test_i = calc_i.calculate(test2);
	std::cout << test2 << " = " << test_i << " - ";
	if (test_i == 364)
	{
		std::cout << "OK" << std::endl;
	} 
	else
	{
		std::cout << "ERROR" << std::endl;
	}

	//Test3
	const char* test3 = "13000000+1500000*5";
	test_l = calc_l.calculate(test3);
	std::cout << test3 << " = " << test_l << " - ";
	if (test_l == 20500000)
	{
		std::cout << "OK" << std::endl;
	} 
	else
	{
		std::cout << "ERROR" << std::endl;
	}
	return 0; 
}