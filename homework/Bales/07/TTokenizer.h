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
    void ReturnToken(); // come back token to expr

private:
    struct Expr {
        std::string _expr; // input data
        size_t _curPos;

        Expr(const char*& expr) : _expr(expr), _curPos(0) { }
        ~Expr() { 
            _curPos = 0;
        }

        char GetSymbol() noexcept {
            return this->_curPos >= this->_expr.length() ? '\0' : this->_expr[this->_curPos++];
        }
        void ReturnSymbol() noexcept {
            if (this->_curPos > 0) {
                this->_curPos--;
            }
        }
    };

    Expr _expr;
};