#include <iostream>
#include <string>
#include<cctype>
#include<algorithm>
#include <map>
#include "Calculator.cpp"
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "INVALID ARGUMENTS!" << endl;
		return 1;
	}
	Calculator<double> calc(argv[1]);
	try {
		calc.delete_spaces();
		calc.bracket_balance();
		calc.check_expression();
		cout << calc.expr() << endl;
	}
	catch (const char* msg) {
		cout << msg << endl;
		return 1;
	}
	
	return 0;
}