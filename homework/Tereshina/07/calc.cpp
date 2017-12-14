#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <limits>

std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

enum errors {
    DIV_BY_ZERO = 0,
    PARSE_ERR,
    PAR_BALANCE,
    NUMERIC_LIMIT,
};

class CalcError {
    errors e;
public:
    CalcError(errors e) {
        this->e = e;
    }
    const char *say() const {
        if (e == DIV_BY_ZERO) {
            return "Division by zero";
        }
        if (e == PARSE_ERR) {
            return "Invalid prim";
        }
        if (e == PAR_BALANCE) {
            return "Unbalanced parentheses";
        }
        if (e == NUMERIC_LIMIT) {
            return "Numeric limit exceeded";
        }
    }
};

template <typename T>
struct NumericTraits
{
};

template <>
struct NumericTraits<int>
{
    static constexpr auto min = std::numeric_limits<int>::min();
    static constexpr auto max = std::numeric_limits<int>::max();
};

template <>
struct NumericTraits<long>
{
    static constexpr auto min = std::numeric_limits<long>::min();
    static constexpr auto max = std::numeric_limits<long>::max();
};

template <>
struct NumericTraits<double>
{
    static constexpr auto min = std::numeric_limits<double>::lowest();
    static constexpr auto max = std::numeric_limits<double>::max();
};

template <class T>
class Expression {
    char *str;
    char *beg;
    char *end;
    T value;
    bool is_calculated;

    // strategy Parse
    class Prim {
        char *beg;
        char *end;
        public:
            Prim(char *beg, char *end) {
                this->beg = beg;
                this->end = end;
            }
            T calculate() {

                char *cur_beg = this->beg;
                char *cur_end = this->end;

                while(*cur_beg == ' ' && cur_beg < cur_end) {
                    cur_beg++;
                }

                while(*(cur_end - 1) == ' ' && cur_beg < cur_end) {
                    cur_end--;
                }

                if (*cur_beg == '(' && (*(cur_end - 1)) == ')') {
                    Expression expr(cur_beg + 1, cur_end - 1);
                    return expr.calculate();
                }

                int sign = 1;
                if (*cur_beg == '-') {
                    sign = -1;
                    cur_beg++;
                    while(*cur_beg == ' ' && cur_beg++ < end)
                        {}
                }

                if (cur_beg == cur_end) {
                   throw CalcError(PARSE_ERR);
                }

                *cur_end = 0;
                std::unordered_map<std::string, double>::const_iterator got = constants.find (cur_beg);

                if ( got == constants.end() ) {
                    long double dn;
                    if (!sscanf(cur_beg, "%Lf", &dn)) {
                        throw CalcError(PARSE_ERR);
                    } else {
                        if (NumericTraits<T>::max <= dn || NumericTraits<T>::min >= dn) {
                            throw CalcError(NUMERIC_LIMIT);
                        }
                        while(*cur_beg) {
                            if ((*cur_beg > '9' || *cur_beg < '0') && *cur_beg != '.') {
                                throw CalcError(PARSE_ERR);
                            }
                            cur_beg++;
                        }
                        return sign * T(dn);
                    }
                } else {
                    return sign * T( got->second);
                }

                return 666;
            }
    };
    
    class Term {
        char *beg;
        char *end;
        public:
            Term(char *beg, char *end) {
                this->beg = beg;
                this->end = end;
            }
            T calculate() {

                char *cur_beg = this->beg;
                char *cur_end = this->beg;
                T cur_value = 1;
                char prev_sign = '*';

                while(true) {
                    if (cur_end == this->end) {
                        Prim prim(cur_beg, cur_end);
                        T p = prim.calculate();
                        if (prev_sign == '*') {
                            cur_value *= p;
                        }
                        if (prev_sign == '/') {
                            if (p) {                            
                                cur_value /= p;
                            } else {
                                throw CalcError(DIV_BY_ZERO);
                            }
                        }

                        return cur_value;
                    }
                    if (*cur_end == '(') {
                        char par_count = 1;
                        cur_end++;
                        while(cur_end < this->end && par_count > 0) {
                            if (*cur_end == ')') par_count--;
                            if (*cur_end == '(') par_count++;
                            cur_end++;
                        }
                        continue;
                    }
                    if (*cur_end == '*' || *cur_end == '/') {
                        char sign = *cur_end;
                        Prim prim(cur_beg, cur_end);
                        T p = prim.calculate();
                        if (prev_sign == '*') {
                            cur_value *= p;
                        }
                        if (prev_sign == '/') {
                            if (p) {                            
                                cur_value /= p;
                            } else {
                                throw CalcError(DIV_BY_ZERO);
                            }
                        }
                        prev_sign = sign;
                        cur_beg = ++cur_end;
                        continue;
                    }
                    cur_end++;
                }

                return 0;
            }
    };

public:
    Expression() {
        char s[6] = "2 + 2";
        this->str = s;
        this->beg = this->end = NULL;
        value = 4;
        is_calculated = true;
    }
    Expression(char *str) {
        this->str = str;
        char *end = str;
        while(*end) {
            end++;
        }
        this->beg = str;
        this->end = end;
        is_calculated = false;
    }
    Expression(char *beg, char *end) {
        this->beg = beg;
        this->end = end;
        is_calculated = false;
    }
    T calculate() {
        if (is_calculated) {
            return value;
        }

        char *cur_beg = this->beg;
        char *cur_end = this->beg;
        T cur_value = 0;
        T prev_sign = 1;
        char prev_char = 0;

        while (true) {
            if (cur_end == this->end) {
                Term term(cur_beg, cur_end);
                cur_value += prev_sign * term.calculate();
                this->value = cur_value;
                this->is_calculated = true;
                return cur_value;
            }
            if (*cur_end == '(') {
                char par_count = 1;
                cur_end++;
                while(cur_end < this->end && par_count > 0) {
                    if (*cur_end == ')') par_count--;
                    if (*cur_end == '(') par_count++;
                    cur_end++;
                }
                if (par_count != 0) {
                    throw CalcError(PAR_BALANCE);
                }
                prev_char = ')';
                continue;
            }
            if (*cur_end == '+') {
                Term term(cur_beg, cur_end);
                cur_value += prev_sign * term.calculate();
                prev_sign = 1;
                prev_char = 0;
                cur_beg = ++cur_end;
                continue;
            }
            if (*cur_end == '-') {
                if (!prev_char) {
                    prev_sign *= -1;
                    prev_char = '-';
                    cur_beg = ++cur_end;
                    continue;
                }
                if (prev_char == '*' || prev_char == '/') {
                    prev_char = '-';
                    cur_end++;
                    continue;
                }
                Term term(cur_beg, cur_end);
                cur_value += prev_sign * term.calculate();
                prev_sign = -1;
                prev_char = 0;
                cur_beg = ++cur_end;
                continue;
            }
            if (*cur_end != ' ' && *cur_end != 0) prev_char = *cur_end;
            cur_end++;
        }
        
        return 0;
    }
};

int main(int argc, char **argv) {
    
    if (argc < 2) {
        std::cerr << "String as an argument is required\n";
        return 1;
    }

    try {
        Expression<int> exp(argv[1]);
        std::cout << exp.calculate() << std::endl;
    } catch (const CalcError& exception) {
        std::cerr << exception.say() << std::endl;
        return 1;
    }

    return 0;
}
