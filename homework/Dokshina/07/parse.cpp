#pragma once

typedef std::string::iterator string_it;

template <typename T>
class Numb {};

template <>
class Numb<int>
{
public:
    int parse(string_it& curr, string_it expr_begin, string_it expr_end, int sign) {
        long number = 0;
        for ( ; curr < expr_end && isdigit(*curr); curr++) {
            number *= 10;
            number += *curr - '0';
            if (number * sign > NumericTraits<int>::max || number * sign < NumericTraits<int>::min) {
                throw std::overflow_error("Error: Invalid size for int");
            }
        }

        return int(number * sign);
    }
};

template <>
class Numb<long>
{
public:
    long parse(string_it& curr, string_it expr_begin, string_it expr_end, int sign) {
        double number = 0;
        for ( ; curr < expr_end && isdigit(*curr); curr++) {
            number *= 10;
            number += *curr - '0';

            if (number * sign > NumericTraits<long>::max || number * sign < NumericTraits<long>::min) {
                throw std::overflow_error("Error: Invalid size for long");
            }
        }
        return long(number * sign);
    }
};

template <>
class Numb<double>
{
public:
    double parse(string_it& curr, string_it expr_begin, string_it expr_end, int sign) {
        long double number = 0;
        for ( ; curr < expr_end && isdigit(*curr); curr++) {
            number *= 10;
            number += *curr - '0';

            if (number * sign > NumericTraits<double>::max || number * sign < NumericTraits<double>::min) {
                throw std::overflow_error("Error: Invalid size for double");
            }
        }

        if (*curr == '.') {
             double frac = 0.1;
             curr++;


             for ( ; curr < expr_end && isdigit(*curr); curr++) {
                 number += (*curr - '0') * frac;
                 frac *= 0.1;
                 if (number * sign > NumericTraits<double>::max || number * sign < NumericTraits<double>::min) {
                     throw std::overflow_error("Error: Invalid size for double");
                 }
             }
        }
        return double(number * sign);
    }
};


template <typename T>
T find_number(string_it& curr, string_it expr_begin, string_it expr_end, int sign) {
    std::unordered_map<std::string, double> constants = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

    if (*curr == 'P') {
        curr++;
        curr++;
        return T(constants.find("Pi")->second);
    }

    if (*curr == 'e') {
        curr++;
        return T(constants.find("e")->second);
    }

    Numb<T> numb;
    T number = numb.parse(curr, expr_begin, expr_end, sign);

    return T(number * sign);
}
