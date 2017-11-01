#include <iostream>
#include <limits>
#include <stdexcept>
#include <cmath>

using namespace std;

//Класс enum, который описывает возможные токены,
//которые мы можем встретить когда будем идти по выражению
enum class Token {
    Minus,    //Знак минус
    Plus,     //Знак плюс
    Mul,      //Знак умножение
    Div,      //Знак деления
    Number,   //Число
    End,      //Конец выражения
    Null,     //Пустой токен
    BktLeft,  //Левая скобка
    BktRight, //Правая скобка
    Pi,       //Число Pi
    e         //Число e
};

template<class T>
class NumericTraits{
};

template<>
class NumericTraits<double> {
public:
    const double min = numeric_limits<double>::min();
    const double max = numeric_limits<double>::max();
};

template<>
class NumericTraits<int> {
public:
    static constexpr int min = numeric_limits<int>::min();
    static constexpr int max = numeric_limits<int>::max();
};

template <>
class NumericTraits<long> {
public:
    static constexpr long min = numeric_limits<long>::min();
    static constexpr long max = numeric_limits<long>::max();
};

template <class T>
class Parser {
};

template<>
class Parser<double> {
public:
    bool parse(const char* text, double& value) {
        long double tmp = strtold(text, nullptr);
        if (tmp < NumericTraits<int>::min) {
            return false;
        } else if (tmp > NumericTraits<int>::max) {
            return false;
        }
        value = (double)tmp;
        return true;
    }
};

template<>
class Parser<long> {
public:
    bool parse(const char* text, long& value) {
        long tmp = atoll(text);
        if (tmp < NumericTraits<long>::min) {
            return false;
        } else if (tmp > NumericTraits<long>::max) {
            return false;
        }
        value = (long)tmp;
        return true;
    }
};

template<>
class Parser<int> {
public:
    bool parse(const char* text, int& value) {
        long tmp = atol(text);
        if (tmp < NumericTraits<int>::min) {
            return false;
        } else if (tmp > NumericTraits<int>::max) {
            return false;
        }
        value = (int)tmp;
        return true;
    }
};

template <class T, class Device>
class Calculator {
public:
    //Конструктор класса без полей
    Calculator() {
        token = (Token*)malloc(sizeof(Token*));
        *token = Token::Null;
        text = nullptr;
        res = 0.;
        pos = 0;
    }
    
    //Конструктор класса, принимающий выражение, которое надо посчитать
    Calculator(const char* text_) {
        token = (Token*)malloc(sizeof(Token*));
        *token = Token::Null;
        size_t len = strlen(text_);
        text = (char*)malloc((len+1)*sizeof(char));
        int count = 0;
        for (int i = 0; i < len; i++) {
            text[i] = text_[i];
            if (text[i] == '(') {
                count++;
            }
            if (text[i] == ')') {
                if (count > 0) {
                    count--;
                } else {
                    throw invalid_argument("Bad expression!");
                }
            }
        }
        text[strlen(text_)] = '\0';
        if (count != 0) {
            throw invalid_argument("Bad expression!");
        }
        res = 0.;
        pos = 0;
    }
    
    //Деструктор класса
    ~Calculator() {
        free(text);
    }
    
    //Функция возвращает результат подсчета
    T getResult() {
        expr();
        return res;
    }
    
private:
    //Функция получения следующего токена
    void getToken() {
        while (const auto c = text[pos]) {
            switch (c) {
                case ' ':
                    pos++;
                    continue;
                case '-':
                    pos++;
                    *token = Token::Minus;
                    return;
                case '+':
                    pos++;
                    *token = Token::Plus;
                    return;
                case '*':
                    pos++;
                    *token = Token::Mul;
                    return;
                case '/':
                    pos++;
                    *token = Token::Div;
                    return;
                case '(':
                    pos++;
                    *token = Token::BktLeft;
                    return;
                case ')':
                    pos++;
                    *token = Token::BktRight;
                    return;
            }
            if (((c >= '0') && (c <= '9')) || (c == '.')) {
                *token = Token::Number;
                return;
            }
            if (c == 'P') {
                pos++;
                if (text[pos] == 'i') {
                    pos++;
                    *token = Token::Pi;
                    return;
                }
            }
            if (c == 'e') {
                pos++;
                *token = Token::e;
                return;
            }
            throw invalid_argument("Bad expression!");
        }
        *token = Token::End;
    }
    
    //Функция реализует часть грамматики:
    //prim = number
    //    | -number
    //number = [0-9]+
    double prim() {
        if (*token == Token::End) {
            throw invalid_argument("Bad expression!");
        }
        if (*token == Token::Minus) {
            getToken();
            if (*token == Token::Pi) {
                *token = Token::Null;
                T num;
                if (!parser_.parse("3.14159", num)) {
                    throw invalid_argument("Bad expression!");
                }
                return -num;
            }
            if (*token == Token::e) {
                *token = Token::Null;
                T num;
                if (!parser_.parse("2.71828", num)) {
                    throw invalid_argument("Bad expression!");
                }
                return -num;
            }
            if (*token != Token::Number) {
                throw invalid_argument("Bad expression!");
            }
            char *buf;
            buf = (char*)calloc(20, sizeof(char));
            int i = 0;
            for (; ((text[pos] >= '0') && (text[pos] <= '9')) || (text[pos] == '.'); ++pos) {
                buf[i] = text[pos];
                i++;
            }
            buf[i] = '\0';
            T num;
            if (!parser_.parse(buf, num)) {
                free(buf);
                throw invalid_argument("Bad expression!");
            }
            free(buf);
            *token = Token::Null;
            return -num;
        }
        if (*token == Token::Pi) {
            *token = Token::Null;
            T num;
            if (!parser_.parse("3.14159", num)) {
                throw invalid_argument("Bad expression!");
            }
            return num;
        }
        if (*token == Token::e) {
            *token = Token::Null;
            T num;
            if (!parser_.parse("2.71828", num)) {
                throw invalid_argument("Bad expression!");
            }
            return num;
        }
        if (*token != Token::Number) {
            throw invalid_argument("Bad expression!");;
        }
        char *buf;
        buf = (char*)calloc(20, sizeof(char));
        int i = 0;
        buf[0] = text[pos];
        for (; ((text[pos] >= '0') && (text[pos] <= '9')) || (text[pos] == '.'); ++pos) {
            buf[i] = text[pos];
            i++;
        }
        buf[i] = '\0';
        T num;
        if (!parser_.parse(buf, num)) {
            free(buf);
            throw invalid_argument("Bad expression!");
        }
        free(buf);
        *token = Token::Null;
        return num;
    }
    
