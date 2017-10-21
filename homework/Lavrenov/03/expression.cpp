#include "expression.h"

Expression::Expression(std::string s)
{
    validateSyntax(s);
    root = new Operator(s);
}

int Expression::execute(){
    return root->execute();
}

void Expression::error(){
    std::cerr <<"syntax error\n";
    exit(-2);
}

void Expression::validateSyntax(std::string& s){
    //TODO
    char prevSymbol = '\0';
    int brackets = 0;
    for(int i = 0; i < s.length(); ++i){

        if(s[i] == '-' &&
                (Operator::isOperator(prevSymbol) || prevSymbol == '(' || prevSymbol == '\0')){
            prevSymbol = 'U';
            continue;
        }

        if(Operator::isNumber(s[i]) || s[i] == 'P' || s[i] == 'E'){
            //error();
            if(prevSymbol == ')')
                error();
            if(s[i] == 'P' || s[i] == 'E'){
                if(Operator::isNumber(prevSymbol) || prevSymbol == 'P' || prevSymbol == 'E')
                    error();
            }
            if(Operator::isNumber(s[i])){
                if(prevSymbol == 'P' || prevSymbol == 'E')
                    error();
                if(Operator::isNumber(prevSymbol) && isSpace(s[i - 1])){
                    error();
                }
            }
            if(s[i] == 'P' && i + 1 < s.length()){
                if(s[i + 1] != 'i'){
                    error();
                }else{
                    ++i;
                    prevSymbol = 'P';
                    continue;
                }
            }
        }

        if(s[i] == '('){
            if(!(Operator::isOperator(prevSymbol) || prevSymbol == 'U' || prevSymbol == '(')){
                error();
            }
            ++brackets;
        }

        if(s[i] == ')'){
            if(Operator::isOperator(prevSymbol) || prevSymbol == '(' || prevSymbol == 'U' || prevSymbol == '\0'){
                error();
            }
            --brackets;
        }

        if(Operator::isOperator(s[i])){
            if(Operator::isOperator(prevSymbol) || prevSymbol == 'U' || prevSymbol == '(' || prevSymbol == '\0')
                error();
        }

        if(Operator::isArephmeticSymbol(s[i]) || isSpace(s[i])){
            if(Operator::isArephmeticSymbol(s[i])){
                prevSymbol = s[i];
            }
        } else{
            error();
        }
    }
}

bool Expression::isSpace(char s){
    switch(s){
    case ' ':
        return true;
        break;
    case '\0':
        return true;
        break;
    case '\n':
        return true;
        break;
    default:
        return false;
        break;
    }
}

Expression::~Expression()
{
    delete root;
}

