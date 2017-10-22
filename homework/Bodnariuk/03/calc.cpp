// Vasilii Bodnariuk

#include <math.h>
#include <iostream>
#include <string>

#include "calc.hpp"

using namespace std;

std::unordered_map<std::string, double> constants =
   {
       { "Pi", 3.14 },
       { "e", 2.7 }
   };

int digit(char c) {
    return int(c) - '0';
}

double Calc::calculate(char* data) {
    _data = data;
    _expr_level = 0;
    _end_pointer = 0;

    auto result = expression(0, true);
    if(_data[_end_pointer] != '\0') {
        throw ERR_UNBALANCED_PAR;
    }
    return result;
}

int Calc::skip_blanks(int start) {
    while(_data[start] == ' ') {
        ++start;
    }

    return start;
}

double Calc::p_expr(int start, int len) {
    start = skip_blanks(start);
    while(_data[len - 1] == ' ' && len > 0) {
        --len;
    }
    if(_data[start] == '(' && _data[len - 1] == ')') {
        return expression(start + 1, true);
    } else {
        return number(start, len);
    }
}

double Calc::number(int start, int len) {
    int accumulator = 0;
    int i = skip_blanks(start);
    bool negative = _data[i] == '-';
    if (negative) {
        ++i;
        i = skip_blanks(i);
    }

    if(i == len) {
        throw ERR_BAD_STRUCTURE;
    }

    switch (_data[i]) {
        case 'e':
            return constants["e"];
        case 'P':
            if(_data[i + 1] == 'i') {
                return constants["Pi"];
            }
    }

    while(i < len && _data[i] != ' ')
    {
        if(_data[i] >= '0' && _data[i] <= '9') {
            accumulator = 10 * accumulator + digit(_data[i]);
            ++i;
        } else {
            throw ERR_BAD_STRUCTURE;
        }

    }

    if(_data[i] == ' ') {
        if (skip_blanks(i) < len) {
            throw ERR_BAD_STRUCTURE;
        }
    }

    return negative ? -accumulator : accumulator;
}

double Calc::term(int start, int len, bool last_mult) {
    _binary_operator = true;
    start = skip_blanks(start);
    int i = start;

    int p_level = 0;
    while(i < len) {
        switch (_data[i]) {
            case '(':
                ++p_level;
                break;
            case ')':
                --p_level;
                break;
            case '*':
            case '/':
                if(p_level == 0){
                    binary_operator_test();
                    double tail = term(i + 1, len, _data[i] == '*');
                    if((_data[i] == '/') == last_mult) {
                        double result = p_expr(start, i) / tail;
                        if(isinf(result)) {
                            throw ERR_ZERO_DIV;
                        }
                        return result;
                    }
                    else {
                        return p_expr(start, i) * tail;
                    }
                }
        }
        ++i;
        i = skip_blanks(i);
        _binary_operator = false;
    }

    return p_expr(start, len);
}

double Calc::expression(int start, bool last_plus) {
    _binary_operator = true;
    start = skip_blanks(start);
    int i = start;
    int p_level = 0;
    bool looping;
    bool close_par = false;

    do {
        switch (_data[i]) {
            case '-':
                if(_binary_operator) {
                    break;
                }
            case '+':
                if(p_level == 0){
                    binary_operator_test();
                    double tail = expression(i + 1, _data[i] == '+');
                    if((_data[i] == '-') == last_plus) {
                        tail = - tail;
                    }
                    auto result = term(start, i, true) + tail;
                    return result;
                }
            case '*':
            case '/':
                binary_operator_test();
                break;
            case '(':
                if(close_par) {
                    throw ERR_BAD_STRUCTURE;
                }
                ++p_level;
                break;
            case ')':
                --p_level;
                break;
            default:
                _binary_operator = false;
        }

        looping = (_data[i] != '\0') && !(_data[i] == ')' && p_level == -1);
        if(looping) {
            close_par = _data[i] == ')';
            ++i;
            i = skip_blanks(i);
        }
    } while(looping);


    if(_data[i] == '\0' && p_level != 0) {
        throw ERR_UNBALANCED_PAR;
    }

    if(i > _end_pointer) {
        _end_pointer = i;
    }

    return term(start, i, true);
}

void Calc::binary_operator_test() {
    if(_binary_operator) {
        throw ERR_BAD_STRUCTURE;
    }
    _binary_operator = true;
}
