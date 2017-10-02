// Vasilii Bodnariuk

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int digit(char c) {
    if(c >= '0' && c <='9') {
        return int(c) - '0';
    } else {
        throw 1;
    }
}

int number(char* data, int start, int len) {
    bool negative = false;
    int accumulator = 0;
    for(int i = start; i < len; ++i) {
        switch (data[i]) {
            case '-':
                negative = !negative;
                break;
            default:
                accumulator = 10 * accumulator + digit(data[i]);
        }
    }
    if(negative) {
        accumulator = - accumulator;
    }
    return accumulator;
}

double term(char* data, int start, int len, bool last_mult) {
    for(int i = start; i < len; ++i) {
        switch (data[i]) {
            case '*':
            case '/':
                if (data[i + 1] == ' ') {
                    double tail = term(data, i + 2, len, data[i] == '*');
                    if((data[i] == '/') == last_mult) {
                        return number(data, start, i - 1) / tail;
                    }
                    else {
                        return number(data, start, i - 1) * tail;
                    }
                }
        }
    }
    return number(data, start, len);
}

double expression(char* data, int start, int len, bool last_plus) {
    for(int i = start; i < len; ++i) {
        switch (data[i]) {
            case '+':
            case '-':
                if (data[i + 1] == ' ') {
                    double tail = expression(data, i + 2, len, data[i] == '+');
                    if((data[i] == '-') == last_plus) {
                        tail = - tail;
                    }
                    return term(data, start, i - 1, true) + tail;
                }
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '/':
            case '*':
            case ' ':
                break;
            default:
                throw 1;
        }
    }
    return term(data, start, len, true);
}

int main(int argc, char* argv[])
{
    if(argc != 2) {
        cout << "usage:" << '\n';
        cout << argv[0] << " expression" << '\n';
        cout << "example:" << '\n';
        cout << argv[0] << " \"-12 * 2 / 3 + 8 * 2 / 1\"" << '\n';
    } else {
        auto data = argv[1];
        double e;
        try {
            e = expression(data, 0, strlen(data), true);
            cout << e << "\n";
        }
        catch (int code) {
            cout << "r u kidding me?" << "\n";
            return code;
        }
    }
    return 0;
}
