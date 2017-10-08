#pragma once

#include <iostream>

enum lexType
{
	LEX_NULL,
	LEX_NUMBER,
	LEX_PLUS,
	LEX_MINUS,
	LEX_MUL,
	LEX_DIV,
	LEX_LPAREN,
	LEX_RPAREN,
	LEX_FIN,
	LEX_ERROR
};

struct Lex
{
	lexType type;
	double value;
	Lex(lexType type_ = LEX_NULL, double value_ = 0.0): type(type_), value(value_) {}
	Lex(const Lex& lex): type(lex.type), value(lex.value) {}
};
