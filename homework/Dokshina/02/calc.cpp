#include <iostream>
#include <ctype.h>

using namespace std;
typedef string::iterator string_it;

void skip_spaces(string_it& curr) {
	while (isspace(*curr)) {
		curr++;
	}
}

int get_number(string_it& curr, string_it end) {
	skip_spaces(curr);

	int number = 0;
	int sign = 1;

	//get sign
	if (*curr == '-') {
		sign = -1;
		curr++;
	}

	//get number
	for ( ; curr < end && isdigit(*curr); curr++) {
		number *= 10;
		number += *curr - '0';
	}

	return number * sign;
}

int get_term(int left, string_it& curr, string_it end) {
	skip_spaces(curr);
	char op = *curr;

	if (op != '*' && op != '/') {
		return left;
	}

	//get next number
	int next = get_number(++curr, end);

	//get current term
	if (op == '*') {
		return get_term(left * next, curr, end);
	} else {
		if (!next) {
			throw "Error! Division by zero.";
		}
		return get_term(left / next, curr, end);
	}
	
}

int get_expr(int left, string_it& curr, string_it end) {
	skip_spaces(curr);
	char op = *curr;

	if (op != '+' && op!= '-') {
		return left;
	}

	//get next term
	int numb = get_number(++curr, end);
	int next = get_term(numb, curr, end);

	//get current expr
	if (op == '+') {	
		return get_expr(left + next, curr, end);
	} else {
		return get_expr(left - next, curr, end);
	}

}

int calculate(string input) {
	string_it curr = input.begin();

	//get first term
	int numb = get_number(curr, input.end());
	int term = get_term(numb, curr, input.end());

	return get_expr(term, curr, input.end());
}

int main(int argc, char const *argv[])
{
	if (argc != 2) {
		cout << "Please enter expression!" << endl; 
		cout << "Example: " << argv[0] << ' ';
		cout << "\"2 + 3 * 4 - -2\"" << endl;
	} else {	
		try {
			cout << calculate(string(argv[1])) << endl;
		} catch (const char* err) {
			cout << err << endl;
		}
	}
	
	return 0;
}