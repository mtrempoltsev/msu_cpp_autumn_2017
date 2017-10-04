#include <iostream>
#include "parser.h"

int
main(int argc, char * argv[])
{
	if (argc != 2) {
		std::cout << "Try ./calc expr" << std::endl;
		return 0;
	}
	
	try {
		std::cout << calc(argv[1]) << std::endl;
	}
	catch(const char *msg) {
		std::cout << msg << std::endl;
		return 1;
	}
	
	return 0;
}
