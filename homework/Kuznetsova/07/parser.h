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
    if (!tokenizer_.check_balance()) {
        throw std::runtime_error("Imbalanced brackets");
        return 0;
    }
    if (reached_end_ == false) {
        throw std::runtime_error("Didn't reach end");
        return 0;
    }
    return value;
}

//выделяем целые числа
template <typename T> T Parser<T>::parse_primary() {
    if (!tokenizer_.check_pointer()) {
        throw std::runtime_error("Invalid syntax");
        return 0;
    }
    auto token = tokenizer_.get_token();
    T n = 0;
    switch (token) {
    case Token::Number:
        tokenizer_.token_back(); //возвращаемся к только что
        //прочитанному началу числа
        try {
            n = tokenizer_.read_number();
        } catch (const std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        return n;
    case Token::Const:
        tokenizer_.token_back(); //возвращаемся к только что
        //прочитанному началу названия константы
        try {
            n = tokenizer_.read_constant();
        } catch (const std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        return n;
    case Token::Minus:
        try {
            n = -parse_primary(); //унарный минус
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        return n;
    case Token::LBracket:
        try {
            n = parse_expression();
        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        return n;
    case Token::Invalid:
        throw std::runtime_error("Incorrect symbol");
        return 0;
    default:
        throw std::runtime_error("Invalid syntax");
        return 0;
    }
    return n;
}

//выделяем множители
template <typename T> T Parser<T>::parse_term() {

    if (!tokenizer_.check_pointer()) {
        throw std::runtime_error("Invalid syntax");
        return 0;
    }
    T right = 0;
    T left = 0;
    try {
        left = parse_primary();

    } catch (std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
    }
    auto token = tokenizer_.get_token();

    while (token == Token::Mul || token == Token::Div) {
        try {
            right = parse_primary();

        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }

        if (token == Token::Mul) {
            left *= right;
        } else {
            if (right == 0) {
                throw std::runtime_error("Division by zero");
                return 0;
            }
            left /= right;
        }

        token = tokenizer_.get_token();
    }
    if (token == Token::Invalid) {
        throw std::runtime_error("Incorrect symbol");
        return 0;
    }
    tokenizer_.token_back(); //дойдя до + или -, возвращаем токен обратно
    return left;
}

//выделяем слагаемые
template <typename T> T Parser<T>::parse_expression() {
    if (!tokenizer_.check_pointer()) {
        throw std::runtime_error("Invalid syntax");
        return 0;
    }
    T right = 0;
    T left = 0;
    try {
        left = parse_term();

    } catch (std::runtime_error &error) {
        std::cerr << error.what() << std::endl;
    }
    auto token = tokenizer_.get_token();
    switch (token) {
    case Token::Plus:
        try {
            right = parse_expression();

        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        return left + right;
    case Token::Minus:
        try {
            right = parse_expression();

        } catch (std::runtime_error &error) {
            std::cerr << error.what() << std::endl;
        }
        return left - right;
    case Token::RBracket:
        return left;
    case Token::Invalid:
        throw std::runtime_error("Incorrect symbol");
        return 0;
    case Token::End:
        reached_end_ = true;
        return left;
    default:
        return left;
    }
    return left;
}
