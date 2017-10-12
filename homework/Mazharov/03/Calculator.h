//
// Created by Ivan on 10.10.2017.
//

#ifndef CALCULATOR_CALCULATOR_H
#define CALCULATOR_CALCULATOR_H

//класс типов токенов
enum class Token {
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    LB,
    RB,
    e,
    Pi,
    End
};

struct lexeme {
    Token name;
    double value;
};

class Calculator {
public:
    explicit Calculator(char* input_string);
    double expr();
    double term();
    double prim();
    void get_token();
private:
    lexeme cur_lex;
    char* expression;
    int in_brackets;
};

#endif //CALCULATOR_CALCULATOR_H
