#pragma once
#include <cstdint>

/*
grammar:

expr = term { + or - term }
term = prim { * or / term }
prim = number or -number

*/

int64_t number(const char*, int32_t);
int64_t prim(const char*, int32_t);
int64_t term(const char*, int32_t);
int64_t expr(const char*, int32_t);
int64_t calc(const char*);


