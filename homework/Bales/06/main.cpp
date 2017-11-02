#include "TCalculator.h"

/*
    TCalculator принимает в качестве шаблона --- тип, с которым работает парсер,
    а также тип, в котором будет осуществляться вычисление выражения
    Т.е. если TCalculator<int> будет работать с целочисленным типом, 
    и выражение "2.5" преобразует к типу int => "2"
*/

int main(int argc, char* argv[]) {
    if (argc != 2)
        return static_cast<int>(TExitCode::INCORRECT_PARAMS);
    if (TCalculator<double>::IsValidExpr(argv[1])) {
        std::cout << TCalculator<double>::ToCalculate(argv[1]) << std::endl;
    }
    else {
        return static_cast<int>(TExitCode::INCORRECT_INPUT);
    }
    return 0;
}