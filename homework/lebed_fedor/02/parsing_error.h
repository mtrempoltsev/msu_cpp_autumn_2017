#pragma once
#include "parsing.h"

using ParseError = std::pair<Token::Type, const char *>;

void print_parsing_error(ParseError err, const char *str);
