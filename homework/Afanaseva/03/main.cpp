#include <iostream>
#include <exception>

#include "calculator.h"
using namespace std;

int main(int argc, char* argv[])
{
    Calculator calc;

    if (argc < 2)
    {
        cout << "Not enough arguments. Try: " << argv[0] << " <expr>." << endl;
        cout << "Inner test begun..." << endl;
        check_calc();
        return 0;
    }

    const char* text = argv[1];

    try
    {
        //cout << "Input text = " << text << endl;
        cout << calc.token_sequence(text) << endl;
    }
    catch(char const* msg)
    {
        std::cout << endl << "Exception message: " << msg << std::endl;
        return -2;
    }
    return 0;
}
