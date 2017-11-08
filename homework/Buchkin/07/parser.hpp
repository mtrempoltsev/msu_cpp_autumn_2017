#pragma once

#include "scanner.hpp"
#include <vector>

template <class T = int>
class Parser
{
	Lex<T> lex;
	void gl() {lex = sc.gl();}
	Scanner<T> sc;
	
	T expr();
	T term();
	T prim();
	T number();
	
public:
	Parser(const char *str): sc(str) {}

	T calc()
	{
		gl();
		T value = expr();
		if (lex.type != LEX_FIN) {
			throw "Incorrect ending";
		}
		
		return value;
	}
};

template <class T> T
Parser<T>::expr()
{
	T value = term();
	while (lex.type == LEX_PLUS || lex.type == LEX_MINUS) {
		Lex<T> l = lex;
		gl();
		if (l.type == LEX_PLUS) {
			value += term();
		} else {
			value -= term();
		}
	}
	return value;
}

template <class T> T
Parser<T>::term()
{
	T value = prim();
	while (lex.type == LEX_MUL || lex.type == LEX_DIV) {
		Lex<T> l = lex;
		gl();
		if (l.type == LEX_MUL) {
			value *= prim();
		} else {
			T divider = prim();
			if (divider == T()) {
				throw "Zero division";
			}
			value /= divider;
		}
	}
	return value;
}

template <class T> T
Parser<T>::prim()
{
	if (lex.type == LEX_MINUS) {
		gl();
		return -number();
	} else {
		return number();
	}
	
	return T();
}

template <class T> T
Parser<T>::number()
{	
	if (lex.type == LEX_NUMBER) {
		T value = lex.value;
		gl();
		return value;
	} else if (lex.type == LEX_LPAREN) {
		gl();
		T value = expr();
		if (lex.type != LEX_RPAREN) {
			throw "no right parenthesis";
		}
		gl();
		return value;
	} else {
		throw "wrong lexeme";
	}
	
	return T();
}
