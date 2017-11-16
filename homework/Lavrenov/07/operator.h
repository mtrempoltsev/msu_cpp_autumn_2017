#ifndef OPERATOR_H
#define OPERATOR_H
#include <string>
#include <iostream>
#include "tableofvariables.h"
#include <memory>
#include <algorithm>

enum operandType{
    Plus,
    Minus,
    Multiply,
    Divide
};

template<class T, class Parser>
class Operator
{
public:
    Operator(std::string, TableOfVariables<T>& );
    ~Operator();
    TableOfVariables<T>& table;
    std::shared_ptr<Operator> rightOperand;
    std::shared_ptr<Operator> leftOperand;
    operandType op;
    Parser parser;
    T token;
    T execute();
    static constexpr double Pi = 3.14;
    static constexpr double E = 2.7;
    static bool isSpace(char);
    static bool isArephmeticSymbol(char);
    static bool isOperator(char);
    static bool isNumber(char);
private:
    void init(std::string);
    int getoperatorPriority(char);
    operandType getOperandType(char);
};

template<class T, class Parser>
Operator<T, Parser>::Operator(std::string s, TableOfVariables<T>& t)
    :parser(), table(t)
{
    //table = t;
    init(s);
}

template<class T, class Parser>
void Operator<T, Parser>::init(std::string s){
    int lpOperator = -1, hpOperator = -1, umin = -1, bracket = 0;
    char prevSymbol = '\0';
    for(int i = 0; i < s.length(); ++i){
        if(s[i] == ')'){
            prevSymbol = s[i];
            --bracket;
            continue;
        }
        if(s[i] == '('){
            ++bracket;
            prevSymbol = s[i];
            continue;
        }
        if(bracket > 0){
            continue;
        }
        if(isOperator(s[i]) && getoperatorPriority(s[i]) == 1){
            if(s[i] == '-' &&
                    (isOperator(prevSymbol) || prevSymbol == '(' || prevSymbol == '\0')){
                prevSymbol = 'U';
                umin = i;
                continue;
            }
            prevSymbol = s[i];
            lpOperator = i;
            break;
        }
        if(isOperator(s[i]) && getoperatorPriority(s[i]) == 2){
            hpOperator = i;
            prevSymbol = s[i];
            continue;
        }
        if(!isSpace(s[i])){
            prevSymbol = 'T';
        }
    }
    if(lpOperator != -1){
        leftOperand = std::make_shared<Operator>(Operator(s.substr(0 , lpOperator - 1), table));
        rightOperand = std::make_shared<Operator>(Operator(s.substr(lpOperator + 1), table));
        op = getOperandType(s[lpOperator]);
        return;
    }
    if(hpOperator != -1){
        leftOperand = std::make_shared<Operator>(Operator(s.substr(0 , hpOperator - 1), table));
        rightOperand = std::make_shared<Operator>(Operator(s.substr(hpOperator + 1), table));
        op = getOperandType(s[hpOperator]);
        return;
    }
    if(prevSymbol == ')'){
        for(int i = 0; i < s.length(); ++i){
            if(s[i] == '('){
                s[i] = ' ';
                break;
            }
        }
        for(int i = s.length() - 1; i >= 0; --i){
            if(s[i] == ')'){
                s[i] = ' ';
                break;
            }
        }
        if(umin != -1){
            leftOperand = std::make_shared<Operator>(Operator("-1", table));
            rightOperand = std::make_shared<Operator>(Operator(s.substr(umin + 1), table));
            op = operandType::Multiply;
            return;
        }
        init(s);
        return;
    }
    leftOperand = nullptr;
    rightOperand = nullptr;
    if(umin != -1)
        s.erase(umin, 1);
    s.erase(remove_if(s.begin(), s.end(), isspace), s.end());

    if(table.exist(s)){
        if(umin != -1)
            token = - table.getVariable(s).getValue();
        else
            token = table.getVariable(s).getValue();
        return;
    }
    /*
    if(s.find("Pi") >= 0 && s.find("Pi") < s.length()){
        if(umin != -1)
            token = - Operator::Pi;
        else
            token = Operator::Pi;
        return;
    }
    if(s.find("E") >= 0 && s.find("E") < s.length()){
        if(umin != -1)
            token = - Operator::E;
        else
            token = Operator::E;
        return;
    }*/
    if(umin != -1){
        token = -1 * parser.parse(s);
        //atoi(s.substr(umin + 1).c_str());
    }else{
        token = parser.parse(s);
    }
}

