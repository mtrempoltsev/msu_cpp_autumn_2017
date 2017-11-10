#include "parser.h"
#include <iostream>
#include <unordered_map>
const char *message = "Usage: calc \"(5 + 3 * (8 / Pi) * 4.3) + (1)\"";
std::unordered_map<std::string, double> constants = {
    {"Pi", 3.14}, {"e", 2.7},
};
int main(int argc, char *argv[]) {
    if (argc == 2) {
        double result = 0;
        Parser<double> parser(argv[1], constants);
        try {
            result = parser.calculate();
        } catch (const std::runtime_error &error) {
            std::cout << message << std::endl;
            std::cerr << error.what() << std::endl;
            return -1;
        }
        std::cout << result << std::endl;

        return 0;
    } else {
        std::cout << message << std::endl;
        return -2;
    }
}
