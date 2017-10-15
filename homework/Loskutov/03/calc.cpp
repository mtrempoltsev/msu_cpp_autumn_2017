#include <iostream>
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

class Calculator {
public:
    //Конструктор класса без полей
    Calculator();
    
    //Конструктор класса, принимающий выражение, которое надо посчитать
    Calculator(const char* text_);
    
    //Деструктор класса
    ~Calculator();
    
    //Функция реализует часть грамматики:
    //expr = term
    //    | expr + term
    //    | expr - term
    void expr();
    
    //Функция возвращает результат подсчета
    int getResult();
    
private:
    //Функция получения следующего токена
    void getToken();
    
    //Функция реализует часть грамматики:
    //prim = number
    //    | -number
    //number = [0-9]+
    double prim();
    
    //Функция реализует часть грамматики:
    //bkts = ( expr)
    //    | number
    double bkts();
    
    //Функция реализует часть грамматики:
    //term = bkts
    //    | term * bkts
    //    | term / bkts
    void term();
    
    //Поля класса
    Token *token; //Токен, который сейчас обрабатывается
    char* text; //Поле, в котором хранится выражение
    double res; //Поле, в котором хранится результат
    int pos; //Поле, в котором хранится место обрабатываемого символа в строке text
};

Calculator::Calculator() {
    token = (Token*)malloc(sizeof(Token*));
    *token = Token::Null;
    text = nullptr;
    res = 0.;
    pos = 0;
}

Calculator::Calculator(const char* text_) {
    token = (Token*)malloc(sizeof(Token*));
    *token = Token::Null;
    text = (char*)malloc((strlen(text_)+1)*sizeof(char));
    int count = 0;
    for (int i = 0; i < strlen(text_); i++) {
        text[i] = text_[i];
        if (text[i] == '(') {
            count++;
        }
        if (text[i] == ')') {
            count--;
        }
    }
    text[strlen(text_)] = '\0';
    if (count != 0) {
        throw invalid_argument("Bad expression!");
    }
    res = 0.;
    pos = 0;
}

Calculator::~Calculator() {
    free(text);
}

void Calculator::expr() {
    term();
    if (*token == Token::Null) {
        getToken();
    }
    if (*token == Token::Plus) {
        *token = Token::Null;
        double num = res;
        expr();
        res += num;
    } else if (*token == Token::Minus) {
        *token = Token::Null;
        double num = res;
        expr();
        num -= res;
        res = num;
    }
}

int Calculator::getResult() {
    return floor(res);
}

void Calculator::getToken() {
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
        if ((c >= '0') && (c <= '9')) {
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

double Calculator::prim() {
    if (*token == Token::End) {
        throw invalid_argument("Bad expression!");
    }
    if (*token == Token::Minus) {
        getToken();
        if (*token == Token::Pi) {
            *token = Token::Null;
            return -3.14;
        }
        if (*token == Token::e) {
            *token = Token::Null;
            return -2.72;
        }
        if (*token != Token::Number) {
            throw invalid_argument("Bad expression!");
        }
        char *buf;
        buf = (char*)calloc(20, sizeof(char));
        int i = 0;
        for (; (text[pos] >= '0') && (text[pos] <= '9'); ++pos) {
            buf[i] = text[pos];
            i++;
        }
        buf[i] = '\0';
        double num = atof(buf);
        free(buf);
        *token = Token::Null;
        return -num;
    }
    if (*token == Token::Pi) {
        *token = Token::Null;
        return 3.14;
    }
    if (*token == Token::e) {
        *token = Token::Null;
        return 2.72;
    }
    if (*token != Token::Number) {
        throw invalid_argument("Bad expression!");;
    }
    char *buf;
    buf = (char*)calloc(20, sizeof(char));
    int i = 0;
    buf[0] = text[pos];
    for (; (text[pos] >= '0') && (text[pos] <= '9'); ++pos) {
        buf[i] = text[pos];
        i++;
    }
    buf[i] = '\0';
    double num = atof(buf);
    free(buf);
    *token = Token::Null;
    return num;
}

double Calculator::bkts() {
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

void Calculator::term() {
    double left = bkts();
    if (*token == Token::Null) {
        getToken();
    }
    while ((*token == Token::Mul) || (*token == Token::Div)) {
        if (*token == Token::Mul) {
            *token = Token::Null;
            double right = bkts();
            left *= right;
        } else if (*token == Token::Div) {
            *token = Token::Null;
            double right = bkts();
            if (fabs(right) < 1e-20) {
                throw invalid_argument("Bad expression!");
            }
            left /= right;
        }
        getToken();
    }
    res = left;
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        cout << "No expression!" << endl;
        return 1;
    }
    if (argc > 2) {
        cout << "Too many arguments!" << endl;
        return 1;
    }
    const char* text = argv[1];
    int result = 0;
    try {
        Calculator calc(text);
        calc.expr();
        result = calc.getResult();
    } catch(invalid_argument& e) {
        cout << e.what() << endl;
        return 1;
    }
    cout << result << endl;
    return 0;
}
