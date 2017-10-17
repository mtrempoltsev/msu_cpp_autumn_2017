#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <unordered_map>
#include <iostream>
#include <exception>

using namespace std;

// ======================================================================================
int check(const char*& text, int value, bool invalid=false);
void check_calc();

// ======================================================================================

enum class Token // : char
{
    End,     //0
    Minus,   //1
    Plus,    //2
    Mul,     //3
    Div,     //4
    Number,  //5
    Invalid, //6
    Const,
    OpenBracket,
    ClosBracket
};

extern std::unordered_map<std::string, double> constants;

class Calculator
{
private:
    int value;
    int level;
    const char* text;

    Token getToken();
    //Token _getToken();

    int _prim();
    int prim();
    int term();


public:
    Calculator();

    int token_sequence(const char*& text);
    //int calculate(const char*& text);
};
#endif // CALCULATOR_H
