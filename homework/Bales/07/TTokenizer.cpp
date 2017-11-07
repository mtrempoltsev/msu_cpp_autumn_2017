#include "TTokenizer.h"

TTokenizer::TTokenizer(const char*& expr) : _expr(expr) { }

TTokenizer::~TTokenizer() { }

std::pair<std::string, Token> TTokenizer::GetToken() {
    while (const auto ch = this->_expr.GetSymbol()) {
        switch (ch) {
            case ' ': continue;
            case '+': return std::make_pair("+", Token::Plus);
            case '-': return std::make_pair("-", Token::Minus);
            case '*': return std::make_pair("*", Token::Mul);
            case '/': return std::make_pair("/", Token::Div);
            case '(': return std::make_pair("(", Token::OpenBracket);
            case ')': return std::make_pair(")", Token::CloseBracket);
        }

        if (ch >= '0' && ch <= '9') {
            std::string str { ch };
            while (const auto n_ch = this->_expr.GetSymbol()) {
                if ((n_ch >= '0' && n_ch <= '9') || n_ch == '.')
                    str += n_ch;
                else break;
            }
            return std::make_pair(str, Token::Number);
        }
        else if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
            std::string str { ch };
            while (const auto n_ch = this->_expr.GetSymbol()) {
                if ((n_ch >= 'a' && n_ch <= 'z') || (n_ch >= 'A' && n_ch <= 'Z'))
                    str += n_ch;
                else break;
            }
            return std::make_pair(str, Token::DefConstant);            
        }
        else return std::make_pair(std::string({ ch }), Token::Invalid);
    }
    return std::make_pair("", Token::End);
}

void TTokenizer::ReturnToken() {
    this->_expr.ReturnSymbol();
}