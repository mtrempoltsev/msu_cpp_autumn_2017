#pragma once

#include "scanner.h"
#include <vector>

class Parser
{
	Lex lex;
	void gl() {lex = sc.gl();}
	Scanner sc;
	
	double expr();
	double term();
	double prim();
	double number();
	
public:
	Parser(const char *str): sc(str) {}

	double calc()
	{
		gl();
		double value = expr();
		if (lex.type != LEX_FIN) {
			throw "Incorrect ending";
		}
		
		return value;
	}
};

double
Parser::expr()
{
	double value = term();
	while (lex.type == LEX_PLUS || lex.type == LEX_MINUS) {
		Lex l = lex;
		gl();
		if (l.type == LEX_PLUS) {
			value += term();
		} else {
			value -= term();
		}
	}
	return value;
}

double
Parser::term()
{
	double value = prim();
	while (lex.type == LEX_MUL || lex.type == LEX_DIV) {
		Lex l = lex;
		gl();
		if (l.type == LEX_MUL) {
			value *= prim();
		} else {
			double divider = prim();
			if (divider == 0.0) {
				throw "Zero division";
			}
			value /= divider;
		}
	}
	return value;
}

double
Parser::prim()
{
	if (lex.type == LEX_MINUS) {
		gl();
		return -number();
	} else {
		return number();
	}
	
	return 0.0;
}

double
Parser::number()
{	
	if (lex.type == LEX_NUMBER) {
		double value = lex.value;
		gl();
		return value;
	} else if (lex.type == LEX_LPAREN) {
		gl();
		double value = expr();
		if (lex.type != LEX_RPAREN) {
			throw "no right parenthesis";
		}
		gl();
		return value;
	} else {
		throw "wrong lexeme";
	}
	
	return 0.0;
}
