#pragma once

#include <iostream>
#include <unordered_map>

#include "tokenizer.h"

extern const char *message;

//разбор выражений с вычислением
template <typename T> class Parser {
  public:
    Parser(char *input, std::unordered_map<std::string, double> constants)
        : tokenizer_(input, constants) {}
    T calculate();

  private:
    Tokenizer<T> tokenizer_;
    bool reached_end_ = false;

    T parse_primary();
    T parse_term();
    T parse_expression();
};

template <typename T> T Parser<T>::calculate() {
    T value = parse_expression();
    if (!tokenizer_.check_balance())
        return 0;
    if (reached_end_ == false) {
        std::cout << message << std::endl;
        std::cerr << "Extra characters\n";
        return 0;
    }
    return value;
}

//выделяем целые числа
template <typename T> T Parser<T>::parse_primary() {
    if (!tokenizer_.check_pointer())
        return 0;
    auto token = tokenizer_.get_token();
    T n = 0;
    switch (token) {
    case Token::Number:
        tokenizer_.token_back(); //возвращаемся к только что
        //прочитанному началу числа
        n = tokenizer_.read_number();
        return n;
    case Token::Const:
        tokenizer_.token_back(); //возвращаемся к только что
        //прочитанному началу числа
        n = tokenizer_.read_constant();
        return n;
    case Token::Minus:
        return -parse_primary(); //унарный минус
    case Token::LBracket:
        return parse_expression();
    case Token::Invalid:
        std::cout << message << std::endl;
        std::cerr << "Incorrect symbol\n";
        return 0;
    default:
        std::cout << message << std::endl;
        std::cerr << "Invalid syntax\n";
        return 0;
    }
    return n;
}

//выделяем множители
template <typename T> T Parser<T>::parse_term() {
    if (!tokenizer_.check_pointer())
        return 0;

    auto left = parse_primary();
    auto token = tokenizer_.get_token();

    while (token == Token::Mul || token == Token::Div) {
        T right = parse_primary();
        if (token == Token::Mul) {
            left *= right;
        } else {
            if (right == 0) {
                std::cout << message << std::endl;
                std::cerr << "Division by zero\n";
                return 0;
            }
            left /= right;
        }

        token = tokenizer_.get_token();
    }
    if (token == Token::Invalid) {
        std::cout << message << std::endl;
        std::cerr << "Incorrect symbol\n";
        return 0;
    }
    tokenizer_.token_back(); //дойдя до + или -, возвращаем токен обратно
    return left;
}

//выделяем слагаемые
template <typename T> T Parser<T>::parse_expression() {
    if (!tokenizer_.check_pointer())
        return 0;

    auto left = parse_term();
    auto token = tokenizer_.get_token();
    switch (token) {
    case Token::Plus:
        return left + parse_expression();
    case Token::Minus:
        return left - parse_expression();
    case Token::RBracket:
        return left;
    case Token::Invalid:
        std::cout << message << std::endl;
        std::cerr << "Incorrect symbol\n";
        return 0;
    case Token::End:
        reached_end_ = true;
        return left;
    default:
        return left;
    }
    return left;
}