template<class T, class Parser>
int Operator<T, Parser>::getoperatorPriority(char s){
    switch(s){
    case '+':
        return 1;
        break;
    case '-':
        return 1;
        break;
    case '*':
        return 2;
        break;
    case '/':
        return 2;
        break;
    default:
        return -1;
        break;
    }
}

template<class T, class Parser>
bool Operator<T, Parser>::isArephmeticSymbol(char s){
    if(isOperator(s)){
        return true;
    }
    switch(s){
    case '0':
        return true;
        break;
    case '1':
        return true;
        break;
    case '2':
        return true;
        break;
    case '3':
        return true;
        break;
    case '4':
        return true;
        break;
    case '5':
        return true;
        break;
    case '6':
        return true;
        break;
    case '7':
        return true;
        break;
    case '8':
        return true;
        break;
    case '9':
        return true;
        break;
    case '(':
        return true;
        break;
    case ')':
        return true;
        break;
    case 'P':
        return true;
        break;
    case 'i':
        return true;
        break;
    case 'E':
        return true;
        break;
    default:
        return false;
        break;
    }
}

template<class T, class Parser>
bool Operator<T, Parser>::isSpace(char s){
    switch(s){
    case ' ':
        return true;
        break;
    case '\t':
        return true;
        break;
    case '\n':
        return true;
        break;
    case '\v':
        return true;
        break;
    case '\f':
        return true;
        break;
    case '\r':
        return true;
        break;
    default:
        return false;
        break;
    }
}

template<class T, class Parser>
bool Operator<T, Parser>::isNumber(char s){
    switch(s){
    case '0':
        return true;
        break;
    case '1':
        return true;
        break;
    case '2':
        return true;
        break;
    case '3':
        return true;
        break;
    case '4':
        return true;
        break;
    case '5':
        return true;
        break;
    case '6':
        return true;
        break;
    case '7':
        return true;
        break;
    case '8':
        return true;
        break;
    case '9':
        return true;
        break;
    default:
        return false;
    }
}

template<class T, class Parser>
bool Operator<T, Parser>::isOperator(char s){
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

template<class T, class Parser>
T Operator<T, Parser>::execute(){
    if(leftOperand == nullptr && rightOperand == nullptr){
        return token;
    }
    switch(op){
    case operandType::Plus:
        return leftOperand->execute() + rightOperand->execute();
        break;
    case operandType::Divide:
        if(rightOperand->execute() == 0){
            std::cerr<< "division by 0\n";
            exit(-1);
        }
        return leftOperand->execute() / rightOperand->execute();
        break;
    case operandType::Minus:
        return leftOperand->execute() - rightOperand->execute();
        break;
    case operandType::Multiply:
        return leftOperand->execute() * rightOperand->execute();
        break;
    }
}

template<class T, class Parser>
operandType Operator<T, Parser>::getOperandType(char c){
    switch(c){
    case '+':
        return operandType::Plus;
        break;
    case '-':
        return operandType::Minus;
        break;
    case '*':
        return operandType::Multiply;
        break;
    case '/':
        return operandType::Divide;
        break;
    default:
        exit(-1);
        break;
    }
}

template<class T, class Parser>
Operator<T, Parser>::~Operator()
{
}

#endif // OPERATOR_H
