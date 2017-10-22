#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "operator.h"

class Expression
{
public:
    static bool isSpace(char);
    Expression(std::string);
    int execute();
    ~Expression();
private:
    void error();
    void validateSyntax(std::string& s);
    Operator* root;
};

#endif // EXPRESSION_H
