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
    const char *token_start = str;
    int value = 0;
    do {
        if (__builtin_mul_overflow(value, 10, &value)
            || __builtin_add_overflow(value, *str-'0', &value)) {
            str = token_start;
            throw "value too big for int";
        }
    } while (std::isdigit(*++str));
    return value;
}

// prim = number | -number
int get_prim(const char *&str)
{
    Token tok = get_token(str);
    if (tok == Token::Minus) {
        str++;
        tok = get_token(str);
        if (tok == Token::Number) {
            // cannot overflow since |INT_MIN| = |INT_MAX| + 1
            return -get_number(str);
        }
        else {
            throw "number expected";
        }
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
        const char *op_token_start = str++;
        int operand = get_prim(str);
        if (op == Token::Mul) {
            if (__builtin_mul_overflow(value, operand, &value)) {
                str = op_token_start;
                throw "mul overflow";
            }
        }
        else {
            if (operand == 0) {
                str = op_token_start;
                throw "attempt to divide by zero";
            }
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
        const char *op_token_start = str++;
        int operand = get_term(str);
        if (op == Token::Plus) {
            if (__builtin_add_overflow(value, operand, &value)) {
                str = op_token_start;
                throw "add overflow";
            }
        }
        else {
            if (__builtin_sub_overflow(value, operand, &value)) {
                str = op_token_start;
                throw "sub overflow";
            }
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
