#include "doubleparser.h"
#include <string>
#include <exception>
#include <iostream>

DoubleParser::DoubleParser()
{

}

double DoubleParser::parse(std::string s){
    double res = 0;

    res = std::stod(s);

    return res;
}
