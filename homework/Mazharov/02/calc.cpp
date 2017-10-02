#include <iostream>

/* Использованная грамматика:
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | - number | + number
    number = [0-9]
 */

//класс типов токенов
enum class Token {
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
};

//функция получает следующий токен из строки
Token get_token(const char *&text) {
    while (const auto c = *text++) {
        switch (c) {
            case ' ':
                continue;
            case '-':
                return Token::Minus;
            case '+':
                return Token::Plus;
            case '*':
                return Token::Mul;
            case '/':
                return Token::Div;
        }
        if (c >= '0' && c <= '9') {
            return Token::Number;
        }
        return Token::Invalid;
    }
    return Token::End;
}

//элемент грамматики
int prim(const char *&text) {
    //prim всегда начинается с токена
    Token token = get_token(text);
    int number = 0;

    switch (token) {
        case Token::Number:
            number = *(text-1) - '0';
            for (auto c = *text; c >= '0' && c <= '9';) {
                number = number * 10 + c - '0';
                c = *++text;
            }
            return number;
        case Token::Minus:
            return -prim(text);
        case Token::End:
            throw ("Error: prim expected");
        case Token::Invalid:
            throw ("Error: invalid prim");
        default:
            throw ("Wrong formatted input");
    }
}

//элемент грамматики
int term(const char *&text) {
    //term всегда начинается с prim
    int result = prim(text);
    int number;

    while (true) {
        Token token = get_token(text);
        switch (token) {
            case Token::Mul:
                result *= prim(text);
                break;
            case Token::Div:
                //проверка деления на 0
                number = prim(text);
                if (number != 0)
                    result /= number;
                else
                    throw ("Error: null division");
                break;
            case Token::Invalid:
                throw ("Error: invalid term");
            default:
                //отступаем назад, если вышли за конец term
                --text;
                return result;
        }
    }
}

//элемент грамматики
int expr(const char *&text) {
    //expr всегда начинается с term
    int result = term(text);

    while (true) {
        Token token = get_token(text);
        switch (token) {
            case Token::Plus:
                result += term(text);
                break;
            case Token::Minus:
                result -= term(text);
                break;
            case Token::Invalid:
                throw ("Error: invalid expr");
            default:
                return result;
        }
    }
}

int main(int argc, char *argv[]) {
    const char *text;

    //проверка числа аргументов
    if (argc < 2) {
        std::cout << "Error: input expression expected" << std::endl;
        return 1;
    } else {
        text = argv[1];
    }

    //разбор по грамматике начинается с всеобъемлеющего expr
    try {
        std::cout << expr(text) << std::endl;
    }
    catch (const char *str) {
        std::cout << str << std::endl;
        return 1;
    }
    return 0;
}