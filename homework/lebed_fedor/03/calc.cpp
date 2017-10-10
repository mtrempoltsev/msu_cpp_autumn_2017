#include <iostream>
#include <stdio.h>
#include <unordered_map>
#include <string>
#include "parsing.cpp"
#include "parsing_error.cpp"

void print_usage() {
    std::cout << "usage: parse \"expression\"" << std::endl;
}

// expects expression in argv[1]
// if not present prints usage
// if expression is valid prints it's result
// else prints diagnostic message
// NOTE: newline in expression messes up diagnostic message
int main(int argc, char *argv[])
{
    if (argc != 2) {
        print_usage();
        return 1;
    }

    std::unordered_map<std::string, double> constants {
        { "Pi", 3.1415 }, { "e", 2.7182 }
    };

    try {
        Parser parser(argv[1], constants);
        std::cout << parser.value() << std::endl;
    }
    catch (ParsingError e) {
        print_parsing_error(argv[1], e.point, e.msg);
        return 1;
    }
    return 0;
}
