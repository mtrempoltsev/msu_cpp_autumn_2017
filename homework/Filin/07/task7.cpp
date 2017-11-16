//
//  main.cpp
//  Task6
//
//  Created by Максим on 01.11.17.
//  Copyright © 2017 Максим. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <unordered_map>
#include <vector>

using namespace std;

void check(bool value);
void test_double();
void test_long();
void test_int();


///////////////////////// свойства для типов int, long, double ////////////////////////
template<class T>
struct NumericTraits{
    
};

template<>
struct NumericTraits<double>{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();
};

template<>
struct NumericTraits<int>{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
};

template<>
struct NumericTraits<long>{
    static constexpr long min = std::numeric_limits<long>::min();
    static constexpr long max = std::numeric_limits<long>::max();
};
///////////////////////// свойства для типов int, long, double ////////////////////////



///////////////////////////// Стратегия для Parser /////////////////////////////
template<class T>
struct Parser {
    
};

template<>
struct Parser<double>
{
    bool parse(const std::string& text, double& value)
    {
        string tmp_value = "";
        tmp_value += text[0];
        
        for (int i = 1; i < text.length(); i++) {
            double curr_value = atof(tmp_value.c_str());
            double max = NumericTraits<double>::max;
            if (curr_value > max / 10) {
                throw std::runtime_error("Out of double range");
            } else {
                tmp_value += text[i];
            }
        }
        value = atof(tmp_value.c_str());
        return true;
    }
};

template<>
struct Parser<long>
{
    bool parse(const std::string& text, long& value)
    {
        string tmp_value = "";
        tmp_value += text[0];
        
        for (int i = 1; i < text.length(); i++) {
            long curr_value = atol(tmp_value.c_str());
            long max = NumericTraits<long>::max;
            if (curr_value > max / 10) {
                throw std::runtime_error("Out of long range");
            } else {
                tmp_value += text[i];
            }
        }
        value = atol(tmp_value.c_str());
        return true;
    }
};

template<>
struct Parser<int>
{
    bool parse(const std::string& text, int& value) {
        
        string tmp_value = "";
        tmp_value += text[0];
        
        for (int i = 1; i < text.length(); i++) {
            double curr_value = atoi(tmp_value.c_str());
            double max = NumericTraits<int>::max;
            if (curr_value > max / 10) {
                throw std::runtime_error("Out of int range");
            } else {
                tmp_value += text[i];
            }
        }
        value = atoi(tmp_value.c_str());
        return true;
    }
};
///////////////////////////// Стратегия для Parser /////////////////////////////




unordered_map<string, double> constants =
{
    { "Pi", 3.14 },
    { "e", 2.7 }
};

//перечисление значений элементов
enum Token {
    Invalid,
    Minus = '-',
    Plus = '+',
    Mul = '*',
    Div = '/',
    LP = '(',
    RP = ')',
    Name,
    Number,
    End
};


//лексема состоит из двух частей: значения, определяющего вид лексемы tok, и (если необходимо)  значения лексемы - number_value.
template <class T>
struct symbol {
    Token tok;
    T number_value;
};


//шаблонный класс Calculator
template <class T, class Parser>
class Calculator {
    private:
    symbol<T> curr_symbol;
    int num_opened;
    const char* text;
    public:
    
    Calculator(const char*   expression) {
        text = expression;
        symbol<T> s;
        curr_symbol = s;
        num_opened = 0;
    }
    
    T expr();
    T term();
    T prim();
    void getToken();
};


//обрабатывает сложение и вычитание, состоит из одного цикла, в котором распознанные термы складываются или вычитаются
template <class T, class Parser>
T Calculator<T, Parser>:: expr() {
    getToken();
    T left = term();
    while (1) {
        switch (this->curr_symbol.tok) {
            case Token::Plus:
                getToken();
                left += term();
                break;
            case Token::Minus:
                getToken();
                left -= term();
                break;
            default:
                return left;
        }
    }
}

//обрабатывает умножение и деление, состоит из одного цикла, в котором распознанные термы умножаются или делятся
template <class T, class Parser>
T Calculator<T, Parser>::term() {
    T left = prim();
    T d;
    while(1) {
        switch (this->curr_symbol.tok) {
            case Token::Mul:
                getToken();
            
                left *= prim();
                break;
            case Token::Div:
                getToken();
                d = prim();
                if (d == 0) {
                    throw std::runtime_error("Zero division");
                }
                left /= d;
                break;
            case Token::RP:
                if (this->num_opened == 0) {
                    throw std::runtime_error("Wrong brackets sequence");
                }
                else {
                    return left;
                }
            default:
                return left;
        }
    }
}

