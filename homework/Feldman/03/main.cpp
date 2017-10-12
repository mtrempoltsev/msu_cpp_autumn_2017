#include <iostream>
#include <string>
#include<cctype>
#include<algorithm>
#include <map>
using namespace std;
class Calculator
{
public:
	Calculator(char* argv);
	~Calculator();
	void delete_spaces();
	void bracket_balance();
	void check_expression();
	bool constant();
	double expr();
	double factor();
	double bracket();
	double number();
private:
	int pos = 0;
	map <string, double> constants;
	string expression;	
	
};

Calculator::Calculator(char* argv) : expression(argv) {
	constants.insert(pair<string,double>("Pi", 3.14));
	constants.insert(pair<string, double>("e", 2.7));
}

Calculator::~Calculator(){}


bool Calculator::constant() {
	for (auto iter = constants.begin(); iter != constants.end(); ++iter) {
		if (expression.find(iter->first) == (unsigned int)pos)
			return true;
	}
	return false;
}

void Calculator::check_expression() {
	for (size_t i = 0; i < expression.size(); ++i) {
		char c = expression[i];
		if (!isdigit(c)) {
			if ((c != '+') && (c != '-') && (c != '*') && (c != '/') && (c != '(') && (c != ')')) {
				if (expression.find("Pi") == i) {
					i += 2;
				}
				else if (expression.find("e") == i) {
					i += 1;
				}				
				else				
					throw "INVALID EXPRESSION!";
			}
		}				
	}
}


void Calculator::delete_spaces() {
	expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
}

void Calculator::bracket_balance() {
	if (expression[0] == '-') {
		expression.insert(expression.begin(), '0');
	}
	int balance = 0;
	for (size_t i = 0; i < expression.size(); ++i) {
		if (expression[i] == ')')
			balance++;
		else if (expression[i] == '(')
			balance--;
	}
	if (balance != 0)
		throw "INVALID EXPRESSION!";
}



double Calculator::expr() {
	double x = factor();
	for (;;) {
		char c = expression[pos];
		pos++;		
		switch (c) {
		case '+':
			if (!isdigit(expression[pos]) && expression[pos] != '(' && expression[pos] != '-' && !constant())
				throw "INVALID EXPRESSION!";
			x += factor();
			break;
		case '-':
			if (!isdigit(expression[pos]) && expression[pos] != '(' && expression[pos] != '-' && !constant())
				throw "INVALID EXPRESSION!";
			x -= factor();
			break;
		default:
			pos--;
			return x;
		}
	}
}

double Calculator::factor() {
	double div = 0;
	double x = bracket();
	for (;;) {
		char c = expression[pos];
		pos++;		
		switch (c) {
		case '*':
			if (!isdigit(expression[pos]) && expression[pos] != '(' && expression[pos] != '-' && !constant())
				throw "INVALID EXPRESSION!";
			x *= bracket();
			break;
		case '/':
			if (!isdigit(expression[pos]) && expression[pos] != '(' && expression[pos] != '-' && !constant())
				throw "INVALID EXPRESSION!";
			div = bracket();
			if (div == 0)
				throw "DIVISION BY ZERO!";
			
			x /= div;
			break;
		default:
			pos--;
			return x;
		}
	}
}

double Calculator::bracket() {
	char c = expression[pos];
	pos++;
	if (c == '(') {
		if (!isdigit(expression[pos]) && expression[pos] != '(' && expression[pos] != '-' && !constant()) {
			throw "INVALID EXPRESSION!";
		}
		double x = expr();
		pos++;
		return x;
	}
	else {
		pos--;
		return number();
	}
}

double Calculator::number() {
	double res = 0;
	char unary_minus = expression[pos];
	if (unary_minus == '-') {
		pos++;
		if (expression[pos] == '(') {
			pos++;
			res = expr();
		}
	}	
	for (;;) {		
		char c = expression[pos];
		if (c == 'P') {
			pos += 2;
			return constants.find("Pi")->second;
		}
		if (c == 'e') {
			pos++;
			return constants.find("e")->second;
		}
		if (!isdigit(c))
			if (c != '+' && c != '-' && c != '*' && c != '/' && c != ')'  && c != '(' && c != 0) {
				throw "INVALID EXPRESSION!";
			}
		pos++;		
		if (c >= '0' && c <= '9') {
			res = res * 10 + c - '0';
			
		}
		else {
			pos--;
			if (expression[pos] != ')' && c != '+' && c != '-' && c != '*' && c != '/' && c != 0) {
				
					
					
				throw "INVALID EXPRESSION";
				
			}
			if (unary_minus == '-')
				return -res;
			return res;
		}
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "INVALID ARGUMENTS!" << endl;
		return 1;
	}
	Calculator calc(argv[1]);
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
