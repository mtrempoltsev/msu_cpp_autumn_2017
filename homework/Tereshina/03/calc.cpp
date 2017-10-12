#include <iostream>
#include <stdio.h>
#include <unordered_map>

std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

class Expression {
    char *str;
    char *beg;
    char *end;
    int value;
    bool is_calculated;

    class Prim {
        char *beg;
        char *end;
        public:
            Prim(char *beg, char *end) {
                this->beg = beg;
                this->end = end;
            }
            int calculate() {

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
                   throw "Invalid prim";
                }

                *cur_end = 0;
                std::unordered_map<std::string, double>::const_iterator got = constants.find (cur_beg);

                if ( got == constants.end() ) {
                    int n;
                    if (!sscanf(cur_beg, "%d", &n)) {
                        throw "Invalid prim";
                    } else {
                        while(*cur_beg) {
                            if (*cur_beg > '9' || *cur_beg < '0') {
                                throw "Invalid prim";
                            }
                            cur_beg++;
                        }
                        return sign * n;
                    }
                } else {
                    return sign * int( got->second);
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
            int calculate() {

                char *cur_beg = this->beg;
                char *cur_end = this->beg;
                int cur_value = 1;
                char prev_sign = '*';

                while(true) {
                    if (cur_end == this->end) {
                        Prim prim(cur_beg, cur_end);
                        int p = prim.calculate();
                        if (prev_sign == '*') {
                            cur_value *= p;
                        }
                        if (prev_sign == '/') {
                            if (p) {                            
                                cur_value /= p;
                            } else {
                                throw "Divizion by zero";
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
                        int p = prim.calculate();
                        if (prev_sign == '*') {
                            cur_value *= p;
                        }
                        if (prev_sign == '/') {
                            if (p) {                            
                                cur_value /= p;
                            } else {
                                throw "Divizion by zero";
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
    int calculate() {
        if (is_calculated) {
            return value;
        }

        char *cur_beg = this->beg;
        char *cur_end = this->beg;
        int cur_value = 0;
        int prev_sign = 1;
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
                    throw "Unbalanced parentheses";
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
    
    Expression exp(argv[1]);
    try {    
        std::cout << exp.calculate() << std::endl;
    } catch (const char *exeption) {
        std::cerr << exeption << std::endl;
        return 1;
    }

    return 0;
}
