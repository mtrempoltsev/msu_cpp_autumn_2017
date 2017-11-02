#pragma once
#include <stdexcept>
#include "Parser.h"

enum class Token {
    Plus,
    Minus,
    Mult,
    Div,
    Num,
    OpenBracket,
    CloseBracket,
    Word,
    End,
    Invalid,
};

template <typename T>
class Tokenizer {
public:
    void set(const char* str) {
        this->str = str;
        value = 0;
        currentToken = Token::Invalid;
    }

    T getToken() {
        while (auto c = *str++) {
            switch (c) {
                case ' ':
                    continue; // Skip whitespaces
                case '+':
                    currentToken = Token::Plus;
                    return 0;
                case '-':
                    currentToken = Token::Minus;
                    return 0;
                case '*':
                    currentToken = Token::Mult;
                    return 0;
                case '/':
                    currentToken = Token::Div;
                    return 0;
                case '(':
                    ++level;
                    currentToken = Token::OpenBracket;
                    return 0;
                case ')':
                    --level;
                    if (level < 0) {
                        throw std::runtime_error("Unexpected ')'");
                    }
                    currentToken = Token::CloseBracket;
                    return 0;
            }

            if (Parser<T>::isParsable(c)) {
                --str; // str was pointing at symbol following c
                value = Parser<T>::parse(str);
                currentToken = Token::Num;
                return value;
            }

            if (std::isalpha(c)) {
                int i = 0;
                wordBuffer[i] = c;
                while (std::isalpha(*str)) { // probably it should be alphanum
                    wordBuffer[++i] = *str++;
                }
                wordBuffer[++i] = 0;
                currentToken = Token::Word;
                return 0;
            }
            throw std::runtime_error(std::string("Invalid symbol: ") + c);
            //return Token::Invalid;
        }
        if (level > 0) {
            throw std::runtime_error(std::string("Expected ") + std::to_string(level) + std::string(" more ')'."));
        }
        currentToken = Token::End;
        return 0;
    }

    std::string tokenToStr(Token token) {
        switch (token) {
            case Token::Plus: return "Plus";
            case Token::Minus: return "Minus";
            case Token::Mult: return "Mult";
            case Token::Div: return "Div";
            case Token::Num: return "Num";
            case Token::OpenBracket: return "OpenBracket";
            case Token::CloseBracket: return "CloseBracket";
            case Token::Word: return "Word";
            case Token::End: return "End";
            case Token::Invalid: return "Invalid";
        }
        return "Unknown";
    }

    Token getCurrentToken() {
        return currentToken;
    }

    T getValue() {
        return value;
    }

    char* getWordBuffer() {
        return wordBuffer;
    }

private:
    const char* str;
    Token currentToken;
    T value;
    char wordBuffer[128]; // this buffer is used for reading constants
    int level = 0; // number of '(' minus number of ')' encountered 
};