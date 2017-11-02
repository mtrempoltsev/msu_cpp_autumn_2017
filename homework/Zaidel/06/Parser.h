//
// Created by peter on 29.10.17.
//

#ifndef EXPRCALCCLASS_PARSER_H
#define EXPRCALCCLASS_PARSER_H


#include <cstdlib>
#include <limits>
#include <cmath>

template<class T>
struct Parser
{};



template<>
struct Parser<double>
{
    static bool parse(const char*& text, double& value, bool skip)
    {

        if(!(*text >= '0' && *text <= '9'))
        {
            return false;
        }


        char * ptrEnd;
        double res = strtod(text, &ptrEnd);

        if(ptrEnd == text)
        {
            return false;
        }

        // check integer limits
        if (check_value(res) == false)
        {
            throw std::runtime_error("Value out of double limits!");
        }

        value = res;


        if (skip == true) {
            text = ptrEnd;
        }

        return true;
    }

    static bool check_value(double val)
    {
        return  std::isfinite(val);
    }
};


template<>
struct Parser<int>
{
    static bool parse(const char*& text, int& value, bool skip) {
        const char *prev_text = text;

//        long long res = 0;
//        bool isNumber = false;
//        for (; (*text >= '0' && *text <= '9'); ++text) {
//            res = res * 10 + (*text - '0');
//            isNumber = true;
//        }

        long long res = 0;
        long long prev_res = 0;

        bool isNumber = false;
        for (; (*text >= '0' && *text <= '9'); ++text) {
            prev_res = res;
            res = res * 10 + (*text - '0');

            // вышли за границы типа long
            if(res < prev_res)
            {
                if (!skip) {
                    text = prev_text;
                }

                throw std::runtime_error("Value out of int limits!");
            }

            isNumber = true;
        }

        // check integer limits
        if (check_value(res) == false)
        {
            throw std::runtime_error("Value out of int limits!");
        }

        if (isNumber)
            value = (int)res;

        if (!skip) {
            text = prev_text;
        }

        return isNumber;
    }

    static bool check_value(long long val)
    {
        // check integer limits
        if (val < std::numeric_limits<int>::min()
            || val > std::numeric_limits<int>::max()) {
            return false;
        }
        return true;
    }

};


template<>
struct Parser<long>
{
    static bool parse(const char*& text, long& value, bool skip) {
        const char *prev_text = text;

        long long res = 0;
        long long prev_res = 0;

        bool isNumber = false;
        for (; (*text >= '0' && *text <= '9'); ++text) {
            prev_res = res;
            res = res * 10 + (*text - '0');

            // вышли за границы типа
            if(res < prev_res)
            {
                if (!skip) {
                    text = prev_text;
                }

                throw std::runtime_error("Value out of long limits!");
            }

            isNumber = true;
        }

        // check limits
        if (check_value(res) == false)
        {
            throw std::runtime_error("Value out of long limits!");
        }

        if (isNumber)
            value = (long)res;

        if (!skip) {
            text = prev_text;
        }

        return isNumber;
    }

    static bool check_value(long long val)
    {
        // check integer limits
        if (val < std::numeric_limits<long>::min()
            || val > std::numeric_limits<long>::max()) {
            return false;
        }
        return true;
    }

};






#endif //EXPRCALCCLASS_PARSER_H
