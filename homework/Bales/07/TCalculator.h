#pragma once
#include "TTokenizer.h"
#include "TParser.h"

extern const std::unordered_map<std::string, double> Constants;

template<typename TItem = int, typename Parser = TParser<TItem> >
class TCalculator {
public:
    static TItem ToCalculate(const char* expr);
    static bool IsValidExpr(const char* expr);
private:
    static TItem _Expr(const std::unique_ptr<TTokenizer>& tokenizer) noexcept;
    static TItem _Term(const std::unique_ptr<TTokenizer>& tokenizer, size_t cntEnter = 0) noexcept;
    static TItem _Prim(const std::unique_ptr<TTokenizer>& tokenizer) noexcept;
};

template<typename TItem, typename Parser>
TItem TCalculator<TItem, Parser>::ToCalculate(const char* expr) {
    if (!TCalculator<TItem, Parser>::IsValidExpr(expr)) {
        throw std::runtime_error("Expression is not valid.");
    }
    auto tokenizer = std::make_unique<TTokenizer>(expr);
    TItem res = _Expr(tokenizer);
    return res;
}

template<typename TItem, typename Parser>
bool TCalculator<TItem, Parser>::IsValidExpr(const char* expr) {
    auto cpyExpr = std::string(expr);
    const char* linkExpr = cpyExpr.c_str();
    
    auto tmpTokenizer = std::make_unique<TTokenizer>(linkExpr);
    while (true) {
        const auto token = tmpTokenizer->GetToken();
        if (token.second == Token::End) {
            break;
        }
        if (token.second == Token::Invalid) {
            return false;
        }
        else if (token.second == Token::Number 
                || token.second == Token::DefConstant) {
            auto str = token.second == Token::Number
                        ? token.first
                        : std::to_string(Constants.at(token.first));
            try {
                Parser::Parse(str);
            }
            catch (const std::runtime_error& ex) {
                std::cerr << ex.what() << std::endl;
                return false;
            }
        }
    }
    return true;
}

template<typename TItem, typename Parser>
TItem TCalculator<TItem, Parser>::_Expr(const std::unique_ptr<TTokenizer>& tokenizer) noexcept {
    TItem leftOperand = _Term(tokenizer);
    const auto token = tokenizer->GetToken();
    if (Token::End != token.second && Token::CloseBracket != token.second) {
        return Token::Plus != token.second 
            ? leftOperand - _Expr(tokenizer) 
            : leftOperand + _Expr(tokenizer);
    }
    else return leftOperand;
}

template<typename TItem, typename Parser>
TItem TCalculator<TItem, Parser>::_Term(const std::unique_ptr<TTokenizer>& tokenizer, size_t cntEnter) noexcept {
    TItem leftOperand = _Prim(tokenizer);
    const auto token = tokenizer->GetToken();
    if (Token::Mul == token.second || Token::Div == token.second) {
        /* Проверка на кол-во "вложенности" делений
         * Если бы не было данной проверки, то программа воспринимала бы такое выражение "2 / 3 * 4"
         * Как "2 / (3 * 4)" = 1 / 6, что != 8 / 3
         * Для борбы с этой проблемой было решено подсчитывать степень вложенности делений
         * Т.е. все знаки ('*' или '/'), которые внутри '/' будут инвертироваться
         */
        if ((cntEnter & 1) == 0) { // Проверка на нечётность
            return Token::Mul != token.second 
                ? leftOperand / _Term(tokenizer, cntEnter + 1) 
                : leftOperand * _Term(tokenizer, cntEnter);
        }
        else {
            return Token::Mul != token.second 
                ? leftOperand * _Term(tokenizer, cntEnter) 
                : leftOperand / _Term(tokenizer, cntEnter + 1);
        }
    }
    else {
        if (Token::CloseBracket == token.second 
            || Token::Minus == token.second 
            || Token::Plus == token.second) {
                tokenizer->ReturnToken(); // Когда getToken равняется '+', '-' или ')', нам необходимо вернуть этот токен назад в expr
            }            
        return leftOperand;
    }
}

template<typename TItem, typename Parser>
TItem TCalculator<TItem, Parser>::_Prim(const std::unique_ptr<TTokenizer>& tokenizer) noexcept {
    const auto token = tokenizer->GetToken();
    if (Token::Number == token.second) {
        return Parser::Parse(token.first);
    }
    else if (Token::Minus == token.second) {
        return -_Prim(tokenizer);
    }
    else if (Token::DefConstant == token.second) {
        return Constants.at(token.first);
    }
    else return (_Expr(tokenizer));
}