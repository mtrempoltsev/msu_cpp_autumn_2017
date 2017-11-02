#include<iostream>
#include<string>
#include<cctype>
#include<stdexcept>
#include<functional>
#include<limits>
#include<cmath>
using Striter = std::string::const_iterator;
template<typename T>
class Computer
{
    // Коды ошибок:
    // 1 - невалидное выражение
    public:
    int ErrorCode = 1;
    
    T
    compute(std::string str) {
        s = str.begin();
        end = str.end();
        T res = expr();
        if (bracket_count != 0)
            throw std::invalid_argument("Bracket count error");
        return res;
    }

    using Operation = std::function<T(T, T)>;
    
    protected:
        const double
            Pi = 3.14,
            e = 2.7;

        enum class Lexem
        {               
            nop,        
            eof,        
            add = '+',  
            sub = '-',  
            mul = '*',  
            div = '/'   
        };

        Striter s, end;
        int bracket_count = 0;

        T
        expr () {
            Operation op = add;
            Lexem lex = Lexem::add;
            T res = term(lex, op);
            while (lex != Lexem::eof) {
                if (lex == Lexem::add || lex == Lexem::sub) {
                    Operation op1 = op;
                    T k = term(lex, op);
                    res = op1(res, k);
                } else {
                    throw std::invalid_argument("error in expr");
                    return 0;
                }
            }

            return res;
        }

        static inline T         
        add (T a, T b)
        {                  
            return a + b;  
        }                  
                           
        static inline T         
        sub (T a, T b)
        {                  
            return a - b;  
        }                  
                           
        static inline T         
        mul (T a, T b)
        {                  
            return a * b;  
        }                  
                               
        static inline T         
        divi (T a, T b)
        {
            if (b == 0) {
                throw std::invalid_argument("zero devision"); 
            }
            return a / b;  
        }
        
        bool
        check(long long &a, T &b)
        {
            return a >= std::numeric_limits<T>().min() &&
            a <= std::numeric_limits<T>().max();
        }
                
        void 
        skip_trash()
        {                                        
            while (s != end && isspace(*s)) {    
                s++;                             
            }                                    
        }

        T                                               
        get_number()              
        {
            skip_trash();                           
            if (s == end) {                               
                throw std::invalid_argument("no number"); 
            }
            bool flag = false;                            
            long long value; 
            int sign = 1;
            T tst = 1;
            if (*s == '-') {                              
                s++;                                      
                sign = -1;                                
            }    
            if (*s == '(') {
                s++;
                bracket_count++;
                return expr() * sign;
            }
            if (*s == 'P') {
                if (++s != end && *s == 'i'){
                    s++;
                    return Pi * sign;
                } else {
                    throw std::invalid_argument("bad number");
                }
            }
            if (*s == 'e') {
                s++;
                return e * sign; 
            }
            value = 0;
            while (s != end && *s <= '9' && *s >= '0') {  
                value *= 10;                              
                value += *s - '0';                        
                flag = true;                              
                s++;                                      
            }
                
            if (*s == '.' || *s == ',') {
                s++;
                while (s != end && *s <= '9' && *s >= '0') {  
                    flag = true;                              
                    s++;                                      
                }   
            }
            if (!flag) {                                  
                throw std::invalid_argument("bad number");
            }                                             
            value *= sign;
            if (check(value, tst)) {
                return value;                                 
            } else {
                throw std::invalid_argument("number is out of range");
            }
            return 0;
        } 

        Lexem
        next_elem(Operation &op)
        {
            skip_trash();
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
                case ')':
                    bracket_count--;
                    return Lexem::eof;
                default:
                    return Lexem::nop;
            }
        }

        T
        term (Lexem &lex, Operation &op) {
            T n = 0, res = 0; 
            res = get_number();
            lex = next_elem(op);
            while (lex == Lexem::mul || lex == Lexem::div) {
                n = get_number();
                res = op(res, n); 
                lex = next_elem(op);
            }
            return res;
        }
};

