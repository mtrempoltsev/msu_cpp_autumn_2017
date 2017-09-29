#pragma once
#include "scanner.hpp"

/*
grammar:

expr = term { + or - term }
term = prim { * or / term }
prim = number or -number

*/

class Parser
{
	Lex l;
	void gl() {l = sc.gl();} //get next lexeme
	Scanner sc;
	
	int64_t expr();
	int64_t term();
	int64_t prim();
	int64_t number();
	
public:
	Parser(const char *str): sc(str) {}
	
	int64_t calc();
};

int64_t
Parser::calc()
{
	gl();
	return expr();
}

int64_t
Parser::expr()
{
	int64_t result = term();
	
	while (l.type != LEX_FIN) {
		lexType lt = l.type;
		gl();
		switch (lt) {
			case LEX_PLUS:
				result += term();
				break;
			case LEX_MINUS:
				result -= term();
				break;
			default:
				throw "Wrong argument; Error in expr";
		}
	}
	
	return result;
}

int64_t
Parser::term()
{
	int64_t result = prim();
	
	while (l.type != LEX_PLUS && l.type != LEX_MINUS && l.type != LEX_FIN) {
		lexType lt = l.type;
		gl();
		switch (lt) {
			case LEX_MUL:
				result *= prim();
				break;
			case LEX_DIV:
				result /= prim();
				break;
			default:
				throw "Wrong argument; Error in term";
		}
	}
	
	return result;
}

int64_t
Parser::prim()
{
	if (l.type == LEX_UNARMINUS) {
		gl();
		return -number();
	} else if (l.type == LEX_NUMBER) {
		return number();
	} else {
		throw "Wrong argument; Error in prim";
	}
	
	return 0;
}

int64_t
Parser::number()
{
	if (l.type != LEX_NUMBER) {
		throw "Wrong argument; Error in number";
	}
	int64_t result = l.value;
	gl();
	return result;
}


