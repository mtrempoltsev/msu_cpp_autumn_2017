#include "parser.h"
#include <iostream>
#include <unordered_map>
const char *message = "Usage: calc \"(5 + 3 * (8 / Pi) * 4.3) + (1)\"";
std::unordered_map<std::string, double> constants = {
    {"Pi", 3.14}, {"e", 2.7},
};
int main(int argc, char *argv[]) {
    if (argc == 1) {
        std::cout << message << std::endl;
        return -1;
    }
    if (argc == 2) {

        Parser<double> parser(argv[1], constants);
        std::cout << parser.calculate() << std::endl;

        return 0;
    } else {
        std::cout << message << std::endl;
        std::cerr << "Incorrect arguments\n";
        exit(1);
    }
}
