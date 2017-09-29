#pragma once
#include <string>
#include <cstring>
#include "lex.hpp"

class Scanner
{
	char currentSymbol;
	uint32_t currentIndex = 0;
	const char *str;//init with argv[1]
	void gc();
	bool prevLexWasDigit = false;//to distinguish binary and unary minuses

public:
	Scanner(const char *str_): str(str_)
	{
		if (str == nullptr || strlen(str) == 0) {
			throw "Empty input";
		}
		gc();
	}
	
	Lex gl();
};

void
Scanner::gc()
{
	currentSymbol = str[currentIndex++];
}

Lex
Scanner::gl()
{
	while (isspace(currentSymbol)) gc();//skipping spaces
	
	if (isdigit(currentSymbol)) {
		int64_t result = 0;
		while (isdigit(currentSymbol)) {
			result = result * 10 + (int64_t)(currentSymbol - '0');
			gc();
		}
		
		prevLexWasDigit = true;
		
		return Lex(LEX_NUMBER, result);
	}
	//if symbol is not a digit, program goes here
	Lex l;
	switch (currentSymbol) {
		
		case '+':
			gc();
			prevLexWasDigit = false;
			return Lex(LEX_PLUS);
		
		case '-'://unary or binary?
			gc();
			if (prevLexWasDigit) {
				l.type = LEX_MINUS;
			} else {
				l.type = LEX_UNARMINUS;
			}
			prevLexWasDigit = false;
			return l;
		
		case '*':
			gc();
			prevLexWasDigit = false;
			return Lex(LEX_MUL);
		
		case '/':
			gc();
			prevLexWasDigit = false;
			return Lex(LEX_DIV);
		
		case '\0':
			return Lex(LEX_FIN);
		
		default:
			return Lex(LEX_ERROR);
	}
}
