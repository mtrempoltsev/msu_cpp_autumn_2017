#include <iostream>
#include <stdio.h>

int prim(char *str) {
    int sign = 1;
    int n;

    while(*str == ' ') { //this part processes situation when unary minus is separated from its number by spaces
        str++;
    }
    if (*str == '-') {
        sign = -1;
        str++;
    } //str contains beginning of the part of string which is supposed to be numeric

    if (!sscanf(str, "%d", &n)) { //read the number
        std::cerr << "Not a numeric expression\n";
        exit(1);
    }
    
    while(*str >= '0' && *str++ <= '9') //check if there is something left in prim after number
        {}
    while(*str == ' ') {
        str++;
    }
    if (*str) {
        std::cerr << "Not a numeric expression\n";
        exit(1);
    }

    return n * sign;
}

int term(char *str) {
    if (!(*str)) {
        std::cerr << "Not a numeric expression\n";
        exit(1);
    }

    char *p = str;
    while(*p++) //set p to the end of str
        {}
    while (--p >= str) {
        if (*p == '*') { //right sign in a term is *
            *p = 0;
            return term(str) * prim(p + 1);
        }
        if (*p == '/') { //right sign in a term is /
            *p = 0;
            int rvalue = prim(p + 1);
            if (rvalue)
                return term(str) / rvalue;  
            else {
                std::cerr << "Division by zero\n";
                exit(1);
            }
        }
    }
    
    return prim(str);        
}

char *rightest_sum_sign(char *str) {
    if (!*str) 
        return NULL;
    
    char *p = str;
    while(*p++) //set p to the end of str
        {}

    while(--p >= str) { //search for the rightest + or non-unary -
        if (*p == '+') 
            return p; //if the rightest sign is + then it's simple
        if (*p == '-') { //if the rightest sign is - then it is possibly unary
            char *p1 = p;
            while (--p1 >= str && *p1 == ' ') //set pointer to find the next symbol to the left of rightest - sign
                {}
            if (p1 < str) //no other signs left of - in the expr then minus was unary and the whole expr is a term
                return NULL;
            if (*p1 >= '0' && *p1 <= '9') //if there is a number left of the - than - is binary and it's simple
                return p;
            p = p1 + 1; //the rightest binary operation is not + or -; continue search from the pos of this operation
        }
    }
    return NULL; //if no operations were found then expr is a term
}

int expr(char *str) {
    if (!(*str)) {
        std::cerr << "Not a numeric expression\n";
        exit(1);
    }
    
    char *p = rightest_sum_sign(str); //p gets a position of the rightest + or binary -

    if (!p) //if no such position found then expr es a term
        return term(str);

    if (*p == '+') {
        *p = 0;
        return expr(str) + term(p + 1);
    }

    if (*p == '-') {
        *p = 0;
        return expr(str) - term(p + 1);
    }

    return term(str);
}

int main(int argc, char *argv[]) {

    if (argc < 2) {
        std::cerr << "String as an argument is required\n";
        return 1;
    }

    std::cout << expr(argv[1]) << std::endl;

    return 0;
}
