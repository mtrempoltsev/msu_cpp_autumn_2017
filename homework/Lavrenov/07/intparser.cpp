#include "intparser.h"
#include <string>
#include <exception>
#include <iostream>

IntParser::IntParser()
{

}

int IntParser::parse(std::string s){
    int res = 0;
    res = std::stoi(s);

    return res;
}
