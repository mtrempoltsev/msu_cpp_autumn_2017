//
//  main.cpp
//  Task3
//
//  Created by Максим on 09.10.17.
//  Copyright © 2017 Максим. All rights reserved.
//
//
//  task2_calc.cpp
//  TS
//
//  Created by Максим on 30.09.17.
//  Copyright © 2017 Максим. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;


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
struct symbol {
    Token tok;
    double number_value;
};


class Calculator {
private:
    symbol curr_symbol;
    char* text;
public:

    Calculator(char*& expression) {
        text = expression;
        symbol s;
        curr_symbol = s;
    }
    
    double expr();
    double term();
    double prim();
    void getToken();
};







//обрабатывает сложение и вычитание, состоит из одного цикла, в котором распознанные термы складываются или вычитаются
double Calculator:: expr() {
    getToken();
    double left = term();
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
double Calculator::term() {
    double left = prim();
    double d;
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
                    cerr << "zero division" << endl;
                    exit(1);
                }
                left /= d;
                break;
            default:
                return left;
        }
    }
}

//функция обрабатывает первичные элементы
double Calculator::prim() {
    double e;
    switch (this->curr_symbol.tok) {
        case Token::Number:
            getToken();
            return this->curr_symbol.number_value;
        case Token::Minus: //унарный минус
            getToken();
            return -Calculator::prim();
            
        case Token::LP:
            e = expr();
            if (this->curr_symbol.tok != RP) {
                cerr << ") needed" << endl;
                exit(1);
            }
            getToken();
            return e;
        
        default:
            cout << "Original needed" << endl;
            exit(1);
            break;
    }
    return 1;
}

//функция получения очереного токена (операнда, операции или конца выражения)
void Calculator:: getToken() {
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
            this->curr_symbol.tok = Token::Number;
            this->curr_symbol.number_value = atoi(tmp.c_str());
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
        cerr << "Invalid token" << endl;
        exit(1);
        return;
    }
    this->curr_symbol.tok = Token::End;
    return;
}


int main(int argc, char* argv[]) {
    
    char* text; // выражение считанное из командной строки
    
    
    //проверяем кол-во параметров командной строки
    switch(argc) {
        case 1:
            cerr << "Not enough parameters" << endl;
            exit(1);
            break;
        case 2:
            text = argv[1];

            break;
        default:
            cerr << "To many parameters" << endl;
            exit(1);
            break;
    }
    
    Calculator calc = Calculator(text);

    cout << calc.expr() << endl;
    
    return 0;
}


