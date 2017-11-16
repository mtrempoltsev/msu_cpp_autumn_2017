#pragma once

#include <iostream>
#include <unordered_map>

#include "number_reader.h"

extern const char *message;

enum class Token {
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    LBracket,
    RBracket,
    Const,
    Number,
    End
};
//отвечает за техническую работу по извлечению токенов из строки, считыванию
//чисел и констант посимвольно
template <typename T> class Tokenizer {
  public:
    Tokenizer(char *input, std::unordered_map<std::string, double> constants)
        : input_(input), constants_(constants) {}

    Token get_token();
    void token_back();
    T read_number();
    T read_constant();
    bool check_pointer();
    bool check_balance();

  private:
    char *input_;
    std::unordered_map<std::string, double> constants_; // constants type?!
    int brackets_balance_ = 0;
};

//определяем тип текущего токена
template <typename T> Token Tokenizer<T>::get_token() {
    while (auto c = *input_++) {
        switch (c) {
        case ' ':
            continue;
        case '+':
            return Token::Plus;
        case '-':
            return Token::Minus;
        case '*':
            return Token::Mul;
        case '/':
            return Token::Div;
        case '(':
            brackets_balance_ += 2; //при разборе мы дважды обращаемся к
            //правым скобкам, поэтому левые
            //учитываем с двойным весом
            // std::cout<<brackets_balance_<<c<<std::endl;
            return Token::LBracket;
        case ')':

            brackets_balance_--;
            // std::cout<<brackets_balance_<<c<<std::endl;
            return Token::RBracket;
        }

        if (c >= '0' && c <= '9') {
            return Token::Number;
        } else if (isalpha(c)) {
            return Token::Const; //корректность константы проверяется отдельно

        } else
            return Token::Invalid;
    }

    return Token::End;
}

template <typename T> void Tokenizer<T>::token_back() { --input_; }

template <typename T> T Tokenizer<T>::read_number() {
    T n = 0;
    if (NumberReader<T>::read_number(input_, n))
        return n;
    else {
        // std::cerr << "Too long\n";
        throw std::runtime_error("Too long");
        return 0;
    }
    return n;
}

template <typename T> T Tokenizer<T>::read_constant() {
    T n = 0;
    std::string name;
    for (auto c = *input_; isalpha(c);) {
        name += c;
        c = *++input_;
    }
    auto map_iterator = constants_.find(name);
    if (map_iterator != constants_.end()) {
        n = constants_.at(name);

    } else {
        throw std::runtime_error("Invalid syntax");
        return 0;
    }
    return n;
}

template <typename T> bool Tokenizer<T>::check_pointer() {
    if (!(*input_)) {
        return false;
    }
    return true;
}

template <typename T> bool Tokenizer<T>::check_balance() {
    if (brackets_balance_ != 0) {
        return false;
    }
    return true;
}
