#include <iostream>
#include "Calculator.h"

int main(int argc, char* argv[]) {
    Calculator calc;

    const char* text = "Ee";


    if (argc == 1)
    {
        std::cout << "Empty input!"  << std::endl;
        return -1;
    }
    text = argv[1];

    std::cout<<"INPUT: "<<text<<std::endl;

    try
    {
        int res = calc.calculate(text);
        std::cout<<res<<std::endl;
    }
    catch (std::exception& ex)
    {
        std::cout<<ex.what()<<std::endl;
        return -1;
    }



    return 0;
}
