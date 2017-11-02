#pragma once
#include <iostream>
#include <limits>
#include "DefFunc.h"

template <typename T>
class TParser {

};

template <>
class TParser<long> {
public:
    static long Parse(const std::string& expr) {
        if ((double)std::stol(expr) != std::stod(expr)) {            
            std::cerr << "Warning: Incorrect type conversion!" << std::endl;
            throw ExitCodeException(TExitCode::FAILED_TO_PARSE);
        }
        return std::stol(expr);
    }
};

template <>
class TParser<int> {
public:
    static int Parse(const std::string& expr) {
        long val = TParser<long>::Parse(expr);
        if (val > std::numeric_limits<int>::max() 
            || val < std::numeric_limits<int>::min()) {
            std::cerr << "Warning: Value out of range!" << std::endl;
            throw ExitCodeException(TExitCode::FAILED_TO_PARSE);
        }
        return val;
    } 
};

template <>
class TParser<double> {
public:
    static double Parse(const std::string& expr) {
        return std::stod(expr);
    }
};