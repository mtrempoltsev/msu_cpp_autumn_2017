#include "calculator.h"
//определяем тип текущего токена
Token get_token(const char*& input) {
    while (auto c = *input++) {
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
        }

        if (c >= '0' && c <= '9') {
            return Token::Number;
        } else
            return Token::Invalid;
    }
    return Token::End;
}

//выделяем слагаемые
int parse_expression(const char*& input) {
    if (!(*input)) {
        cout << message << endl;
        std::cerr << "Invalid syntax\n";
        exit(1);
    }
    auto left = parse_term(input);
    auto token = get_token(input);
    switch (token) {
        case Token::Plus:
            return left + parse_expression(input);
        case Token::Minus:
            return left - parse_expression(input);
        case Token::Invalid:
            cout << message << endl;
            cerr << "Incorrect symbol\n";
            exit(1);
        default:
            return left;
    }
}

//выделяем множители
int parse_term(const char*& input) {

    if (!(*input)) {
        std::cerr << "Invalid syntax\n";
        exit(1);
    }

    auto left = parse_primary(input);
    auto token = get_token(input);

    while (token == Token::Mul || token == Token::Div) {
        
        int right = parse_primary(input);
        if (token == Token::Mul) {
            left *= right;
        }
        else {
            if (right == 0) {
                cout << message << endl;
                cerr << "Division by zero\n";
                exit(1);
            }
            left /= right;
        }

        token = get_token(input);
    }
    if (token == Token::Invalid) {
        cout << message << endl;
        cerr << "Incorrect symbol\n";
        exit(1);
    }
    --input; //дойдя до + или -, возвращаем токен обратно
    return left;
}


//выделяем целые числа
int parse_primary(const char*& input) {
    if (!(*input)) {
        std::cerr << "Invalid syntax\n";
        exit(1);
    }
    auto token = get_token(input);
    int n = 0;
    switch (token) {
        case Token::Number:
            --input; //возвращаемся к только что прочитанному началу числа
            for (auto c = *input; c >= '0' && c <= '9';) {
                n = n * 10 + c - '0';
                c = *++input;
            }
            return n;
        case Token::Minus:
            return -parse_primary(input); //унарный минус
        case Token::Invalid:
            cout << message << endl;
            cerr << "Incorrect symbol\n";
            exit(1);
        default:
            cout << message << endl;
            cerr << "Invalid syntax\n";
            exit(1);
    }
}



