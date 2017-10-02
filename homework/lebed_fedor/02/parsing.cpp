#include <ctype.h>
#include "parsing.h"
#include "parsing_error.h"

struct Tokenizer {
    const char *cur_pos;
    const char *next_pos;
    Token token;

    Tokenizer(const char *str): next_pos(str) {
        next_token();
    }

    void next_token() {
        cur_pos = next_pos;
        while (isspace(*cur_pos)) {
            cur_pos++;
        }
        next_pos = cur_pos;

        if (*next_pos == '\0') {
            token.type = Token::End;
            return;
        }

        if (isdigit(*next_pos)) {
            token.type = Token::Number;
            int value = 0;
            do {
                value *= 10;
                value += *next_pos-'0';
            } while (isdigit(*++next_pos));
            token.value = value;
            return;
        }

        token.type = Token::Operation;
        token.value = *next_pos++;
    }
};

class Parser {
    Tokenizer _tok;
    int _value;

public:
    Parser(const char *str): _tok(str) {
        _value = expr();
        if (_tok.token.type != Token::End) {
            throw ParseError(Token::End, _tok.cur_pos);
        }
    }

    int value() {
        return _value;
    }

private:
    int expr() {
        int value = term();
        while (_tok.token.type == Token::Operation) {
            if (_tok.token.value == '+') {
                _tok.next_token();
                value += term();
            }
            else if (_tok.token.value == '-') {
                _tok.next_token();
                value -= term();
            }
            else {
                break;
            }
        }

        return value;
    }

    int term() {
        int value = prim();
        while (_tok.token.type == Token::Operation) {
            if (_tok.token.value == '*') {
                _tok.next_token();
                value *= prim();
            }
            else if (_tok.token.value == '/') {
                _tok.next_token();
                value /= prim();
            }
            else {
                break;
            }
        }

        return value;
    }

    int prim() {
        if (_tok.token.type == Token::Operation && _tok.token.value == '-') {
            _tok.next_token();
            return -number();
        }

        return number();
    }

    int number() {
        if (_tok.token.type == Token::Operation && _tok.token.value == '(') {
            _tok.next_token();
            int value = expr();
            if (_tok.token.type == Token::Operation && _tok.token.value == ')') {
                _tok.next_token();
                return value;
            }
            throw ParseError(Token::Operation, _tok.cur_pos);
        }

        if (_tok.token.type == Token::Number) {
            int value = _tok.token.value;
            _tok.next_token();
            return value;
        }

        throw ParseError(Token::Number, _tok.cur_pos);
    }
};

int calc_parse(const char *s) {
    Parser p(s);
    return p.value();
}
