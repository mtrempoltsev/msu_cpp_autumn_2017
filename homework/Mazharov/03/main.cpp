#include <iostream>
#include "Calculator.h"
/* Использованная грамматика:
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | - number | + number
    number = [0-9]
 */

int main(int argc, char *argv[]) {
    char *text;

    //проверка числа аргументов
    if (argc < 2) {
        std::cout << "Error: input expression expected" << std::endl;
        return 1;
    } else {
        text = argv[1];
    }

    //разбор по грамматике начинается с всеобъемлеющего expr
    try {
        Calculator calc = Calculator(text);
        std::cout << calc.expr() << std::endl;
    }
    catch (const char *str) {
        std::cout << str << std::endl;
        return 1;
    }
    return 0;
}