#include <iostream>
#include <string>
#include "calculator.hpp"

int main(int argc, char *argv[]) {
	std::string s(argv[1]);
	std::cout << calcExpr(s) << std::endl;
	return 0;
}
