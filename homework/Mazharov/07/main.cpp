#include <iostream>
#include <unordered_map>
#include <limits>
#include <vector>
#include <cmath>

std::unordered_map<std::string, double> constants =
        {
                {"Pi", 3.14},
                {"e",  2.7}
        };

enum class Token {
    Invalid, Minus, Plus, Mul, Div,
    Number, LB, RB, e, Pi, End
};

//Класс Parser для анализа числа
template<class T>
struct Parser {

};

template<>
struct Parser<int> {
    int parse(const std::string &text) {
        long long int tmp = atoll(text.c_str());
        if (tmp < std::numeric_limits<int>::min() || tmp > std::numeric_limits<int>::max()) {
            throw ("Error: out of range");
        }
        return (int) tmp;
    }
};

template<>
struct Parser<long> {
    long parse(const std::string &text) {
        long long tmp = atoll(text.c_str());
        if (tmp < std::numeric_limits<long>::min() || tmp > std::numeric_limits<long>::max()) {
            throw ("Error: out of range");
        }
        return (long) tmp;
    }
};

template<>
struct Parser<double> {
    double parse(const std::string &text) {
        long double tmp = atof(text.c_str());
        if (tmp < std::numeric_limits<double>::min() || tmp > std::numeric_limits<double>::max()) {
            throw ("Error: out of range");
        }
        return (double) tmp;
    }
};

template<class T>
struct lexeme {
    Token name;
    T value;
};

template<class T, class Parser>
class Calculator {
public:
    explicit Calculator(const char *input_string);

    T expr();

    T term();

    T prim();

    void get_token();

private:
    lexeme<T> cur_lex;
    const char *expression;
    int in_brackets;
};

template<class T, class Parser>
Calculator<T, Parser>::Calculator(const char *input_string) {
    expression = input_string;
    in_brackets = 0;
};

template<class T, class Parser>
T Calculator<T, Parser>::expr() {
    //expr всегда начинается с term
    T result = term();

    while (true) {
        get_token();
        switch (this->cur_lex.name) {
            case Token::Plus:
                result += term();
                break;
            case Token::Minus:
                result -= term();
                break;
            case Token::Invalid:
                throw ("Error: invalid expr");
            default:
                return result;
        }
    }
};

template<class T, class Parser>
T Calculator<T, Parser>::term() {
    //term всегда начинается с prim
    T result = prim();
    T number;

    while (true) {
        get_token();
        switch (this->cur_lex.name) {
            case Token::Mul:
                result *= prim();
                break;
            case Token::Div:
                //проверка деления на 0
                number = prim();
                if (number != 0)
                    result /= number;
                else
                    throw ("Error: null division");
                break;
            case Token::Invalid:
                throw ("Error: invalid term");
            case Token::RB:
                if (!this->in_brackets)
                    throw ("Error: open bracket");
            default:
                //отступаем назад, если вышли за конец term
                --(this->expression);
                return result;
        }
    }
};

template<class T, class Parser>
T Calculator<T, Parser>::prim() {
    //prim всегда начинается с токена
    get_token();
    T tmp_expr;

    switch (this->cur_lex.name) {
        case Token::Number:
            return this->cur_lex.value;
        case Token::Minus:
            return -prim();
        case Token::e:
            return 2.7;
        case Token::Pi:
            return 3.14;
        case Token::LB:
            this->in_brackets++;
            tmp_expr = expr();
            if (this->cur_lex.name != Token::RB)
                throw ("Error: close brackets");
            this->in_brackets--;
            return tmp_expr;
        case Token::End:
            throw ("Error: prim expected");
        case Token::Invalid:
            throw ("Error: invalid prim");
        default:
            throw ("Wrong formatted input");
    }
};

template<class T, class Parser>
void Calculator<T, Parser>::get_token() {
    while (auto c = *(this->expression)++) {
        switch (c) {
            case ' ':
                continue;
            case '-':
                this->cur_lex.name = Token::Minus;
                return;
            case '+':
                this->cur_lex.name = Token::Plus;
                return;
            case '*':
                this->cur_lex.name = Token::Mul;
                return;
            case '/':
                this->cur_lex.name = Token::Div;
                return;
            case '(':
                this->cur_lex.name = Token::LB;
                return;
            case ')':
                this->cur_lex.name = Token::RB;
                return;
            default:

                if (c >= '0' && c <= '9') {
                    std::string tmp_str = "";
                    tmp_str += c;

                    //this->cur_lex.value = c - '0';
                    for (auto c = *(this->expression); c >= '0' && c <= '9';) {
                        //this->cur_lex.value = this->cur_lex.value * 10 + c - '0';
                        tmp_str += c;
                        c = *++(this->expression);
                    }

                    if (c == '.') {
                        for (auto c = *(this->expression); c >= '0' && c <= '9';) {
                            //this->cur_lex.value = this->cur_lex.value * 10 + c - '0';
                            tmp_str += c;
                            c = *++(this->expression);
                        }
                    }

                    //Проверяем число на соответствие диапазону
                    try {
                        this->cur_lex.value = Parser().parse(tmp_str);
                    }
                    catch (const char *str) {
                        throw;
                    }

                    this->cur_lex.name = Token::Number;
                    return;
                }

                if (isalpha(c)) {
                    std::string name = "";
                    name += c;
                    for (auto c = *(this->expression); isalpha(c);) {
                        name += c;
                        c = *++(this->expression);
                    }
                    if (constants[name]) {
                        this->cur_lex.name = Token::Number;
                        this->cur_lex.value = constants[name];
                        return;
                    }
                }
                this->cur_lex.name = Token::Invalid;
                return;
        }
    }
    this->cur_lex.name = Token::End;
};

/* Использованная грамматика:
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | - number | + number
    number = [0-9]
 */

void check(bool value) {
    if (!value)
        std::cout << "error" << std::endl;
}

void check_int() {
    std::string text1 = "(1 + 2 - (-3 * 4) / 5)";

    Calculator<int, Parser<int>> calc1 = Calculator<int, Parser<int>>(text1.c_str());
    check(calc1.expr() == 5);
};

void check_long() {
    std::string text1 = "(1 + 2 - (-3 * 4) / 5)";

    Calculator<long, Parser<long>> calc1 = Calculator<long, Parser<long>>(text1.c_str());
    check(calc1.expr() == 5);
};

void check_double() {
    std::string text1 = "(1 + 2 - (-3 * 4) / 5)";

    Calculator<double, Parser<double>> calc1 = Calculator<double, Parser<double>>(text1.c_str());
    check(calc1.expr() == 5.4);
};

int main(int argc, char *argv[]) {
    char *text;


    //проверка числа аргументов
    if (argc < 2) {
        std::cout << "Error: input expression expected" << std::endl;
        return 1;
    } else if ((std::string) argv[1] == "test") {
        try {
            check_int();
            check_long();
            check_double();
        }
        catch (const char *str) {
            std::cout << str << std::endl;
            return 1;
        }
        return 0;
    } else {
        text = argv[1];

        //разбор по грамматике начинается с всеобъемлеющего expr
        try {
            Calculator<int, Parser<int>> calc = Calculator<int, Parser<int>>(text);
            std::cout << calc.expr() << std::endl;
        }
        catch (const char *str) {
            std::cout << str << std::endl;
            return 1;
        }
    }

    return 0;
}