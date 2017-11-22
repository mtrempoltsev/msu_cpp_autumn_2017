#include <iostream>

#include "freq_dictionary.hpp"

int main(int argc, char** argv) {
    try {
        FreqDictionary dict(argv[1], argv[2]);
        dict.make_dictionary();
        dict.sort_dictionary();
        dict.print_dictionary();

    } catch (std::exception& err) {
        std::cout << "Error: " << err.what() << std::endl;
        return 1;
    } catch (...) {
        std::cout << "Something wrong." << std::endl;
        return 1;
    }
    return 0;
}
