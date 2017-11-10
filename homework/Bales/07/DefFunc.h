#pragma once
#include <iostream>
#include <utility>
#include <unordered_map>
#include <string>
#include <cstring>
#include <sstream>
#include <memory>
#include <limits>

static const std::unordered_map<std::string, double> Constants = {
    { "e", 2.7 },
    { "Pi", 3.14 },
    { "eps", 1e-6 }
};

class DivideByZeroException : public std::runtime_error {
public:
    DivideByZeroException(const char* err) : std::runtime_error(err) { }
    virtual const char* what() const throw() {
        return std::runtime_error::what();
    }
};