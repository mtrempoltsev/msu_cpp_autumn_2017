#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "operator.h"

template<class T, class Parser>
class Expression
{
public:
    TableOfVariables<T> table;
    Expression(std::string);
    T execute();
    ~Expression();
private:
    Parser parser;
    void error();
    void validateSyntax(std::string& s);
    Operator<T, Parser>* root;
};

template<class T, class Parser>
Expression<T, Parser>::Expression(std::string s)
    : parser(), table()
{
    validateSyntax(s);
    root = new Operator<T, Parser>(s, table);
}

template<class T, class Parser>
T Expression<T, Parser>::execute(){
    return root->execute();
}

template<class T, class Parser>
void Expression<T, Parser>::error(){
    std::cerr <<"syntax error\n";
    exit(-2);
}

template<class T, class Parser>
void Expression<T, Parser>::validateSyntax(std::string& s){
    //TODO
    char prevSymbol = '\0';
    int brackets = 0;
    for(int i = 0; i < s.length(); ++i){

        if(s[i] == '-' &&
                (Operator<T, Parser>::isOperator(prevSymbol) || prevSymbol == '(' || prevSymbol == '\0')){
            prevSymbol = 'U';
            continue;
        }

        if(!Operator<T, Parser>::isOperator(s[i]) && s[i] != '(' && s[i] != ')' && !Operator<T, Parser>::isSpace(s[i])){
            if(prevSymbol == 'T'){
                if(Operator<T, Parser>::isSpace(s[i - 1])){
                    error();
                }
            }
            if(prevSymbol == ')')
                error();
            int length = 1;
            while(i + length < s.length() && !Operator<T, Parser>::isOperator(s[i + length]) && s[i + length] != '(' &&
                  s[i + length] != ')' && !Operator<T, Parser>::isSpace(s[i + length])){
                ++length;
            }
            std::string token = s.substr(i, length);
            if(!table.exist(token)){
                parser.parse(token);
            }
			i += length - 1;
            prevSymbol = 'T';
            continue;
        }
        /*if(Operator::isNumber(s[i]) || s[i] == 'P' || s[i] == 'E'){
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
                if(Operator::isNumber(prevSymbol) && Operator::isSpace(s[i - 1])){
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
        }*/

        if(s[i] == '('){
            if(!(Operator<T, Parser>::isOperator(prevSymbol) || prevSymbol == 'U' || prevSymbol == '(' || prevSymbol == '\0')){
                error();
            }
            ++brackets;
        }

        if(s[i] == ')'){
            if(Operator<T, Parser>::isOperator(prevSymbol) || prevSymbol == '(' || prevSymbol == 'U' || prevSymbol == '\0'){
                error();
            }
            --brackets;
        }

        if(Operator<T, Parser>::isOperator(s[i])){
            if(Operator<T, Parser>::isOperator(prevSymbol) || prevSymbol == 'U' || prevSymbol == '(' || prevSymbol == '\0')
                error();
        }


        if(!Operator<T, Parser>::isSpace(s[i])){
            prevSymbol = s[i];
        }

    }
}

template<class T, class Parser>
Expression<T, Parser>::~Expression()
{
    delete root;
}


#endif // EXPRESSION_H
