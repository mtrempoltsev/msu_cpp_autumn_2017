#include <iostream>
#include <cstring>
#include <limits>
#include "parser.hpp"

int
main(int argc, char * argv[])
{
	if (argc != 2 && argc != 3) {
		std::cout << "Try ./calc expr (-i / -d / -l)" << std::endl;
		return 0;
	}
	
	try {
		if (argc == 2 || !strcmp(argv[2], "-i") || !strcmp(argv[2], "--integer")) {
			Parser<int> p(argv[1]);
			std::cout << p.calc() << std::endl;
		} else if (!strcmp(argv[2], "-d") || !strcmp(argv[2], "--double")) {
			Parser<double> p(argv[1]);
			std::cout << p.calc() << std::endl;
		} else if (!strcmp(argv[2], "-l") || !strcmp(argv[2], "--long-double")) {
			Parser<long double> p(argv[1]);
			std::cout << p.calc() << std::endl;
		} else {
			std::cout << "Unknown command " << argv[2] << ". Try --integer / --double / --long-double" << std::endl;
		}
	}
	catch(const char *msg) {
		std::cout << msg << std::endl;
		return 1;
	}
	
	return 0;
}
