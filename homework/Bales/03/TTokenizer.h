#pragma once 
#include "DefFunc.h"

enum class Token {
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    OpenBracket,
    CloseBracket,
    DefConstant,
    End
};

class TTokenizer {
public:
    TTokenizer(const char*& expr);
    ~TTokenizer();
    std::pair<std::string, Token> GetToken(); // get token from expr
    void RetrieveToken(); // come back token to expr
    static TExitCode IsValidExpr(const char* expr); // static method to validate expr

private:
    const char* _expr = nullptr; // input data
};