#include "RDParser.h"


int main(int argc, char * argv[]){
	RDParser& parser = RDParser::Instance();
	try{
		std::cout << parser.calculateExprFromStr(argv[1]) << std::endl;
	}
	catch(const std::invalid_argument& e){
		std::cout << e.what() << std::endl;
		exit(1);
	}

	return 0;
}