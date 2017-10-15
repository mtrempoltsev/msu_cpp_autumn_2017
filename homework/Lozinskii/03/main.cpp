#include<iostream>
#include<string>
#include<cctype>
#include<stdexcept>
#include <functional>
using Striter = std::string::const_iterator;

class Computer  
{
    public:
        
    int compute(std::string str) {
            s = str.begin();
            end = str.end();
            int res = expr();
            if (bracket_count != 0)
                throw std::invalid_argument("Bracket count error");
            return res;
        }
    using Operation = std::function<int(int, int)>;
    

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
        int
        expr () {
            Operation op = add;
            Lexem lex = Lexem::add;
            int res = term(lex, op);
            while (lex != Lexem::eof) {
                if (lex == Lexem::add || lex == Lexem::sub) {
                    Operation op1 = op;
                    int k = term(lex, op);
                    res = op1(res, k);
                } else {
                    throw std::invalid_argument("error in expr");
                    return 0;
                }
            }

            return res;
        }

        
        static inline int         
        add (int a, int b)
        {                  
            return a + b;  
        }                  
                           
        
        static inline int         
        sub (int a, int b)
        {                  
            return a - b;  
        }                  
                           
        
        static inline int         
        mul (int a, int b)
        {                  
            return a * b;  
        }                  
                           
        
        static inline int         
        divi (int a, int b)
        {
            if (b == 0) {
                throw std::invalid_argument("zero devision"); 
            }
            return a / b;  
        }


        
        void 
        skip_trash()
        {                                        
            while (s != end && isspace(*s)) {    
                s++;                             
            }                                    
        }

        
        int                                               
        get_number()              
        {                                                 
            skip_trash();                           
            if (s == end) {                               
                throw std::invalid_argument("no number"); 
            }                                             
            bool flag = false;                            
            int value;                                    
            int sign = 1;
            if (*s == '(') {
                s++;
                bracket_count++;
                return expr();
            }
            if (*s == 'P') {
                if (++s != end && *s == 'i'){
                    s++;
                    return Pi;
                } else {
                    throw std::invalid_argument("bad number");
                }
            }
            if (*s == 'e') {
                s++;
                return e; 
            }
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

        
        int
        term (Lexem &lex, Operation &op) {
            int n = 0, res = 0; 
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
int
main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " Expr." << std::endl;
        return 0;
    }

    std::string str = std::string(argv[1]);
    Computer c = Computer();
    try {
        std::cout << c.compute(str) << std::endl;
    } catch (std::invalid_argument &e) {
        std::cout << e.what() << std::endl;
        return 134;
    }
    return 0;
}
