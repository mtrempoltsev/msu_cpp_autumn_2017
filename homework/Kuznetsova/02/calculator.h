#include <stdio.h>
#include <cctype>
#include <iostream>
#include <string>  // std::string

using namespace std;
int parse_expression(const char*& input);
int parse_term(const char*& input);
int parse_primary(const char*& input);

enum class Token { Invalid, Minus, Plus, Mul, Div, Number, End };

extern const char* message;
