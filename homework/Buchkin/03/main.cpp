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
		Parser p(argv[1]);
		std::cout << p.calc() << std::endl;
	}
	catch(const char *msg) {
		std::cout << msg << std::endl;
		//code 1
		return 1;
	}
	
	return 0;
}
