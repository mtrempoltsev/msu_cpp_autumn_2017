#include <iostream>
#include <ctype.h>
#include <unordered_map>

using namespace std;
typedef string::iterator string_it;

enum {
    Digit,
    LBracket,
    RBracket,
    Operation,
    Minus,
    Space,
    Begin
};

class Calcuator {
public:
    Calcuator(string expr) ;
    string_it get_begin();
    string_it get_end();
    void skip_spaces();
    void skip_digit();
    bool is_correct_op(char c);
    bool is_correct_const(char c);
    int get_number(string_it begin, string_it end) ;
    int get_term(int left, string_it begin, string_it end);
    int get_expr(int left, string_it begin, string_it end);
    void check_input();
    int calculate(string_it begin, string_it end);
    string_it find_rbracket(string_it begin, string_it end);

private:
    bool checked;
    string expr;
    string_it expr_begin;
    string_it expr_end;
    string_it curr;
    unordered_map<string, double> constants;
};

Calcuator::Calcuator(string expr_) {
    expr = expr_;
    expr_begin = expr.begin();
    expr_end = expr.end();
    curr = expr_begin;
    constants = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
    checked = false;
}

string_it Calcuator::get_begin() {
    return expr_begin;
}

string_it Calcuator::get_end() {
    return expr_end;
}

void Calcuator::skip_spaces() {
    while (isspace(*curr)) {
            curr++;
    }
}

void Calcuator::skip_digit() {
    while(isdigit(*curr)) {
        curr++;
    }
    curr--;
}

bool Calcuator::is_correct_op(char c) {
    switch (c) {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
    }
    return false;
}

bool Calcuator::is_correct_const(char c) {
    switch (c) {
        case 'P':
        case 'e':
            return true;
    }
    return false;
}

int Calcuator::get_number(string_it begin, string_it end) {
    skip_spaces();
    int number = 0;
    int sign = 1;

    //get sign
    if (*curr == '-') {
        sign = -1;
        curr++;
    }

    // get expression
    if (*curr == '(') {
        int numb = calculate(++curr, find_rbracket(begin, end));
        curr++;
        return numb * sign;
    }

    skip_spaces();

    if (*curr == 'P') {
        curr++;
        curr++;
        return sign * int(constants.find("Pi")->second);
    }

    if (*curr == 'e') {
        curr++;
        return sign * int(constants.find("e")->second);
    }

    //get number
    for ( ; curr < expr_end && isdigit(*curr); curr++) {
        number *= 10;
        number += *curr - '0';
    }
    return number * sign;
}

string_it Calcuator::find_rbracket(string_it begin, string_it end) {
    for (end--; end > begin && *end != ')'; end--)
        ;
    return end;
}

int Calcuator::get_term(int left, string_it begin, string_it end) {
    skip_spaces();
    char op = *curr;

    if ((op != '*' && op != '/' ) || curr == end) {
        return left;
    }

    //get next number
    curr++;

    int next = get_number(begin, end);

    //get current term
    if (op == '*') {
        return get_term(left * next, begin, end);
    } else {
        if (!next) {
            throw "Error: Division by zero";
        }
        return get_term(left / next, begin, end);
    }

}

int Calcuator::get_expr(int left, string_it begin, string_it end) {
    skip_spaces();
    char op = *curr;

    if ((op != '+' && op!= '-' ) || curr == end) {
        return left;
    }

    //get next term
    int next;
    curr++;
    int numb = get_number(begin, end);
    next = get_term(numb, begin, end);


    //get current expr
    if (op == '+') {
        return get_expr(left + next, begin, end);
    } else {
        return get_expr(left - next, begin, end);
    }

}

