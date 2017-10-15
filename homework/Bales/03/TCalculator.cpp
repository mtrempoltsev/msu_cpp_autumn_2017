#include "TCalculator.h"

extern std::unordered_map<std::string, double> Constants;

double TCalculator::ToCalculate(const char* expr) {
    auto exitCode = TTokenizer::IsValidExpr(expr);
    if (exitCode != TExitCode::OK) { 
        throw ExitCodeException(exitCode);
    }
    TTokenizer* tokenizer = new TTokenizer(expr);
    auto res = _Expr(tokenizer);
    delete tokenizer;
    return res;
}

double TCalculator::_Expr(TTokenizer* const tokenizer) {
    auto leftOperand = _Term(tokenizer);
    auto token = tokenizer->GetToken();

    if (Token::End != token.second && Token::CloseBracket != token.second) {
        return Token::Plus != token.second ? leftOperand - _Expr(tokenizer) : leftOperand + _Expr(tokenizer);
    }
    else return leftOperand;
}

double TCalculator::_Term(TTokenizer* const tokenizer, size_t cntEnter) {
    auto leftOperand = _Prim(tokenizer);
    auto token = tokenizer->GetToken();

    if (Token::Mul == token.second || Token::Div == token.second) {
        /* Проверка на кол-во "вложенности" делений
         * Если бы не было данной проверки, то программа воспринимала бы такое выражение "2 / 3 * 4"
         * Как "2 / (3 * 4)" = 1 / 6, что != 8 / 3
         * Для борбы с этой проблемой было решено подсчитывать степень вложенности делений
         * Т.е. все знаки ('*' или '/'), которые внутри '/' будут инвертироваться
         */
        if ((cntEnter & 1) == 0) { // Проверка на нечётность
            return Token::Mul != token.second ? leftOperand / _Term(tokenizer, cntEnter + 1) : leftOperand * _Term(tokenizer, cntEnter);
        }
        else {
            return Token::Mul != token.second ? leftOperand * _Term(tokenizer, cntEnter) : leftOperand / _Term(tokenizer, cntEnter + 1);
        }
    }
    else {
        tokenizer->RetrieveToken(); // Когда getToken равняется '+', '-', '(' или ')', нам необходимо вернуть этот токен назад в expr
        return leftOperand;
    }
}

double TCalculator::_Prim(TTokenizer* const tokenizer) {
    auto token = tokenizer->GetToken();

    if (Token::Number == token.second) {
        return std::stoi(token.first);
    }
    else if (Token::Minus == token.second) {
        return -_Prim(tokenizer);
    }
    else if (Token::DefConstant == token.second) {
        return Constants[token.first];
    }
    else return (_Expr(tokenizer));
}
