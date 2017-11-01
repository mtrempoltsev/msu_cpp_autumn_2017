#include "intparser.h"
#include <string>
#include <exception>
#include <iostream>

IntParser::IntParser()
{

}

int IntParser::parse(std::string s){
    int res = 0;
    try{
        res = std::stoi(s);
    } catch(std::exception e){
        std::cerr<<"nan\n";
        exit(-1);
    }
    return res;
}
