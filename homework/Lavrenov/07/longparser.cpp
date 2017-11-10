#include "longparser.h"
#include <iostream>

LongParser::LongParser()
{

}

long long LongParser::parse(std::string s){
    long long res = 0;

    res = std::stol(s);

    return res;
}
