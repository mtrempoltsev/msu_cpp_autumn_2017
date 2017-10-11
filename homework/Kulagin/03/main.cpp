#include <iostream>

#include "src/calc.cpp"

using namespace std;

int main(int argc, char** argv) {
	if(argc < 2) {
		cout << "Usage: ./a.out <expression>" << endl;
		
		exit(1);
	}
	
	try {
		Calculator calc;
		
		cout << calc.eval(argv[1]) << endl;
	} catch(const char* e) {
		cout << e << endl;
		
		exit(1);
	}
	
	return 0;
}
