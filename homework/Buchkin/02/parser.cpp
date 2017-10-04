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
	int32_t i = len - 1;
	while (i >= 0 && str[i] != '*' && str[i] != '/') {
		--i;
	}
	
	if (i == -1) {
		return prim(str, len);
	} else if (str[i] == '*') {
		return term(str, i) * prim(str + i + 1, len - i - 1);
	} else if (str[i] == '/') {
		//zero-division checking
		int64_t dividend = term(str, i);
		int64_t divider = prim(str + i + 1, len - i - 1);
		if (divider == 0) {
			throw "Zero division";
		}
		return dividend / divider;
	} else {
		throw "Wrong argument; Error in term";
	}
}

int64_t
expr(const char* str, int32_t len)
{
	int32_t i = len - 1;
	while (i >= 0 && str[i] != '+') {
		//minus - unary or binary?
		if (str[i] == '-') {
			int32_t j = i - 1;
			while (j >= 0 && isspace(str[j])) {
				--j;
			}
			if (j == -1 || !isdigit(str[j])) {//minus is unary
				i = j + 1;
			} else {
				break;
			}
		}
		--i;
	}
	
	if (i == -1) {
		return term(str, len);
	} else if (str[i] == '+') {
		return expr(str, i) + term(str + i + 1, len - i - 1);
	} else if (str[i] == '-') {
		return expr(str, i) - term(str + i + 1, len - i - 1);
	} else {
		throw "Wrong argument; Error in expr";
	}
}

int64_t
calc(const char* str)
{
	return expr(str, strlen(str));
}
