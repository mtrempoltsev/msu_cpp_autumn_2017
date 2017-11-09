# pragma once

typedef std::string::iterator string_it;

enum {
    Digit,
    LBracket,
    RBracket,
    Operation,
    Minus,
    Space,
    Begin
};

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

bool is_correct_const(char c) {
    switch (c) {
        case 'P':
        case 'e':
            return true;
    }
    return false;
}

template <typename T>
void check_symbols(string_it expr_begin, string_it expr_end) {
    for (string_it curr = expr_begin; curr < expr_end; curr++) {
        char symbol = *curr;
        if (is_correct_const(symbol)) {
            if (symbol == 'P') {
                curr++;
                if (*curr != 'i') {
                    throw std::invalid_argument("Error: Invalid constant");
                }
            }
        } else if (!isdigit(symbol) && !is_correct_op(symbol) && !isspace(symbol) &&
                 symbol != '(' && symbol != ')') {
            throw std::invalid_argument("Error: Bad symbol");
        }
    }
}

template<>
void check_symbols<double>(string_it expr_begin, string_it expr_end) {
    for (string_it curr = expr_begin; curr < expr_end; curr++) {
        char symbol = *curr;
        if (is_correct_const(symbol)) {
            if (symbol == 'P') {
                curr++;
                if (*curr != 'i') {
                    throw std::invalid_argument("Error: Invalid constant");
                }
            }
        } else if (isdigit(symbol)) {
            //skip numbers
            while (isdigit(*curr)) {
                curr++;
            }
            if (*curr == '.') {
                curr++;
                if (!isdigit(*curr)) {
                    throw std::invalid_argument("Error: Invalid input");
                }
                while (isdigit(*curr)) {
                    curr++;
                }
            }
            curr--;

        } else if (!is_correct_op(symbol) && !isspace(symbol) &&
                 symbol != '(' && symbol != ')') {
            throw std::invalid_argument("Error: Bad symbol");
        }
    }
}


template <typename T>
class Calcuator
{
public:
    Calcuator(std::string expr_) {
        expr = expr_;
        expr_begin = expr.begin();
        expr_end = expr.end();
        curr = expr_begin;
        checked = false;
    }

    void skip_spaces() {
        while (isspace(*curr)) {
                curr++;
        }
    }

    void skip_digit() {
        while(isdigit(*curr) || *curr == '.') {
            curr++;
        }
        curr--;
    }

    T get_number(string_it begin, string_it end) {
        skip_spaces();
        int sign = 1;

        //get sign
        if (*curr == '-') {
            sign = -1;
            curr++;
        }

        // get expression
        if (*curr == '(') {
            T numb = calculate(++curr, find_rbracket(begin, end));
            curr++;
            return numb * sign;
        }

        skip_spaces();

        T number = find_number<T>(curr, expr_begin, expr_end, sign);
        return number;

    }

    string_it find_rbracket(string_it begin, string_it end) {
        for (end--; end > begin && *end != ')'; end--)
            ;
        return end;
    }

    T get_term(T left, string_it begin, string_it end) {
        skip_spaces();
        char op = *curr;

        if ((op != '*' && op != '/' ) || curr == end) {
            return left;
        }

        //get next number
        curr++;

        T next = get_number(begin, end);

        //get current term
        if (op == '*') {
            return get_term(left * next, begin, end);
        } else {
            if (next == 0) {
                throw std::invalid_argument("Error: Division by zero");
            }
            return get_term(left / next, begin, end);
        }

    }

    T get_expr(T left, string_it begin, string_it end) {
        skip_spaces();
        char op = *curr;

        if ((op != '+' && op!= '-' ) || curr == end) {
            return left;
        }

        //get next term
        T next;
        curr++;
        T numb = get_number(begin, end);
        next = get_term(numb, begin, end);

        //get current expr
        if (op == '+') {
            return get_expr(left + next, begin, end);
        } else {
            return get_expr(left - next, begin, end);
        }

    }

    void check_input() {
        int state = Begin;
        int minus_count = 0;
        int bracket_balance = 0;
        checked = true;
        check_symbols<T>(expr_begin, expr_end);

        while (curr < expr_end) {
            skip_spaces ();
            if (curr == expr_end) {
                break;
            }
            char symbol = *curr;
            switch (state) {
                case Begin:
                    if (is_correct_const(symbol)) {
                        if (symbol == 'P') {
                            curr++;
                            if (*curr != 'i') {
                                throw std::invalid_argument("Error: Invalid constant");
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
                            throw std::invalid_argument("Error: Invalid input");
                        }
                    } else if (isdigit(symbol)) {
                        state = Digit;
                        minus_count = 0;
                        skip_digit();
                    } else {
                        throw std::invalid_argument("Error: Invalid input");
                    }
                    break;
                case Minus:
                    if (is_correct_const(symbol)) {
                        if (symbol == 'P') {
                            curr++;
                            if (*curr != 'i') {
                                throw std::invalid_argument("Error: Invalid input");
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
                        throw std::invalid_argument("Error: Invalid input");
                    }
                    break;

                case Operation:
                    if (is_correct_const(symbol)) {
                        if (symbol == 'P') {
                            curr++;
                            if (*curr != 'i') {
                                throw std::invalid_argument("Error: Invalid input");
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
                            throw std::invalid_argument("Error: Invalid input");
                        }

                    } else if (isdigit(symbol)) {
                         state = Digit;
                         minus_count = 0;
                         skip_digit();
                     } else {
                         throw std::invalid_argument("Error: Invalid input");
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
                        throw std::invalid_argument("Error: Invalid input");
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
                                throw std::invalid_argument("Error: Invalid input");
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
                        throw std::invalid_argument("Error: Invalid input");
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
                        throw std::invalid_argument("Error: Invalid input");
                    }
                    break;
            }

            if (minus_count > 2) {
                throw std::invalid_argument("Error: Invalid input");
            }
            curr++;
        }
        if (state != Digit && state != RBracket) {
            throw std::invalid_argument("Error: Invalid input");
        }
        if (bracket_balance != 0) {
            throw std::invalid_argument("Error: Bad bracket balance");
        }
        curr = expr_begin;
    }

    T calculate(string_it begin, string_it end) {
        if (!checked) {
            check_input();
        }

        //get first term
        T term;
        T numb = get_number(begin, end);
        term = get_term(numb, begin, end);

        return get_expr(term, begin, end);
    }

    T calculate() {
        return calculate(expr_begin, expr_end);
    }

private:
    bool checked;
    std::string expr;
    string_it expr_begin;
    string_it expr_end;
    string_it curr;
};