// Bad c++! Why I need to do so...
template<>
bool
Computer<double>::check(long long &a, double &b) {
    return !std::isnan(b) && !std::isinf(b);
}
                               
template<>                     
double                         
Computer<double>::get_number() 
{                           
    skip_trash();                           
    if (s == end) {                               
        throw std::invalid_argument("no number"); 
    }
    bool flag = false;                            
    double value; 
    long long a;
    double value1 = 0;
    int sign = 1;
    if (*s == '-') {                              
        s++;                                      
        sign = -1;                                
    }    
    if (*s == '(') {
        s++;
        bracket_count++;
        return expr() * sign;
    }
    if (*s == 'P') {
        if (++s != end && *s == 'i'){
            s++;
            return Pi * sign;
        } else {
            throw std::invalid_argument("bad number");
        }
    }
    if (*s == 'e') {
        s++;
        return e * sign; 
    }
    value = 0;
    while (s != end && *s <= '9' && *s >= '0') {  
        value *= 10;                              
        value += *s - '0';                        
        flag = true;                              
        s++;                                      
    }
    if (*s == '.' || *s == ',') {
        s++;
        while (s != end && *s <= '9' && *s >= '0') {  
            value1 += *s - '0';                        
            value1 /= 10;                              
            flag = true;                              
            s++;                                      
        }   
    }
    if (!flag) {                                  
        throw std::invalid_argument("bad number");
    }                                             
    value *= sign;
    value += value1;
    if (check(a, value)) {
        return value;                                 
    } else {
        throw std::invalid_argument("number is out of range");
    }
    return 0;
}                              


template <typename T>
bool 
check(T a, T b, std::string error = "error")
{
    if (a != b) {
        std::cout << error << std::endl;
        return false;
    }
    return true;
}

void 
test_double()
{
    Computer<double> c = Computer<double>();
    double d = c.compute(std::string("2.5 + 2.5"));
    check(d, 5., "d1");
}

void
test_int()
{
    Computer<int> c = Computer<int>();
    int d = c.compute(std::string("2.5 + 2.5"));
    check(d, 4, "i1");
    try {
        d = c.compute(std::string("9999999999999999 + 2.5"));
        std::cout<<"i2"<<std::endl;
    } catch (std::invalid_argument &e) {}

}

void
test_long()
{
    Computer<long> c = Computer<long>();
    long d = c.compute(std::string("2.5 + 2.5"));
    check(d, 4l, "l1");
    try {
        d = c.compute(std::string("9999999999999999 + 2.5"));
    } catch (std::invalid_argument &e) {
         std::cout<<"l2"<<std::endl;
    }
}

void
run_tests()
{
    test_double();
    test_int();
    test_long();
}

int
main(int argc, char *argv[])
{
    if (argc <= 2) {
        if (argc == 2) {
            if (argv[1][0] == '-' && argv[1][1] == 't') {
                run_tests();
                return 0;
            }
        }
        std::cout << "Usage: " << argv[0] << " 'Expr.' f" << std::endl;
        std::cout << "Where f is 'i' for int, 'd' for double or 'l' for long type" << std::endl;
        std::cout << "Write -t for run tests" << std::endl;
        return 0;
    }
    std::string str = std::string(argv[1]);
    if (argv[2][0] == 'i') {
        Computer<int> c = Computer<int>();
        try {
            std::cout << c.compute(str) << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return c.ErrorCode;
        }
    }
    if (argv[2][0] == 'l') {
        Computer<long> c = Computer<long>();
        try {
            std::cout << c.compute(str) << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return c.ErrorCode;
        }
    }
    if (argv[2][0] == 'd') {
        Computer<double> c = Computer<double>();
        try {
            std::cout << c.compute(str) << std::endl;
        } catch (std::invalid_argument &e) {
            std::cout << e.what() << std::endl;
            return c.ErrorCode;
        }
    }


    return 0;
}
