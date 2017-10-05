#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

bool isOperator(char s){
    switch(s){
    case '+':
        return true;
        break;
    case '-':
        return true;
        break;
    case '*':
        return true;
        break;
    case '/':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool isSpace(char s){
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

bool isNumber(char s){
    if(s >= '0' && s <= '9'){
        return true;
    } else{
        return false;
    }
}

bool isArephmeticSymbol(char s){
    if(isNumber(s)){
        return true;
    }
    if(isOperator(s)){
        return true;
    }
    if(isSpace(s)){
        return true;
    }
    return false;
}

int toNumber(char s){
    return int(s - '0');
}

int executeTerm(const string& term){
    int res = 0;
    int tokenpos = -1;
    bool unarMinus = false;
    char prevsymbol = '\0';
    for(int i = term.length() - 1; i >= 0; --i){
        if(!isArephmeticSymbol(term[i]))
            exit(1);

        if(isNumber(term[i])){
            int start, end = i;
            while(isNumber(term[i])){
                --i;
            }
            start = i + 1;
            string num = term.substr(start, end - start + 1);
            res = atoi(num.c_str());
            prevsymbol = term[end];
            if(i < 0)
                break;
        }
        if(term[i] == '*' || term[i] == '/'){
            tokenpos = i;
            break;
        }
        if(term[i] == '+'){
            cerr<<"syntax error\n";
            exit(1);
        }
        if(prevsymbol == '\0' && isOperator(term[i])){
            cerr<<"syntax error\n";
            exit(1);
        }
        if(term[i] == '-' && prevsymbol != 'U'){
            prevsymbol = 'U';
            unarMinus = true;
            continue;
        }
        if(isOperator(term[i]) || isNumber(term[i])){
            prevsymbol = term[i];
        }
        if(isOperator(prevsymbol) && isOperator(term[i])){
            cerr<<"syntax error\n";
            exit(1);
        }
    }
    if(unarMinus){
        res *= -1;
    }
    if(tokenpos != -1){
        if(term[tokenpos] == '*'){
            res *= executeTerm(term.substr(0, tokenpos));
        }else if(term[tokenpos] == '/'){
            res = executeTerm(term.substr(0, tokenpos)) / res;
        }
    }
    return res;
}

int executeExpr(const string& expr){
    string term;
    int tokenpos = -1, res = 0, umin = -1;
    char prevsymbol = '\0';
    for(int i = expr.length() - 1; i >= 0; --i){
        //TODO unarminus;
        if(!isArephmeticSymbol(expr[i])){
            cerr<<"syntax error\n";
            exit(1);
        }
        if(isOperator(prevsymbol) && isOperator(expr[i])){
            cerr<<"syntax error\n";
            exit(1);
        }
        if(prevsymbol == '\0' && isOperator(expr[i])){
            cerr<<"syntax error\n";
            exit(1);
        }
        if(expr[i] == '-' && !isOperator(prevsymbol) && prevsymbol != 'U'){
            umin = i;
            prevsymbol = 'U';
            continue;
        }
        if(isNumber(expr[i]) && prevsymbol == 'U'){
            tokenpos = umin;
            break;
        }
        if(isOperator(expr[i]) || isNumber(expr[i])){
            prevsymbol = expr[i];
        }
        if(expr[i] == '-' || expr[i] == '+'){
            tokenpos = i;
            break;
        }
    }
    if(tokenpos != -1){
        term = expr.substr(tokenpos + 1, expr.length() - tokenpos - 1);
        if(expr.substr(0 ,tokenpos) == ""){
            cerr<<"syntax error\n";
            exit(1);
        }
        if(expr[tokenpos] == '-'){
            res = executeExpr(expr.substr(0 ,tokenpos)) - executeTerm(term);
        }else if(expr[tokenpos] == '+'){
            res = executeTerm(term) + executeExpr(expr.substr(0, tokenpos));
        }
    }else{
        res = executeTerm(expr);
    }
    return res;
}

int main(int argc, char** argv)
{
    if(argc < 2)
        exit(1);
    string expression = argv[1];
    cout<<executeExpr(expression);
    return 0;
}

