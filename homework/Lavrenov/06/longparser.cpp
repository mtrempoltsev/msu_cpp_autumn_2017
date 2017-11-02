#include "longparser.h"
#include <iostream>

LongParser::LongParser()
{

}

long long LongParser::parse(std::string s){
    long long res = 0;
    try{
        res = std::stol(s);
    } catch(std::exception e){
        std::cerr<<"nan\n";
        exit(-1);
    }
    return res;
}
