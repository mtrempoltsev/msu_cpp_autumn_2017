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

template <class T = int>
struct Lex
{
	lexType type;
	T value;
	Lex(lexType type_ = LEX_NULL, T value_ = T()): type(type_), value(value_) {}
	Lex(const Lex& lex): type(lex.type), value(lex.value) {}
};