void Calcuator::check_input() {
    int state = Begin;
    int minus_count = 0;
    int bracket_balance = 0;
    checked = true;

    while (curr < expr_end) {
        skip_spaces ();
        if (curr == expr_end) {
            break;
        }
        char symbol = *curr;
        if (!isdigit(symbol) && !is_correct_op(symbol) && !isspace(symbol) &&
                !is_correct_const(symbol) && symbol != '(' && symbol != ')') {
            throw "Error: Invalid input";
        }
        switch (state) {
            case Begin:
                if (is_correct_const(symbol)) {
                    if (symbol == 'P') {
                        curr++;
                        if (*curr != 'i') {
                            throw "Error: Invalid input";
                        }
                    }
                    state = Digit;
                    minus_count = 0;
                } else if (symbol == '(') {
                    bracket_balance++;
                    state = LBracket;
                    minus_count = 0;
                } else if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                    } else {
                        throw "Error: Invalid input";
                    }
                } else if (isdigit(symbol)) {
                    state = Digit;
                    minus_count = 0;
                    skip_digit();
                } else {
                    throw "Error: Invalid input";
                }
                break;
            case Minus:
                if (is_correct_const(symbol)) {
                    if (symbol == 'P') {
                        curr++;
                        if (*curr != 'i') {
                            throw "Error: Invalid input";
                        }
                    }
                    state = Digit;
                    minus_count = 0;
                } else if (symbol == '(') {
                    bracket_balance++;
                    state = LBracket;
                    minus_count = 0;
                } else if (isdigit(symbol)) {
                    state = Digit;
                    skip_digit();
                    minus_count = 0;
                } else if (symbol == '-') {
                    state = Minus;
                    minus_count++;
                } else {
                    throw "Error: Invalid input";
                }
                break;

            case Operation:
                if (is_correct_const(symbol)) {
                    if (symbol == 'P') {
                        curr++;
                        if (*curr != 'i') {
                            throw "Error: Invalid input";
                        }
                    }
                    state = Digit;
                    minus_count = 0;
                } else if (symbol == '(') {
                    bracket_balance++;
                    state = LBracket;
                    minus_count = 0;
                } else if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                        break;
                    } else {
                        throw "Error: Invalid input";
                    }

                } else if (isdigit(symbol)) {
                     state = Digit;
                     minus_count = 0;
                     skip_digit();
                 } else {
                     throw "Error: Invalid input";
                 }
                 break;

            case Digit:
                if (symbol == ')') {
                    bracket_balance--;
                    state = RBracket;
                    minus_count = 0;
                } else if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                    } else {
                        state = Operation;
                        minus_count = 0;
                    }
                } else {
                    throw  "Error: Invalid Input";
                }
                break;
            case LBracket:
                if (symbol == '(') {
                    bracket_balance++;
                    state = LBracket;
                    minus_count = 0;
                } else if (is_correct_const(symbol)) {
                    if (symbol == 'P') {
                        curr++;
                        if (*curr != 'i') {
                            throw "Error: Invalid input";
                        }
                    }
                    state = Digit;
                    minus_count = 0;
                } else if (isdigit(symbol)) {
                    state = Digit;
                    skip_digit();
                    minus_count = 0;
                } else if (symbol == '-') {
                    state = Minus;
                    minus_count++;
                } else {
                    throw "Error: Invalid input";
                }
                break;

            case RBracket:
                if (symbol == ')') {
                    bracket_balance--;
                    state = RBracket;
                    minus_count = 0;
                } else if (is_correct_op(symbol)) {
                    if (symbol == '-') {
                        state = Minus;
                        minus_count++;
                    } else {
                        state = Operation;
                        minus_count = 0;
                    }
                } else {
                    throw "Error: Invalid Input";
                }
                break;
        }
        if (minus_count > 2) {
            throw "Error: Invalid input";
        }
        curr++;
    }
    if (state != Digit && state != RBracket) {
        throw "Error: Invalid input";
    }
    if (bracket_balance != 0) {
        throw "Error: Bad Bracket Balance";
    }
    curr = expr_begin;
}

int Calcuator::calculate(string_it begin, string_it end) {
    if (!checked) {
        check_input();
    }

    //get first term
    int term;
    int numb = get_number(begin, end);
    term = get_term(numb, begin, end);

    return get_expr(term, begin, end);
}

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "Please enter expression!" << endl;
        cout << "Example: " << argv[0] << ' ';
        cout << "\"(5 + 3 * (8 / Pi) * 4) + (1)\"" << endl;
    } else {
        try {
            Calcuator calc = Calcuator(string(argv[1]));
            cout << calc.calculate(calc.get_begin(), calc.get_end()) << endl;
        } catch (const char* err) {
            cout << err << endl;
            return 1;
        }
    }

    return 0;
}
