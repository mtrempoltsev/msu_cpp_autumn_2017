#include <iostream>
#include <stdexcept>
#include <math.h>
#include <string.h>

#include "calculator.hpp"
using namespace std;

// ======================================================================================
int check(const char*& text, int value, bool invalid=false);
void check_calc();

/*
 * ======================================================================================
 * ======================================================================================
 * ======================================================================================
 */
template<typename T>
void check(const char* text, T value, bool invalid=false)
{
    Calculator<T, Parser<T>> calc;
    const char* text_ptr = text;
    try
    {
        auto result = calc.token_sequence(text);
        if (almost_equal(result, value) && !invalid)
            std::cout << "Passed: " << text_ptr << " = " << value << std::endl;
        else
            std::cout << "Failed: " << text_ptr << " = " << result << " (" << value << " expected)" << std::endl;
    }
    catch(const CalculatorError& e)
    {
        if (invalid)
            std::cout << "Passed: " << text_ptr << " Exception message: " << e.what() << std::endl;
        else
            std::cout << "Failed: " << text_ptr << " Exception message: " << e.what() << " (" << value << " expected)" <<std::endl;
    }
    catch (...)
    {
        std::cout << "Unknown error occured." << std::endl;
    }
}
template <typename T>
void check_calc()
{
    check<T>("1+2", 3);
    check<T>("2+ 2", 4);
    check<T>("2 +2", 4);
    check<T>("2 + 2", 4);
    check<T>("2 +       2", 4);
    check<T>("2", 2);
    check<T>("-2", -2);
    check<T>("-2 - 2", -4);
    check<T>("2- 2", 0);
    check<T>("2- -  2", 4);
    check<T>("100 + 2", 102);
    check<T>("101 + 2", 103);
    check<T>("8 - 6 * 2 / 2", 2);
    check<T>("8 - 6 / 2 * 2", 2);
    check<T>("8 - 6 / 2 * - 2", 14);
    check<T>("2 + 3 * 4 - -2", 16);
    check<T>("2*-2", -4);
    check<T>("Pi", (T)constants["Pi"]);
    check<T>("Pi + e", (T)constants["Pi"] + (T)constants["e"]);
    check<T>("-Pi + 11", -(T)constants["Pi"] + 11);

    check<T>("(2)", 2);
    check<T>("(-2)", -2);
    check<T>("(e)", (T)constants["e"]);
    check<T>("(-e)", -(T)constants["e"]);

    check<T>("(e*2)+2", (T)constants["e"]* 2 + 2);
    check<T>("(e+2)+2", (T)constants["e"]+ 2 + 2);
    check<T>("e+(2)+2", (T)constants["e"]+ 2 + 2);
    check<T>("e+(2+2)", (T)constants["e"]+ 2 + 2);
    check<T>("e/(2)", (T)(constants["e"] / 2));
    check<T>("(2+e)/2", (T)((2 + constants["e"]) / 2));

    check<T>("1.5 + 1.5", (T)(1.5) + (T)(1.5));
    check<T>("1.511111", (T)(1.511111));
    check<T>("1.5 * 2", (T)(1.5) * 2);

    check<T>("2-+2", 0, true);
    check<T>("2++2", 0, true);
    check<T>("2 c 2", 0, true);
    check<T>("2 2", 0, true);
    check<T>("((2+2", 0, true);
    check<T>("(2)+2)", 0, true);
    check<T>("(2)+2/(2-2)", 0, true);
    check<T>(".2 + 2", 0, true);
    check<T>("(2 + 2", 0, true);
    check<T>(")2 + 2", 0, true);

    check<T>("2*+ 2", 0, true);
    check<T>("2+* 2", 0, true);
    check<T>("2..+* 2", 0, true);
}

/*
 * ======================================================================================
 * ======================================================================================
 * ======================================================================================
 */


int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Not enough arguments. Try: " << argv[0] << " <type> <expr>." << endl;
        cout << "Inner test begun..." << endl;
        check_calc<int>();
        check_calc<double>();
        check_calc<long>();
        return 0;
    }

    const char* type = argv[1];
    const char* text = argv[2];

    try
    {
        if(strcmp(type, "int") == 0)
        {
            Calculator<int, Parser<int>> calc;
            //cout << "Input text = " << text << endl;
            cout << calc.token_sequence(text) << endl;

        }
        else if(strcmp(type, "long") == 0)
        {
            Calculator<long, Parser<long>> calc;
            //cout << "Input text = " << text << endl;
            cout << calc.token_sequence(text) << endl;

        }
        else if(strcmp(type, "double") == 0)
        {
            Calculator<double, Parser<double>> calc;
            //cout << "Input text = " << text << endl;
            cout << calc.token_sequence(text) << endl;
        }
        else
        {
            throw UnknownType();
        }
    }
    catch(const CalculatorError& e)
    {
        std::cout << "During calculation runtime error occured: " << e.what() << std::endl;
        return -1;
    }
    catch (...)
    {
        std::cout << "Unknown error occured." << std::endl;
        return -2;
    }
    return 0;
}
