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
    div = '/'
};

void skip_trash(Striter &s, Striter &end) 
{
    while (s != end && isspace(*s)) {
        s++;
    }                                
}

int
get_number(Striter &s, Striter &end)
{
    skip_trash(s, end);
    if (s == end) {
        throw std::invalid_argument("no number");
    }
    bool flag = false;                          
    int value;
    int sign = 1;                               
    if (*s == '-') {                            
        s++;
        sign = -1;                              
    }
    value = 0;                                  
    while (s != end && *s <= '9' && *s >= '0') {
        value *= 10;                            
        value += *s - '0';                      
        flag = true;                            
        s++;
    }            
    if (!flag) {
        throw std::invalid_argument("bad number");
    }
    value *= sign;
    return value;
}

Lexem
next_elem(Striter &s, Striter &end, Operation &op)
{
    skip_trash(s, end);
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
            return Lexem::nop;
    }
}

int
term (Striter &s, Striter &end, Lexem &lex, Operation &op) {
    int n = 0, res = 0; 
    res = get_number(s, end);
    lex = next_elem(s, end, op);
    while (lex == Lexem::mul || lex == Lexem::div) {
        n = get_number(s, end);
        res = op(res, n); 
        lex = next_elem(s, end, op);
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
    try {
        std::cout << expr(s, end) << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 134;
    }
    return 0;
}
