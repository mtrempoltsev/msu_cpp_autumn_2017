#include <iostream>
#include <stdio.h>

// implemented in parsing.cpp
int calc_parse(const char *&str);
// implemented in parsing_error.cpp
void print_parsing_error(const char *str, const char *mark, const char *error);

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

    const char *p = argv[1];
    try {
        int value = calc_parse(p);
        std::cout << value << std::endl;
    }
    catch (const char *err) {
        print_parsing_error(argv[1], p, err);
        return 1;
    }
    return 0;
}
