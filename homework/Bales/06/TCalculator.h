#pragma once
#include "TTokenizer.h"
#include "TParser.h"

extern std::unordered_map<std::string, double> Constants;

template<typename T = int, typename Parser = TParser<T> >
class TCalculator {
public:
    static T ToCalculate(const char* expr);
    static bool IsValidExpr(const char* expr);
private:
    static T _Expr(TTokenizer* const tokenizer);
    static T _Term(TTokenizer* const tokenizer, size_t cntEnter = 0);
    static T _Prim(TTokenizer* const tokenizer);
};

template<typename T, typename Parser>
T TCalculator<T, Parser>::ToCalculate(const char* expr) {
    /*
    auto exitCode = TTokenizer::IsValidExpr(expr);
    if (exitCode != TExitCode::OK) { 
        throw ExitCodeException(exitCode);
    }
    */
    TTokenizer* tokenizer = new TTokenizer(expr);
    T res = _Expr(tokenizer);
    delete tokenizer;
    return res;
}

template<typename T, typename Parser>
bool TCalculator<T, Parser>::IsValidExpr(const char* expr) {
    char* cpyExpr = (char*)malloc(sizeof(char) * strlen(expr));
    memcpy(cpyExpr, expr, strlen(expr));
    const char* linkExpr = cpyExpr;
    auto tmpTokenizer = new TTokenizer(linkExpr);
    while (true) {
        const auto token = tmpTokenizer->GetToken();
        if (token.second == Token::End) {
            break;
        }
        if (token.second == Token::Invalid) {
            delete tmpTokenizer;
            return false;
        }
        else if (token.second == Token::Number 
                || token.second == Token::DefConstant) {
            auto str = token.second == Token::Number
                        ? token.first
                        : std::to_string(Constants[token.first]);
            try {
                Parser::Parse(str);
            }
            catch (const ExitCodeException& ex) {
                std::cerr << ex.what() << std::endl;
                return false;
            }
        }
    }
    delete tmpTokenizer;
    return true;
}


template<typename T, typename Parser>
T TCalculator<T, Parser>::_Expr(TTokenizer* const tokenizer) {
    T leftOperand = _Term(tokenizer);
    auto token = tokenizer->GetToken();

    if (Token::End != token.second && Token::CloseBracket != token.second) {
        return Token::Plus != token.second 
        ? leftOperand - _Expr(tokenizer) 
        : leftOperand + _Expr(tokenizer);
    }
    else return leftOperand;
}

template<typename T, typename Parser>
T TCalculator<T, Parser>::_Term(TTokenizer* const tokenizer, size_t cntEnter) {
    T leftOperand = _Prim(tokenizer);
    auto token = tokenizer->GetToken();

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
        tokenizer->RetrieveToken(); // Когда getToken равняется '+', '-', '(' или ')', нам необходимо вернуть этот токен назад в expr
        return leftOperand;
    }
}

template<typename T, typename Parser>
T TCalculator<T, Parser>::_Prim(TTokenizer* const tokenizer) {
    auto token = tokenizer->GetToken();

    if (Token::Number == token.second) {
        return Parser::Parse(token.first);
    }
    else if (Token::Minus == token.second) {
        return -_Prim(tokenizer);
    }
    else if (Token::DefConstant == token.second) {
        return Constants[token.first];
    }
    else return (_Expr(tokenizer));
}
