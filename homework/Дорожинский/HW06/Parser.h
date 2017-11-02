#pragma once
#include <iostream>

template <typename T>
class Parser {
};

template <>
class Parser<long> {
public:
    static bool isParsable(char c) {
        if ((c >= '0') && (c <= '9')) {
            return true;
        }
        return false;
    }

    static long parse(const char*& str) {
        size_t offset = 0;
        long value = std::stol(str, &offset);
        str += offset;
        return value;
    }
};

template <>
class Parser<int> {
public:
    static bool isParsable(char c) {
        return Parser<long>::isParsable(c);
    }

    static int parse(const char*& str) {
        long value = Parser<long>::parse(str);
        if ((value > std::numeric_limits<int>::max()) || (value < std::numeric_limits<int>::lowest())) {
            std::cout << "[Parser<int>]: Warning. Value out of bounds." << std::endl;
        }
        return value;
    }
};

template <>
class Parser<double> {
public:
    static bool isParsable(char c) {
        if (((c >= '0') && (c <= '9')) || (c == '.')) {
            return true;
        }
        return false;
    }

    static double parse(const char*& str) {
        size_t offset = 0;
        double value = std::stod(str, &offset);
        str += offset;
        return value;
    }
};