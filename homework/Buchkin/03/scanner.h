#pragma once

#include <string>
#include <unordered_map>
#include "lex.h"

class Scanner
{
	char c;
	int i;
	const char *str;
	void gc() {c = str[i++];}
	
	enum state
	{
		H,
		CONSTANT,
		INTEGER
	};
	
	std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
	
public:
	Scanner(const char *str_): str(str_), i(0)
	{
		if (str == nullptr) {
			throw "Empty input";
		}
		gc();
	}
	
	Lex gl();
};

Lex
Scanner::gl()
{
	state CS = H;
	std::string buf;
	lexType type;
	double value = 0.0;
	
	while (true) {		
		switch (CS) {
		case H:
			if (isalpha(c)) {
				buf.clear();
				CS = CONSTANT;
			} else if (isdigit(c)) {
				value = 0.0;
				CS = INTEGER;
			} else if (isspace(c)) {
				gc();
			} else if (c == '+') {
				gc();
				return Lex(LEX_PLUS);
			} else if (c == '-') {
				gc();
				return Lex(LEX_MINUS);
			} else if (c == '*') {
				gc();
				return Lex(LEX_MUL);
			} else if (c == '/') {
				gc();
				return Lex(LEX_DIV);
			} else if (c == '(') {
				gc();
				return Lex(LEX_LPAREN);
			} else if (c == ')') {
				gc();
				return Lex(LEX_RPAREN);
			} else if (c == '\0') {
				return Lex(LEX_FIN);
			} else {
				return Lex(LEX_ERROR);
			}
			break;
		case CONSTANT:
			if (isalpha(c)) {
				buf.push_back(c);
				gc();
			} else {
				auto it = constants.find(buf);
				if (it == constants.end()) {
					throw "Unknown constant";
				}
				return Lex(LEX_NUMBER, it->second);
			}
			break;
		case INTEGER:
			if (isdigit(c)) {
				value = value * 10.0 + (double)(c - '0');
				gc();
			} else {
				return Lex(LEX_NUMBER, value);
			}
			break;
		default:
			return Lex(LEX_ERROR);
			break;
		}
	}
}
