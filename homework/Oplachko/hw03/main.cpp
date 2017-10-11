#include <iostream>
#include <string>
#include "calculator.hpp"

int main(int argc, char *argv[]) {
	std::string s(argv[1]);
	Calculator calc(s);
	std::cout << calc.calcExpr() << std::endl;
	return 0;
}