    //Функция реализует часть грамматики:
    //bkts = ( expr)
    //    | number
    double bkts() {
        getToken();
        if (*token == Token::BktLeft) {
            getToken();
            if (*token == Token::BktRight) {
                throw invalid_argument("Bad expression!");
            }
            expr();
        } else if (*token == Token::BktRight) {
            *token = Token::Null;
        } else {
            return prim();
        }
        *token = Token::Null;
        return res;
    }
    
    //Функция реализует часть грамматики:
    //term = bkts
    //    | term * bkts
    //    | term / bkts
    void term() {
        double left = bkts();
        if (*token == Token::Null) {
            getToken();
        }
        while ((*token == Token::Mul) || (*token == Token::Div)) {
            if (*token == Token::Mul) {
                *token = Token::Null;
                T right = bkts();
                left *= right;
            } else if (*token == Token::Div) {
                *token = Token::Null;
                T right = bkts();
                if (abs(right) < 1e-20) {
                    throw invalid_argument("Bad expression!");
                }
                left /= right;
            }
            getToken();
        }
        res = left;
    }
    
    //Функция реализует часть грамматики:
    //expr = term
    //    | expr + term
    //    | expr - term
    void expr() {
        term();
        if (*token == Token::Null) {
            getToken();
        }
        if (*token == Token::Plus) {
            *token = Token::Null;
            T num = res;
            expr();
            res += num;
        } else if (*token == Token::Minus) {
            *token = Token::Null;
            T num = res;
            expr();
            num -= res;
            res = num;
        }
    }
    
    //Поля класса
    Token *token; //Токен, который сейчас обрабатывается
    char* text; //Поле, в котором хранится выражение
    T res; //Поле, в котором хранится результат
    int pos; //Поле, в котором хранится место обрабатываемого символа в строке text
    Device parser_; //Поле, в котором хранится парсер числа
};

template <class T>
void check(T value, T check_value) {
    if (abs(value - check_value) > 1e-10)
        cout << "error" << endl;
    //cout << value << " " << check_value << " " << abs(value - check_value) << endl;
}

template <class T, class U>
void check(const char* text, T value, bool correct) {
    try {
        Calculator<T, Parser<U>> calc(text);
        check(calc.getResult(), value);
        if (!correct) {
            cout << "error" << endl;
        }
    } catch(invalid_argument) {
        if (correct) {
            cout << "error" << endl;
        }
    }
}

void check() {
    check<int, int>("(1+ - 1)", 0, true);
    check<int, int>("8 - 6 * 2 / 2", 2, true);
    check<int, int>("8 - 6 / 2 * 2", 2, true);
    check<int, int>("8 - 6 / 2 * -2", 14, true);
    check<int, int>("2 + 3 * 4 - -2", 16, true);
    check<int, int>("(5 + 3 * (9 / Pi) * 4) + (1)", 42, true);
    check<int, int>("(5 + 3 * (9 / Pi) * 4) + (1 * e)", 43, true);
    
    check<long, long>("(1+ - 1)", 0, true);
    check<long, long>("8 - 6 * 2 / 2", 2, true);
    check<long, long>("8 - 6 / 2 * 2", 2, true);
    check<long, long>("8 - 6 / 2 * -2", 14, true);
    check<long, long>("2 + 3 * 4 - -2", 16, true);
    check<long, long>("(5 + 3 * (9 / Pi) * 4) + (1)", 42, true);
    check<long, long>("(5 + 3 * (9 / Pi) * 4) + (1 * e)", 43, true);
    
    check<double, double>("Pi+e", 5.85987, true);
    check<double, double>("(1.3+ - 1.2)", 0.1, true);
    check<double, double>("8.1 - 6 * 2 / 2", 2.1, true);
    check<double, double>("8.7 - 6.2 / 2 * 2", 2.5, true);
    check<double, double>("8 - 6 / 2 * -2.5", 15.5, true);
    check<double, double>("2.12344 + 3 * 4 - -2.444", 16.56744, true);
    
    check<int, int>("2 -+ 2", 0, false);
    check<int, int>("2 ++ 2", 0, false);
    check<long, long>("2 c 2", 0, false);
    check<long, long>(")1+ - 1(", 0, false);
    check<double, double>("()", 0, false);
    check<double, double>("(2 + 2))", 4., false);
}

int main(int argc, const char * argv[]) {
    if (argc == 2) {
        Calculator<double, Parser<double>> calc(argv[1]);
        try {
            cout << calc.getResult() << endl;
        } catch(invalid_argument& e) {
            cout << e.what() << endl;
        }
    }
    if (argc > 2) {
        cout << "Too many arguments!" << endl;
        return 1;
    }
    check();
    return 0;
}

