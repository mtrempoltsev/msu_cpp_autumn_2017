
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

//перечисление значений элементов (если можно было бы объекту типа Token присвоить rawValue, то можно
//хранить и тип и значение, а не создавать структуру symbol)
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
} curr_symbol;


double expr();
double term();
double prim();
symbol getToken();

char* text; // выражение считанное из командной строки



//обрабатывает сложение и вычитание, состоит из одного цикла, в котором распознанные термы складываются или вычитаются
double expr() {
    double left = term();
    while (1) {
        switch (curr_symbol.tok) {
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
double term() {
    double left = prim();
    double d;
    while(1) {
        switch (curr_symbol.tok) {
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
double prim() {
    switch (curr_symbol.tok) {
        case Token::Number:
            getToken();
            return curr_symbol.number_value;
        case Token::Minus: //унарный минус
            getToken();
            return -prim();
        case Token::End:
            return 1;
        default:
            cout << "Original needed" << endl;
            break;
    }
    return 1;
}

//функция получения очереного токена (операнда, операции или конца выражения)
symbol getToken() {
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
    
    getToken();
    cout << expr() << endl;
    
    return 0;
}
