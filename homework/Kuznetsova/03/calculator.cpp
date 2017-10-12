#include "calculator.h"
//определяем тип текущего токена
Token Tokenizer::get_token() {
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
                brackets_balance_ += 2;  //при разборе мы дважды обращаемся к
                //правым скобкам, поэтому левые
                //учитываем с двойным весом
                // cout<<brackets_balance_<<c<<endl;
                return Token::LBracket;
            case ')':

                brackets_balance_--;
                // cout<<brackets_balance_<<c<<endl;
                return Token::RBracket;
        }

        if (c >= '0' && c <= '9') {
            return Token::Number;
        } else if (isalpha(c)) {
            return Token::Const;  //корректность константы проверяется отдельно

        } else
            return Token::Invalid;
    }

    return Token::End;
}

void Tokenizer::token_back() { --input_; }

int Tokenizer::read_number() {
    int n = 0;
    for (auto c = *input_; c >= '0' && c <= '9';) {
        n = n * 10 + c - '0';
        c = *++input_;
    }
    return n;
}

int Tokenizer::read_constant() {
    int n = 0;
    string name;
    for (auto c = *input_; isalpha(c);) {
        name += c;
        c = *++input_;
    }
    auto map_iterator = constants_.find(name);
    if (map_iterator != constants_.end()) {
        n = constants_.at(name);

    } else {
        cout << message << endl;
        cerr << "Invalid syntax\n";
        exit(1);
    }
    return n;
}

void Tokenizer::check_pointer() {
    if (!(*input_)) {
        cout << message << endl;
        std::cerr << "Invalid syntax\n";
        exit(1);
    }
}
void Tokenizer::check_balance() {
    if (brackets_balance_ != 0) {
        cout << message << endl;
        cerr << "Imbalanced brackets\n";
        exit(1);
    }
}

int Parser::calculate() {
    int value = parse_expression();
    tokenizer_.check_balance();
    if (reached_end_ == 0) {
        cout << message << endl;
        cerr << "Extra characters\n";
        exit(1);
    }
    return value;
}

//выделяем целые числа
int Parser::parse_primary() {
    tokenizer_.check_pointer();
    auto token = tokenizer_.get_token();
    int n = 0;
    switch (token) {
        case Token::Number:
            tokenizer_.token_back();  //возвращаемся к только что
            //прочитанному началу числа
            n = tokenizer_.read_number();
            return n;
        case Token::Const:
            tokenizer_.token_back();  //возвращаемся к только что
            //прочитанному началу числа
            n = tokenizer_.read_constant();
            return n;
        case Token::Minus:
            return -parse_primary();  //унарный минус
        case Token::LBracket:
            return parse_expression();
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

//выделяем множители
int Parser::parse_term() {
    tokenizer_.check_pointer();

    auto left = parse_primary();
    auto token = tokenizer_.get_token();

    while (token == Token::Mul || token == Token::Div) {
        int right = parse_primary();
        if (token == Token::Mul) {
            left *= right;
        } else {
            if (right == 0) {
                cout << message << endl;
                cerr << "Division by zero\n";
                exit(1);
            }
            left /= right;
        }

        token = tokenizer_.get_token();
    }
    if (token == Token::Invalid) {
        cout << message << endl;
        cerr << "Incorrect symbol\n";
        exit(1);
    }
    tokenizer_.token_back();  //дойдя до + или -, возвращаем токен обратно
    return left;
}
//выделяем слагаемые
int Parser::parse_expression() {
    tokenizer_.check_pointer();

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
            cout << message << endl;
            cerr << "Incorrect symbol\n";
            exit(1);
        case Token::End:
            reached_end_ = 1;
            return left;
        default:
            return left;
    }
}
