#include <cstring>
#include <cctype>
#include "parser.h"

int64_t
number(const char* str, int32_t len)
{
	int64_t result = 0;
	int32_t i = 0;
	
	for (i = 0; i != len; ++i) {
		if (isspace(str[i])) continue;
		
		if (isdigit(str[i])) {
			result = result * 10 + int64_t(str[i] - '0');
		} else {
			throw "Wrong argument; Error in number";
		}
	}
	
	return result;
}

int64_t
prim(const char* str, int32_t len)
{
	int32_t i = 0;
	for (i = 0; i != len; ++i) {
		if (isspace(str[i])) continue;
		
		if (str[i] == '-') {
			return -prim(str + i + 1, len - i - 1);
		} else if (isdigit(str[i])) {
			return number(str + i, len - i);
		} else {
			throw "Wrong argument; Error in prim";
		}
	}
	
	throw "Wrong argument; Error in prim";
}

int64_t
term(const char* str, int32_t len)
{	
	int32_t i = 0;
	while (i != len && str[i] != '*' && str[i] != '/') {
		++i;
	}
	
	if (i == len) {
		return prim(str, len);
	} else if (str[i] == '*') {
		return prim(str, i) * term(str + i + 1, len - i - 1);
	} else if (str[i] == '/') {
		return prim(str, i) / term(str + i + 1, len - i - 1);
	} else {
		throw "Wrong argument; Error in term";
	}
}

int64_t
expr(const char* str, int32_t len)
{
	int32_t i = 0;
	bool prevWasDigit = false;//to determine unary and binary minuses
	while (i != len && str[i] != '+' && (str[i] != '-' || prevWasDigit == false)) {
		if (isdigit(str[i])) {
			prevWasDigit = true;
		} else if (!isspace(str[i])) {
			prevWasDigit = false;
		}
		
		i++;
	}
	
	if (i == len) {
		return term(str, len);
	} else if (str[i] == '+') {
		return term(str, i) + expr(str + i + 1, len - i - 1);
	} else if (str[i] == '-') {
		return term(str, i) - expr(str + i + 1, len - i - 1);
	} else {
		throw "Wrong argument; Error in expr";
	}
}

int64_t
calc(const char* str)
{
	return expr(str, strlen(str));
}