//функция обрабатывает первичные элементы
template <class T, class Parser>
T Calculator<T, Parser>::prim() {
    T e;
    switch (this->curr_symbol.tok) {
        case Token::Number:
            getToken();
            return this->curr_symbol.number_value;
        case Token::Minus: //унарный минус
            getToken();
            return -Calculator::prim();
        
        case Token::LP:
            this->num_opened++;
            e = expr();
            if (this->curr_symbol.tok != RP) {
                throw std::runtime_error("Wrong brackets sequence");
            }
            this->num_opened--;
            getToken();
            return e;
        
            default:
                throw std::runtime_error("Original needed");
                break;
    }
    return 1;
}

//функция получения очереного токена (операнда, операции или конца выражения)
template <class T, class Parser>
void Calculator<T, Parser>:: getToken() {
    while (const auto c = *(this->text)++) {
        switch (c) {
            case ' ': continue;
            case '-':
            case '+':
            case '*':
            case '/':
            case '(':
            case ')':
            this->curr_symbol.tok = Token(c);
            return;
        }
        if (c >= '0' && c <= '9') {
            string tmp = "";
            tmp += c;
            
            while (isdigit(*text)) {
                tmp += *text;
                text++;
            }
            
            if (*text == '.') { //если считываем double
                tmp += '.';
                text++;
                while (isdigit(*text)) {
                    tmp += *text;
                    text++;
                }
            }
            
            T value;
            //проверим на то что число находится в допустимом диапазоне, заданном в свойствах типов
            Parser().parse(tmp, value);
            
            this->curr_symbol.number_value = value;
            this->curr_symbol.tok = Token::Number;
            return;
        }
        if (isalpha(c)) {
            string name = "";
            name += c;
            while (isalpha(*text)) {
                name += *text;
                text++;
            }
            if (constants[name]) {
                this->curr_symbol.tok = Token::Number;
                this->curr_symbol.number_value = constants[name];
                return;
            }
            
        }
        throw std::runtime_error("Invalid token");
        return;
    }
    this->curr_symbol.tok = Token::End;
    return;
}


int main(int argc, char* argv[]) {
    
    char* text; // выражение считанное из командной строки
    
    //проверяем кол-во параметров командной строки
    try {
        switch(argc) {
            case 1:
                throw std::runtime_error("Not enough parameters");
                break;
            case 2:
                if (strcmp(argv[1], "DEBUG") == 0) {
                    test_double();
                    test_long();
                    test_int();
                    cout << "All tests completed" << endl;
                } else {
                    text = argv[1];
                    Calculator<int, Parser<int> > calc =
                        Calculator<int, Parser<int> >(text);
                    cout << calc.expr() << endl;
                }
                break;
            default:
                throw std::runtime_error("To many parameters");
                break;
        }
    }
    catch (const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Unexpected Exception" << endl;
    }
    
    return 0;
}


/////////////////////////////////////// Тесты /////////////////////////////////////////

void check(bool value) {
    if (!value)
    std::cout << "error" << std::endl;
}

void test_double() {
    cout << "testing double" << endl;
    vector<const char*> texts = {"5.7 - 0.7 -- 10 / 2.5 - 20",
        "15 / 3.0 + (-2.1 * 10) / 7 --0.11",
        "(9.3 + 0.7) * 2 / 2.0 + 0.5"
    };
    vector<double> results = {-11.0, 2.11, 10.5};
    
    for (int i = 0; i < texts.size(); i++) {
        Calculator<double, Parser<double> > calc = Calculator<double, Parser<double> >(texts[i]);
        check(fabs(calc.expr() - results[i]) < __DBL_EPSILON__);
    }
    
}

void test_long() {
    cout << "testing long" << endl;
    vector<const char*> texts = {"9 - 2 + 6 / 3",
        "(8 - (2 * 10) + 100 / 5)",
        "-100 / (10 * 10) + 22"
    };
    vector<long> results = {9, 8, 21};
    
    for (int i = 0; i < texts.size(); i++) {
        Calculator<long, Parser<long> > calc = Calculator<long, Parser<long> >(texts[i]);
        check(calc.expr() == results[i]);
    }
    
}



void test_int() {
    cout << "testing int" << endl;
    vector<const char*> texts = {"(8 - 4) / (2 * -2)",
        "(((2 + 2)) * 2)",
        "(8 - 6) / 2 * -2 - 100"
    };
    vector<int> results = {-1, 8, -102};
    
    for (int i = 0; i < texts.size(); i++) {
        Calculator<int, Parser<int> > calc = Calculator<int, Parser<int> >(texts[i]);
        check(calc.expr() == results[i]);
    }
    
}













