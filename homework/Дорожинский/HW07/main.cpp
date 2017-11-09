#include <iostream>
#include <stdexcept>
#include "Calculator.h"
#include "tests.h"

int main(int argc, char const *argv[]) {
    try {
        if (argc > 1) {
            Calculator<double> calc;
            std::cout << calc.calculate(argv[1]) << std::endl;
        } else {
            doTests();
        }
    } catch (const std::runtime_error& e) {
        std::cout << "During calculation error occured: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Unknown error occured" << std::endl;
        return 1;
    }
    
    return 0;
}