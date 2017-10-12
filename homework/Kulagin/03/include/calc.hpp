#ifndef CALC_HPP
#define CALC_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>

using namespace std;

class Calculator {

public:
	Calculator() {
		init_constants();
	}
	
	~Calculator() {}
	
	int eval(char* expr);	// calculate the value of input expression
	
	static std::unordered_map<std::string, double> constants;
	
private:

	void init_constants() {
		constants["Pi"] = 3.14;
		constants["e"] = 2.7;
	}
	
	bool is_letter(char c) {
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}
	
	bool is_digit(char c) {
		return (c >= '0' && c <= '9');
	}
	
	void skip_spaces(char*& expr) {
		while(*expr == ' ') {
			expr++;
		}
	}
	
	// [GET_PRIM]: parsing [+-]?(?:Pi|e|\d+) - perl style
	int get_prim(char*& expr);
	
	// [GET_TERM]: parsing 'prim | term * prim | term / prim'
	int get_term(char*& expr);
	
	// [GET_EXPR]: parsing 'expr = term | expr + term | expr - term'
	int get_expr(char*& expr);
	
	// IF '(' THEN opened_brackets_cnt += 1
	// ELSE IF ')' THEN opened_brackets_cnt -= 1
	// ENDIF
	int opened_brackets_cnt;
};

#endif
