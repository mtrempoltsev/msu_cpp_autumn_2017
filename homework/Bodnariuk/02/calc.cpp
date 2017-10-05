// Vasilii Bodnariuk

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

int good_str(char* data) {
    int i = 0;
    bool binary_operator = false;
    while(data[i] != '\0') {
        switch (data[i]) {
            case '+':
            case '/':
            case '*':
                if(binary_operator) {
                    return 0;
                }
                binary_operator = true;
                break;
            case ' ':
                break;
            case '-':
                if(binary_operator) {
                    data[i] = '~';
                }
                else {
                    binary_operator = true;
                }
                break;
            default:
                if(data[i] < '0' || data[i] > '9') {
                    return 0;
                }
                binary_operator = false;
        }
        ++i;
    }
    return i;
}

int digit(char c) {
    return int(c) - '0';
}

int skip_blanks(char* data, int start) {
    while(data[start] == ' ') {
        ++start;
    }

    return start;
}

int number(char* data, int start, int len) {
    int accumulator = 0;
    int i = skip_blanks(data, start);

    bool negative = data[i] == '~';
    if (negative) {
        ++i;
    }
    i = skip_blanks(data, i);

    while(data[i] >= '0' && data[i] <= '9')
    {
        accumulator = 10 * accumulator + digit(data[i]);
        ++i;
    }

    return negative ? -accumulator : accumulator;
}

double term(char* data, int start, int len, bool last_mult) {
    start = skip_blanks(data, start);
    int i = start;

    while(i < len) {
        switch (data[i]) {
            case '*':
            case '/':
                if (true) {
                    double tail = term(data, i + 1, len, data[i] == '*');
                    if((data[i] == '/') == last_mult) {
                        return number(data, start, i) / tail;
                    }
                    else {
                        return number(data, start, i) * tail;
                    }
                }
        }
        ++i;
        i = skip_blanks(data, i);
    }

    return number(data, start, len);
}

double expression(char* data, int start, int len, bool last_plus) {
    start = skip_blanks(data, start);
    int i = start;

    while(i < len) {
        switch (data[i]) {
            case '-':
            case '+':
                {
                    double tail = expression(data, i + 1, len, data[i] == '+');
                    if((data[i] == '-') == last_plus) {
                        tail = - tail;
                    }
                    return term(data, start, i, true) + tail;
                }
        }

        ++i;
        i = skip_blanks(data, i);
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
        int len = good_str(data);
        if (len > 0) {
            e = expression(data, 0, len, true);
            cout << e << "\n";
        } else {
            cout << "The program processes an arithmetic expression of integers!" << "\n";
            return -1;
        }
    }

    return 0;
}
