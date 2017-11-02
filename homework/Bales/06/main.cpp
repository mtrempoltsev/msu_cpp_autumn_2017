#include "TCalculator.h"

/*
    TCalculator принимает в качестве шаблона --- тип, с которым работает парсер,
    а также тип, в котором будет осуществляться вычисление выражения
    Т.е. если TCalculator<int> будет работать с целочисленным типом, 
    и выражение "2.5" преобразует к типу int => "2"
*/

void check(bool pred) {
    if (!pred) {
        std::cerr << "Was happened error!" << std::endl;
    }
}

void CheckIntParses() {
    const char* expr = "5.0 + 3 - 4.0";
    check(TCalculator<int>::IsValidExpr(expr));
    std::cout << "CheckIntParses is ended." << std::endl;
}

void CheckDoubleParses() {
    const char* expr = "5.2 + 3 / Pi - 4.2 * e";
    check(TCalculator<double>::IsValidExpr(expr));
    std::cout << "CheckDoubleParses is ended." << std::endl;
}

void CheckLongParses() {
    const char* expr = "2147483650 + 3";
    check(TCalculator<long>::IsValidExpr(expr));
    std::cout << "CheckLongParses is ended." << std::endl;
}

void FailedIntParserForLong() {
    const char* expr = "2147483650 + 3";
    check(!TCalculator<int>::IsValidExpr(expr));    
    std::cout << "FailedIntParserForLong is ended." << std::endl;
}

void FailedIntParserForDouble() {
    const char* expr = "4.5 + 3.1";
    check(!TCalculator<int>::IsValidExpr(expr));    
    std::cout << "FailedIntParserForDouble is ended." << std::endl;
}

int main(int argc, char* argv[]) {
    CheckIntParses();
    CheckLongParses();
    CheckDoubleParses();
    FailedIntParserForDouble();
    FailedIntParserForLong();
    return 0;
}