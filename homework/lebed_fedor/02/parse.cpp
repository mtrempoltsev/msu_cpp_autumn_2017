#include <iostream>
#include <stdio.h>
#include "parsing.h"
#include "parsing_error.h"

void print_usage() {
    std::cout << "usage: parse \"expression\"" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        print_usage();
        return 1;
    }

    try {
        int value = calc_parse(argv[1]);
        std::cout << value << std::endl;
    }
    catch (ParseError err) {
        print_parsing_error(err, argv[1]);
    }
    return 0;
}
