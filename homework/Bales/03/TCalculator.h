#pragma once
#include "TTokenizer.h"

class TCalculator {
public:
    static double ToCalculate(const char* expr);

private:
    static double _Expr(TTokenizer* const tokenizer);
    static double _Term(TTokenizer* const tokenizer, size_t cntEnter = 0);
    static double _Prim(TTokenizer* const tokenizer);
};