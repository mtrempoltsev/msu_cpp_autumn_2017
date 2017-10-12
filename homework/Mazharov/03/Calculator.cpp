//
// Created by Ivan on 10.10.2017.
//
#include <ctype.h>
#include <string>
#include <unordered_map>
#include "Calculator.h"

std::unordered_map<std::string, double> constants =
        {
                { "Pi", 3.14 },
                { "e", 2.7 }
        };

Calculator::Calculator(char *input_string) {
    expression = input_string;
    in_brackets = 0;
}

double Calculator::expr() {
    //expr всегда начинается с term
    double result = term();

    while (true) {
        get_token();
        switch (this->cur_lex.name) {
            case Token::Plus:
                result += term();
                break;
            case Token::Minus:
                result -= term();
                break;
            case Token::Invalid:
                throw ("Error: invalid expr");
            default:
                return result;
        }
    }
}

double Calculator::term() {
    //term всегда начинается с prim
    double result = prim();
    double number;

    while (true) {
        get_token();
        switch (this->cur_lex.name) {
            case Token::Mul:
                result *= prim();
                break;
            case Token::Div:
                //проверка деления на 0
                number = prim();
                if (number != 0)
                    result /= number;
                else
                    throw ("Error: null division");
                break;
            case Token::Invalid:
                throw ("Error: invalid term");
            case Token::RB:
                if (!this->in_brackets)
                    throw ("Error: open bracket");
            default:
                //отступаем назад, если вышли за конец term
                --(this->expression);
                return result;
        }
    }
}

double Calculator::prim() {
    //prim всегда начинается с токена
    get_token();
    double tmp_expr;

    switch (this->cur_lex.name) {
        case Token::Number:
            return this->cur_lex.value;
        case Token::Minus:
            return -prim();
        case Token::e:
            return 2.7;
        case Token::Pi:
            return 3.14;
        case Token::LB:
            this->in_brackets++;
            tmp_expr = expr();
            if (this->cur_lex.name != Token::RB)
                throw ("Error: close brackets");
            this->in_brackets--;
            return tmp_expr;
        case Token::End:
            throw ("Error: prim expected");
        case Token::Invalid:
            throw ("Error: invalid prim");
        default:
            throw ("Wrong formatted input");
    }
}

void Calculator::get_token() {
    while (auto c = *(this->expression)++) {
        switch (c) {
            case ' ':
                continue;
            case '-':
                this->cur_lex.name = Token::Minus;
                return;
            case '+':
                this->cur_lex.name = Token::Plus;
                return;
            case '*':
                this->cur_lex.name = Token::Mul;
                return;
            case '/':
                this->cur_lex.name = Token::Div;
                return;
            case '(':
                this->cur_lex.name = Token::LB;
                return;
            case ')':
                this->cur_lex.name = Token::RB;
                return;
            default:

                if (c >= '0' && c <= '9') {
                    this->cur_lex.value = c - '0';
                    for (auto c = *(this->expression); c >= '0' && c <= '9';) {
                        this->cur_lex.value = this->cur_lex.value * 10 + c - '0';
                        c = *++(this->expression);
                    }
                    this->cur_lex.name = Token::Number;
                    return;
                }

                if (isalpha(c)){
                    std::string name = "";
                    name += c;
                    for (auto c = *(this->expression); isalpha(c);) {
                        name += c;
                        c = *++(this->expression);
                    }
                    if (constants[name]) {
                        this->cur_lex.name = Token::Number;
                        this->cur_lex.value = constants[name];
                        return;
                    }
                }
                this->cur_lex.name = Token::Invalid;
                return;
        }
    }
    this->cur_lex.name = Token::End;
}
