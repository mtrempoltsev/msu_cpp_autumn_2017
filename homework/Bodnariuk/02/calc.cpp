// Vasilii Bodnariuk

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int digit(char c) {
    return int(c) - '0';
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

double term(char* data, int start, int len) {
    for(int i = start; i < len; ++i) {
        switch (data[i]) {
            case '*':
            case '/':
                if (data[i + 1] == ' ') {
                    double tail = term(data, i + 2, len);
                    if(data[i] == '/') {
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

double expression(char* data, int start, int len) {
    for(int i = start; i < len; ++i) {
        switch (data[i]) {
            case '+':
            case '-':
                if (data[i + 1] == ' ') {
                    double tail = expression(data, i + 2, len);
                    if(data[i] == '-') {
                        tail = - tail;
                    }
                    return term(data, start, i - 1) + tail;
                }
        }
    }
    return term(data, start, len);
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
        auto e = expression(data, 0, strlen(data));
        cout << e << "\n";
    }
    return 0;
}
