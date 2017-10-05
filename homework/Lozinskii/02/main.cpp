#include<iostream>
#include<string>
#include<cctype>
#include<stdexcept>
using Striter = std::string::const_iterator;

typedef int (*Operation) (int, int);

inline int
add (int a, int b)
{
    return a + b;
}

inline int
sub (int a, int b)
{
    return a - b;
}

inline int
mul (int a, int b)
{
    return a * b;
}

inline int 
divi (int a, int b)
{
    return a / b;
}

enum class Lexem
{
    nop,
    eof,
    add = '+',
    sub = '-',
    mul = '*',
    div = '/',
    num = '0'
};

Lexem
next_elem(Striter &s, Striter &end, int &value, Operation &op)
{
    while (isspace(*s) && s != end) {
        s++;
    }
    if (s == end) {
        return Lexem::eof;
    }
    char c = *s;
    s++;
    switch (c) {
        case (int)Lexem::add:
            op = add;
            return Lexem::add;
        case (int)Lexem::sub:
            op = sub; 
            return Lexem::sub;
        case (int)Lexem::mul:
            op = mul;
            return Lexem::mul;
        case (int)Lexem::div:
            op = divi;
            return Lexem::div;
        default:
            bool flag = false;
            int sign = 1;
            s--;
            if (*s == '-') {
                sign = -1;
            }
            value = 0;
            while (s != end && *s <= '9' && *s >= '0') {
                value *= 10;
                value += *s - '0';
                flag = true;
                s++;
            }
            value *= sign;
            return flag ? Lexem::num : Lexem::nop;
    }
}

int
term (Striter &s, Striter &end, Lexem &lex, Operation &op) {
    int n = 0, res = 0; 
    lex = next_elem(s, end, res, op);
    if (lex != Lexem::num) {
        throw std::invalid_argument("error in term");
        return 0;
    }
    lex = next_elem(s, end, n, op);
    while (lex == Lexem::mul || lex == Lexem::div) {
        lex = next_elem(s, end, n, op);
        if (lex != Lexem::num) {
            throw std::invalid_argument("error in term");
            return 0;     
        }
        res = op(res, n); 
        lex = next_elem(s, end, n, op);
    }
    return res;
}

int
expr (Striter &s, Striter &end) {
    Operation op = add;
    Lexem lex = Lexem::add;
    int res = term(s, end, lex, op);
    while (lex != Lexem::eof) {
        if (lex == Lexem::add || lex == Lexem::sub) {
            res = op(res, term(s, end, lex, op));
        } else {
            throw std::invalid_argument("error in expr");
            return 0;
        }
    }
    return res;
}


int
main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " Expr." << std::endl;
        return 0;
    }
    std::string str = std::string(argv[1]);
    Striter s = str.begin();
    Striter end = str.end();
    std::cout << expr(s, end) << std::endl;
    return 0;
}
