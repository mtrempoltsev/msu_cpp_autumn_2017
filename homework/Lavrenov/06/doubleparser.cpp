#include "doubleparser.h"
#include <string>
#include <exception>
#include <iostream>

DoubleParser::DoubleParser()
{

}

double DoubleParser::parse(std::string s){
    double res = 0;
    try{
        res = std::stod(s);
    } catch(std::exception e){
        std::cerr<<"nan\n";
        exit(-1);
    }
    return res;
}
