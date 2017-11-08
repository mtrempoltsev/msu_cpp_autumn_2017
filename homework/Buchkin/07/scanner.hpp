#pragma once

#include <string>
#include <sstream>
#include <unordered_map>
#include <limits>
#include "lex.hpp"

template <class T = int>
T parse(const std::string& str)
{
	std::string maxStr = std::to_string(std::numeric_limits<T>::max());
	if (maxStr.length() < str.length() || (maxStr.length() == str.length() && maxStr < str)) {
		throw "Constant is out of limits";
	}
	std::stringstream ss(str);
	T result;
	ss >> result;
	return result;
}

template <class T = int>
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
		NUMBER
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
	
	Lex<T> gl();
};

template <class T>
Lex<T>
Scanner<T>::gl()
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
				buf.clear();
				CS = NUMBER;
			} else if (isspace(c)) {
				gc();
			} else if (c == '+') {
				gc();
				return Lex<T>(LEX_PLUS);
			} else if (c == '-') {
				gc();
				return Lex<T>(LEX_MINUS);
			} else if (c == '*') {
				gc();
				return Lex<T>(LEX_MUL);
			} else if (c == '/') {
				gc();
				return Lex<T>(LEX_DIV);
			} else if (c == '(') {
				gc();
				return Lex<T>(LEX_LPAREN);
			} else if (c == ')') {
				gc();
				return Lex<T>(LEX_RPAREN);
			} else if (c == '\0') {
				return Lex<T>(LEX_FIN);
			} else {
				return Lex<T>(LEX_ERROR);
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
				return Lex<T>(LEX_NUMBER, it->second);
			}
			break;
		case NUMBER:
			if (isdigit(c) || c == '.') {
				buf.push_back(c);
				gc();
			} else {
				T value = parse<T>(buf);
				return Lex<T>(LEX_NUMBER, value);
			}
			break;
		default:
			return Lex<T>(LEX_ERROR);
			break;
		}
	}
}
