// Vasilii Bodnariuk

#include <math.h>
#include <iostream>
#include <string>

#include "calc.hpp"

using namespace std;

int digit(char c) {
    return int(c) - '0';
}

double Calc::calculate(char* data) {
    _data = data;

    return expression(0, true);
}

int Calc::skip_blanks(int start) {
    while(_data[start] == ' ') {
        ++start;
    }

    return start;
}

int Calc::number(int start, int len) {
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

    while(i < len) {
        switch (_data[i]) {
            case '*':
            case '/':
                {
                    binary_operator_test();
                    double tail = term(i + 1, len, _data[i] == '*');
                    if((_data[i] == '/') == last_mult) {
                        double result = number(start, i) / tail;
                        if(isinf(result)) {
                            throw ERR_ZERO_DIV;
                        }
                        return result;
                    }
                    else {
                        return number(start, i) * tail;
                    }
                }
        }
        ++i;
        i = skip_blanks(i);
        _binary_operator = false;
    }

    return number(start, len);
}

double Calc::expression(int start, bool last_plus) {
    _binary_operator = true;
    start = skip_blanks(start);
    int i = start;

    while(_data[i] != '\0') {
        switch (_data[i]) {
            case '-':
                if(_binary_operator) {
                    break;
                }
            case '+':
                {
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
            default:
                _binary_operator = false;
        }

        ++i;
        i = skip_blanks(i);
    }

    return term(start, i, true);
}

void Calc::binary_operator_test() {
    if(_binary_operator) {
        throw ERR_BAD_STRUCTURE;
    }
    _binary_operator = true;
}
