#ifndef OPERATOR_H
#define OPERATOR_H
#include <string>
#include <iostream>
#include <stdlib.h>

enum operandType{
    Plus,
    Minus,
    Multiply,
    Divide
};

class Operator
{
public:
    Operator(std::string);
    ~Operator();
    Operator* rightOperand;
    Operator* leftOperand;
    operandType op;
    int token;
    int execute();
    static constexpr double Pi = 3.14;
    static constexpr double E = 2.7;
    static bool isArephmeticSymbol(char);
    static bool isOperator(char);
    static bool isNumber(char);
private:
    void init(std::string);
    int getoperatorPriority(char);
    operandType getOperandType(char);
};


#endif // OPERATOR_H
