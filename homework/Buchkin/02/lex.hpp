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
	LEX_UNARMINUS,
	LEX_FIN,
	LEX_ERROR
};

struct Lex
{
	lexType type;
	int64_t value;
	Lex(lexType type_ = LEX_NULL, int64_t value_ = 0): type(type_), value(value_) {}
};

