#include <iostream>
#include <ctype.h>

using namespace std;
typedef string::iterator string_it;

enum {
    Digit,
    Operation,
    Minus,
    Space,
    Begin
};


void skip_spaces(string_it& curr) {
    while (isspace(*curr)) {
            curr++;
    }
}

void skip_digit(string_it& curr) {
    while(isdigit(*curr)) {
        curr++;
    }
    curr--;
}

bool is_correct_op(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
    }
    return false;
}

int get_number(string_it& curr, string_it end) {
    skip_spaces(curr);

    int number = 0;
    int sign = 1;

    //get sign
    if (*curr == '-') {
        sign = -1;
        curr++;
    }

    skip_spaces(curr);

    //get number
    for ( ; curr < end && isdigit(*curr); curr++) {
        number *= 10;
        number += *curr - '0';
    }
    return number * sign;
}

int get_term(int left, string_it& curr, string_it end) {
    skip_spaces(curr);
    char op = *curr;

    if ((op != '*' && op != '/' ) || curr == end) {
        return left;
    }

    //get next number
    int next = get_number(++curr, end);

    //get current term
    if (op == '*') {
        return get_term(left * next, curr, end);
    } else {
        if (!next) {
            throw "Error: Division by zero";
        }
        return get_term(left / next, curr, end);
    }

}

int get_expr(int left, string_it& curr, string_it end) {
    skip_spaces(curr);
    char op = *curr;

    if ((op != '+' && op!= '-' ) || curr == end) {
        return left;
    }

    //get next term
    int numb = get_number(++curr, end);
    int next = get_term(numb, curr, end);

    //get current expr
    if (op == '+') {
        return get_expr(left + next, curr, end);
    } else {
        return get_expr(left - next, curr, end);
    }

}

void check_input(string_it begin, string_it end) {
    int state = Begin;
    int minus_count = 0;

    while (begin < end) {
        skip_spaces (begin);
        if (begin == end) {
            break;
        }
        char symbol = *begin;
        if (!isdigit(symbol) && !is_correct_op(symbol) && !isspace(symbol)) {
            cout << symbol;
            throw "Error: Invalid input";
        }
        switch (state) {
            case Begin:
                if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                    } else {
                        throw "Error: Invalid input";
                    }
                } else if (isdigit(symbol)) {
                    state = Digit;
                    minus_count = 0;
                    skip_digit(begin);
                } else {
                    throw "Error: Invalid input";
                }
                break;
            case Minus:
                if (isdigit(symbol)) {
                    state = Digit;
                    minus_count = 0;
                } else if (symbol == '-') {
                    minus_count++;
                } else {
                    throw "Error: Invalid input";
                }
                break;

            case Operation:
                if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                        break;
                    } else {
                        throw "Error: Invalid input";
                    }

                 }
                 if (isdigit(symbol)) {
                     state = Digit;
                     minus_count = 0;
                     skip_digit(begin);
                 } else {
                     throw "Error: Invalid input";
                 }
                 break;

            case Digit:
                if (isdigit(symbol)) {
                    throw "Error: Invalid input";
                }
                if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                    } else {
                        state = Operation;
                        minus_count = 0;
                    }
                }
        }

        if (minus_count > 2) {
            throw "Error: Invalid input";
        }
        begin++;
    }
    if (state != Digit) {
        throw "Error: Invalid input";
    }
}

int calculate(string input) {
    string_it curr = input.begin();
    check_input(curr, input.end());

    //get first term
    int numb = get_number(curr, input.end());
    int term = get_term(numb, curr, input.end());

    return get_expr(term, curr, input.end());
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "Please enter expression!" << endl;
        cout << "Example: " << argv[0] << ' ';
        cout << "\"2 + 3 * 4 - -2\"" << endl;
    } else {
        try {
            cout << calculate(string(argv[1])) << endl;
        } catch (const char* err) {
            cout << err << endl;
            return 1;
        }
    }

    return 0;
}
