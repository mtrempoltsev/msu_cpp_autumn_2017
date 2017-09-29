#include "parser.hpp"

int
main(int argc, char * argv[])
{
	if (argc != 2) {
		std::cout << "Try ./calc expr" << std::endl;
	}
	
	Parser p(argv[1]);
	
	try {
		std::cout << p.calc() << std::endl;
	}
	catch(const char *msg) {
		std::cout << msg << std::endl;
	}
	
	return 0;
}
