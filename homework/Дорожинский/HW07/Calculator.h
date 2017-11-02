#pragma once
#include <stdexcept>
#include <unordered_map>
#include "Tokenizer.h"

template <typename T>
class Calculator {
public:

    T calculate(const char* str) {
        tokenizer.set(str);
        return _calc();
    }
private:
    T _calc() { // Here we add or subtract items. Item is a sequence of multiplications/divisions
        T result = getItem();
        validateOperation();
        while ((tokenizer.getCurrentToken() == Token::Plus) || (tokenizer.getCurrentToken() == Token::Minus)) {
            if (tokenizer.getCurrentToken() == Token::Plus) {
                result += getItem();
            } else {
                result -= getItem();
            }
            validateOperation();
        }
        return result;
    }

    T getItem() {
        T result = getNumber();
        validateOperation();
        while ((tokenizer.getCurrentToken() == Token::Mult) || (tokenizer.getCurrentToken() == Token::Div)) {
            if (tokenizer.getCurrentToken() == Token::Mult) {
                result *= getNumber();
            } else {
                T value = getNumber();
                if (value == 0) {
                    throw std::invalid_argument("Zero division");
                }
                result /= value;
            }
            validateOperation();
        }
        return result;
    }

    T getNumber() {
        T result = tokenizer.getToken();
        int sign = 1;
        if (tokenizer.getCurrentToken() == Token::Minus) { // Things may start with '-' sign
            result = tokenizer.getToken();
            sign = -1;
        }
        if (tokenizer.getCurrentToken() == Token::Num) { // The simplest case
            tokenizer.getToken(); // When we done with a number we need to read token for next operation ('*', '/', '+', '-', 'END')
            return result * sign;
        }
        if (tokenizer.getCurrentToken() == Token::OpenBracket) {
            result = _calc();
            if (tokenizer.getCurrentToken() == Token::CloseBracket) { // _calc() returns control if it encountered 'END' or ')'. Operation after ')' should be read
                tokenizer.getToken();
            }
            return result * sign;
        }
        if (tokenizer.getCurrentToken() == Token::Word) {
            auto wordContainer = constants.find(tokenizer.getWordBuffer());
            if (wordContainer == constants.end()) {
                throw std::invalid_argument("Unknown word: " + std::string(tokenizer.getWordBuffer()));
            }
            result = wordContainer->second;
            tokenizer.getToken();
            return result * sign;
        }
        throw std::invalid_argument("Unexpected token: " + tokenizer.tokenToStr(tokenizer.getCurrentToken()));
        return 0;
    }

    void validateOperation() { // Throws if tokenizer's currentToken is not set to a valid operation or end
        Token token = tokenizer.getCurrentToken();
        if ((token == Token::Num) || (token == Token::OpenBracket) || (token == Token::Word)) {
            throw std::invalid_argument("Unexpected token: " + tokenizer.tokenToStr(token));
        }
    }
    
    Tokenizer<T> tokenizer;

    std::unordered_map<std::string, double> constants = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
};