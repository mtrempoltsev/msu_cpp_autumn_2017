#include <map>
#include <string>
#include<cctype>
#include <iostream>
#include<algorithm>
#include "Property.h"
#include "Parser.h"
using namespace std;

template <class T>
class Calculator
{
public:
	Calculator(char* argv) : expression(argv) {
		constants.insert(pair<string, double>("Pi", 3.14));
		constants.insert(pair<string, double>("e", 2.7));
	};
	Calculator(const char* argv) : expression(argv) {
		constants.insert(pair<string, double>("Pi", 3.14));
		constants.insert(pair<string, double>("e", 2.7));
	};
	~Calculator() {};
	void delete_spaces() {
		expression.erase(std::remove(expression.begin(), expression.end(), ' '), expression.end());
	}
	void bracket_balance() {
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
	void check_expression() {
		for (size_t i = 0; i < expression.size(); ++i) {
			char c = expression[i];
			if (!isdigit(c)) {
				if ((c != '+') && (c != '-') && (c != '*') && (c != '/') && (c != '(') && (c != ')') && (c != '.')) {
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
	bool constant() {
		for (auto iter = constants.begin(); iter != constants.end(); ++iter) {
			if (expression.find(iter->first) == (unsigned int)pos)
				return true;
		}
		return false;
	}
	T expr() {
		T x = factor();
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
	T factor() {
		T div = 0;
		T x = bracket();
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
	T bracket() {
		char c = expression[pos];
		pos++;
		if (c == '(') {
			if (!isdigit(expression[pos]) && expression[pos] != '(' && expression[pos] != '-' && !constant()) {
				throw "INVALID EXPRESSION!";
			}
			T x = expr();
			pos++;
			return x;
		}
		else {
			pos--;
			return number();
		}
	}
	T number() {
		double res = 0;
		string str_res;
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
				Parser<T> parser;
				if (!parser.isCorrect("3.14"))
					throw "INVALID DATA TYPE";
				return constants.find("Pi")->second;
			}
			if (c == 'e') {
				pos++;
				Parser<T> parser;
				if (!parser.isCorrect("2.7"))
					throw "INVALID DATA TYPE";
				return constants.find("e")->second;
			}
			if (!isdigit(c))
				if (c != '+' && c != '-' && c != '*' && c != '/' && c != ')'  && c != '(' && c != 0 && c != '.') {
					throw "INVALID EXPRESSION!";
				}
			pos++;
			if ((c >= '0' && c <= '9') || (c == '.')) {
				str_res.push_back(c);
			}
			else {
				pos--;
				if (expression[pos] != ')' && c != '+' && c != '-' && c != '*' && c != '/' && c != 0 && c != '.') {
					throw "INVALID EXPRESSION";
				}
				res = stod(str_res);
				Parser<T> parser;
				if (!parser.isCorrect(str_res))
					throw "INVALID DATA TYPE";
				NumericTraits<T> num;
				if (res < num.min || res > num.max)
					throw "INVALID NUMBER SIZE";

				if (unary_minus == '-')
					return -res;
				return res;
			}
		}
	}
private:
	int pos = 0;
	map <string, double> constants;
	string expression;

};

