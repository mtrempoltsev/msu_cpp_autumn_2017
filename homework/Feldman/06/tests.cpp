#include <iostream>
#include <string>


#include "Calculator.h"
using namespace std;
void check_expression(const char* test) {
		Calculator<double> double_calc(test);
		Calculator<int> int_calc(test);
		Calculator<long long int> long_calc(test);
		cout << "EXPRESSION: " << test << endl;
		double double_result = 0;
		int int_result = 0;
		long long int long_result = 0;
		try {
			cout << "DOUBLE:  " << " = ";
			double_result = double_calc.expr();
			cout << double_result << endl;
		}
		catch (const char* msg) {
			cout << msg << endl;
		}

		try {
			cout << "INT:  " <<  " = ";
			int_result = int_calc.expr();
			cout << int_result << endl;
		}
		catch (const char* msg) {
			cout << msg << endl;
		}

		try {
			cout << "LONG:  " <<  " = ";
			long_result = long_calc.expr();
			cout << long_result << endl;
		}
		catch (const char* msg) {
			cout << msg << endl;
		}	

}


int main() {
	check_expression("1+1");
	check_expression("1.5+3");
	check_expression("(1+2)/4");
	check_expression("Pi*2");
	check_expression("e/2");
	check_expression("10000000000+1");
	return 0;
}
