#include <cctype>

// defines token types in string
enum class Token
{
    Invalid,
    Minus,
    Plus,
    Div,
    Mul,
    Number,
    End
};

// installs str at start of token and returns it's type
// if token type is NUMBER getNumber should be used to retrieve it's value
// NOTE: does not move to next token
Token get_token(const char *&str)
{
    while (std::isspace(*str)) {
        str++;
    }

    switch (*str) {
        case '-': return Token::Minus;
        case '+': return Token::Plus;
        case '*': return Token::Mul;
        case '/': return Token::Div;
        case '\0': return Token::End;
    }

    if (std::isdigit(*str)) {
        return Token::Number;
    }

    return Token::Invalid;
}

// returns number if token type is NUBMER and moves to next token
int get_number(const char *&str)
{
    int value = 0;
    do {
        value *= 10;
        value += *str-'0';
    } while (std::isdigit(*++str));
    return value;
}

// prim = number | -number
int get_prim(const char *&str)
{
    Token tok = get_token(str);
    if (tok == Token::Minus) {
        str++;
        return -get_number(str);
    }
    else if (tok == Token::Number) {
        return get_number(str);
    }
    else {
        throw "number expected";
    }
}

// term = prim | term*prim | term/prim
int get_term(const char *&str)
{
    int value = get_prim(str);
    Token op = get_token(str);
    while (op == Token::Mul || op == Token::Div) {
        str++;
        int operand = get_prim(str);
        if (op == Token::Mul) {
            value *= operand;
        }
        else {
            value /= operand;
        }

        op = get_token(str);
    }
    return value;
}

// expr = term | expr + term | expr - term
int get_expr(const char *&str)
{
    int value = get_term(str);
    Token op = get_token(str);
    while (op == Token::Plus || op == Token::Minus) {
        str++;
        int operand = get_term(str);
        if (op == Token::Plus) {
            value += operand;
        }
        else {
            value -= operand;
        }

        op = get_token(str);
    }
    return value;
}

// validates & parses expression in str
// NOTE: throws error if str is invalid
int calc_parse(const char *&str) {
    int value = get_expr(str);
    if (get_token(str) != Token::End) {
        throw "EOF expected";
    }
    return value;
}
