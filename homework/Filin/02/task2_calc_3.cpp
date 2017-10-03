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

using namespace std;

//перечисление значений элементов
enum Token {
    Invalid,
    Minus = '-',
    Plus = '+',
    Mul = '*',
    Div = '/',
    Number,
    End
};

//лексема состоит из двух частей: значения, определяющего вид лексемы tok, и (если необходимо)  значения лексемы - number_value.
struct symbol {
    Token tok;
    double number_value;
};


double expr(char*& text);
double term(char*& text, symbol& curr_symbol);
double prim(char*& text, symbol& curr_symbol);
symbol getToken(char*& text, symbol& curr_symbol);



//обрабатывает сложение и вычитание, состоит из одного цикла, в котором распознанные термы складываются или вычитаются
double expr(char*& text) {
    symbol curr_symbol;
    getToken(text, curr_symbol);
    double left = term(text, curr_symbol);
    while (1) {
        switch (curr_symbol.tok) {
            case Token::Plus:
                getToken(text, curr_symbol);
                left += term(text, curr_symbol);
                break;
            case Token::Minus:
                getToken(text, curr_symbol);
                left -= term(text, curr_symbol);
                break;
            default:
                return left;
        }
    }
    
}

//обрабатывает умножение и деление, состоит из одного цикла, в котором распознанные термы умножаются или делятся
double term(char*& text, symbol& curr_symbol) {
    double left = prim(text, curr_symbol);
    double d;
    while(1) {
        switch (curr_symbol.tok) {
            case Token::Mul:
                getToken(text, curr_symbol);
                
                left *= prim(text, curr_symbol);
                break;
            case Token::Div:
                getToken(text, curr_symbol);
                d = prim(text, curr_symbol);
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
double prim(char*& text, symbol& curr_symbol) {
    switch (curr_symbol.tok) {
        case Token::Number:
            getToken(text, curr_symbol);
            return curr_symbol.number_value;
        case Token::Minus: //унарный минус
            getToken(text, curr_symbol);
            return -prim(text,curr_symbol);
        case Token::End:
            return 1;
        default:
            cout << "Original needed" << endl;
            break;
    }
    return 1;
}

//функция получения очереного токена (операнда, операции или конца выражения)
symbol getToken(char*& text, symbol& curr_symbol) {
    while (const auto c = *text++) {
        switch (c) {
            case ' ': continue;
            case '-':
            case '+':
            case '*':
            case '/':
                curr_symbol.tok = Token(c);
                return curr_symbol;
        }
        if (c >= '0' && c <= '9') {
            string tmp = "";
            tmp += c;
            for (auto c = *text;  c >= '0' && c <= '9';) {
                ++text;
                c = *text;
                tmp += c;
                
            }
            curr_symbol.tok = Token::Number;
            curr_symbol.number_value = atoi(tmp.c_str());
            return curr_symbol;
            
        }
        curr_symbol.tok = Token::Invalid;
        return curr_symbol;
    }
    curr_symbol.tok = Token::End;
    return curr_symbol;
}


int main(int argc, char* argv[]) {
    
    char* text; // выражение считанное из командной строки

    
    //проверяем кол-во параметров командной строки
    switch(argc) {
        case 1:
            cerr << "Not enough paramenters" << endl;
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
    
    cout << expr(text) << endl;
    
    return 0;
}
