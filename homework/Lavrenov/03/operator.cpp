#include "operator.h"

//- ((4 * 6) - 9)
//4 * ((4 * 6) - 9)
Operator::Operator(std::string s)
{
    init(s);
}

void Operator::init(std::string s){
    int lpOperator = -1, hpOperator = -1, umin = -1, bracket = 0;
    char prevSymbol = '\0';
    for(int i = 0; i < s.length(); ++i){
        if(s[i] == ')'){
            prevSymbol = s[i];
            --bracket;
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
            lpOperator = i;
            break;
        }
        if(isOperator(s[i]) && getoperatorPriority(s[i]) == 2){
            hpOperator = i;
        }
        if(isArephmeticSymbol(s[i])){
            prevSymbol = s[i];
        }
    }
    if(lpOperator != -1){
        leftOperand = new Operator(s.substr(0 , lpOperator - 1));
        rightOperand = new Operator(s.substr(lpOperator + 1));
        op = getOperandType(s[lpOperator]);
        return;
    }
    if(hpOperator != -1){
        leftOperand = new Operator(s.substr(0 , hpOperator - 1));
        rightOperand = new Operator(s.substr(hpOperator + 1));
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
            leftOperand = new Operator("-1");
            rightOperand = new Operator(s.substr(umin + 1));
            op = operandType::Multiply;
            return;
        }
        init(s);
        return;
    }
    leftOperand = NULL;
    rightOperand = NULL;
    if(s.find("Pi") < s.length()){
        if(umin != -1)
            token = - Operator::Pi;
        else
            token = Operator::Pi;
        return;
    }
    if(s.find("E") < s.length()){
        if(umin != -1)
            token = - Operator::E;
        else
            token = Operator::E;
        return;
    }
    if(umin != -1){
        token = -1 * atoi(s.substr(umin + 1).c_str());
    }else{
        token = atoi(s.c_str());
    }
}

int Operator::getoperatorPriority(char s){
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

bool Operator::isArephmeticSymbol(char s){
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

bool Operator::isNumber(char s){
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

bool Operator::isOperator(char s){
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

int Operator::execute(){
    if(leftOperand == NULL && rightOperand == NULL){
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

operandType Operator::getOperandType(char c){
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

Operator::~Operator()
{
    delete leftOperand;
    delete rightOperand;
}
