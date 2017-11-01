#include <iostream>
#include <cmath>
#include <cstring>

#include "src/calc.cpp"

using namespace std;

const double precision = 1e-15;


template<typename T>
void is(std::string text, T value, bool positive = true) {
	const char* text_ptr = text.c_str();

	Calculator<T> calc;

	try {
		auto result = calc.eval((char*)text_ptr);

		if (abs(result - value) < precision) {
			if (positive) {
				cout << "'" << text << "'" << " == " << value << " - ";
				cout << "ok" << endl;
			} else {
				cout << "'" << text << "'" << " != " << value << " - ";
				cout << "not ok" << " " << "(got: " << result << ")" << endl;
			}
		} else {
			if (positive) {
				cout << "'" << text << "'" << " == " << value << " - ";
				cout << "not ok" << " " << "(got: " << result << ")" << endl;
			} else {
				cout << "'" << text << "'" << " != " << value << " - ";
				cout << "ok" << endl;
			}
		}
	} catch (std::runtime_error& e) {
		if (positive) {
			cout << "'" << text << "'" << " == " << value << " - ";
			cout << "not ok " << endl;
		} else {
			cout << "'" << text << "'" << " != " << value << " - ";
			cout << "ok " << endl;
		}
		cout << "Parse error: " << e.what() << endl;
	}
}

template <typename T>
void check_calc() {
	const double Pi = 3.14;
	const double e = 2.7;

	// POSITIVE TESTS
	cout << "POSITIVE TESTS:" << endl;
	is<T>("1", 1);
	is<T>(" 1", 1);
	is<T>("+1", 1);
	is<T>("-1", -1);
	is<T>("1+2", 3);
	is<T>("1 + 2", 3);
	is<T>(" +1 + +2", 3);
	is<T>(" -1 + -2", -3);
	is<T>(" -1 - 2", -3);
	is<T>(" -1 - -2", 1);
	is<T>("2 - 6 * 2 / 2", -4);
	is<T>("2 - 6 / 2 * 2", -4);
	is<T>("3 + 4 * 2 - -1", 12);
	is<T>("2*-2", -4);
	is<T>(" +2 * -2", -4);
	is<T>(" -2 * +2", -4);

	is<T>("Pi", (T)Pi);
	is<T>("e", (T)e);
	is<T>("Pi + e", (T)Pi + (T)e);
	is<T>("Pi + 3", (T)Pi + 3);
	is<T>("-Pi + 4", -(T)Pi + 4);
	is<T>(" +5 + Pi", 5 + (T)Pi);
	is<T>(" +6 + -Pi", 6 - (T)Pi);
	is<T>(" -7 - +Pi", -7 - (T)Pi);
	// is<T>("()", 0); error
	is<T>("(1)", 1);
	is<T>("(-1)", -1);
	is<T>("-(1)", -1);
	is<T>("-(-1)", 1);

	is<T>("(Pi)", (T)Pi);
	is<T>("(-Pi)", -(T)Pi);
	is<T>("-(Pi)", -(T)Pi);
	is<T>("-(-Pi)", (T)Pi);

	is<T>("(e)", (T)e);
	is<T>("(-e)", -(T)e);
	is<T>("-(e)", -(T)e);
	is<T>("-(-e)", (T)e);

	is<T>(" ( e+3 ) + 5", (T)e + 3 + 5);
	is<T>(" ( e*3 ) + 5", (T)e * 3 + 5);
	is<T>("e + (3) + 4", (T)e + 3 + 4);
	is<T>("e + (3 + 4) ", (T)e + (3 + 4));
	is<T>("e / (5) ", (T)((T)e / 5));
	is<T>("e / (6 + 7) ", (T)((T)e / (6 + 7)));
	is<T>("(8 - e) / (9 + 10) ", (T)((8 - (T)e) / (9 + 10)));

	is<T>("2.5", (T)2.5);
	is<T>("(2.5)", (T)2.5);
	is<T>("(-2.5)", -(T)2.5);
	is<T>("-(2.5)", -(T)2.5);

	is<T>("2.5 + 2.5", (T)5);
	is<T>("2.5 + -2.5", 0);
	is<T>(" -2.5 + 2.5", 0);
	is<T>(" -2.5 + -2.5", (T) - 5);
	is<T>(" -2.5 - -2.5", 0);

	is<T>(" -2.5 *  3.25", (T)((T) - 2.5 * (T)3.25));

	is<T>("2.445332664432 - 1223.434545634", (T)((T)2.445332664432 - (T)1223.434545634));

	is<T>("5 + 0.", 5);
	is<T>("5 + 0.", 5);

	is<T>("5 + +0.", 5);
	is<T>("5 + +.0", 5);

	is<T>("5 - +0.", 5);
	is<T>("5 - +.0", 5);


	is<T>("5 - +1.", 4);
	is<T>("5 - +.6", (T)4.4);
	is<T>("22323232137128931", (T)22323232137128931);
	cout << endl;

	// NEGATIVE TESTS
	cout << "NEGATIVE TESTS:" << endl;
	is<T>("1 + +1", 0, false);
	is<T>("2 2", 0, false);

	is<T>("((3+3", 0, false);
	is<T>("3+3))", 0, false);
	is<T>("(3)+3)", 0, false);

	is<T>("(3)+4/(5-0)", 0, false);
	is<T>(".5 + 2", 0, false);
	is<T>("(1 + 2", 0, false);
	is<T>(")1 + 2", 0, false);

	is<T>("4*+ 5", 0, false);
	is<T>("5 + .", 5, false);
	is<T>("2..+* 2", 0, false);
}


int main(int argc, char** argv) {
	if (argc < 3) {
		cout << "Testing for 'int' type:" << endl << endl;
		check_calc<int>();
		cout << endl;

		cout << "Testing for 'long' type:" << endl << endl;
		check_calc<long>();
		cout << endl;

		cout << "Testing for 'double' type:" << endl;
		check_calc<double>();
		cout << endl;
	} else {
		const char* type = argv[2];

		if (strcmp(type, "int") == 0 || strcmp(type, "Int") == 0) {
			Calculator<int> calc;

			cout << calc.eval((char*) argv[1]) << endl;
		} else if (strcmp(type, "long") == 0 || strcmp(type, "Long") == 0) {
			Calculator<int> calc;

			cout << calc.eval((char*) argv[1]) << endl;

		} else if (strcmp(type, "double") == 0 || strcmp(type, "Double") == 0) {
			Calculator<double> calc;

			cout << calc.eval((char*) argv[1]) << endl;
		} else {
			cout << "Usage: ./a.out <expression> <type>" << endl << endl;
			cout << "<type>: int, long, double" << endl << endl;
			cout << "Example: ./a.out '1+2' int" << endl;
		}
	}

	return 0;
}
