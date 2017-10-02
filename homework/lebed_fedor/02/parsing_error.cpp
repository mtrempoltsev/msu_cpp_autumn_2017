#include <iostream>
#include "parsing_error.h"

enum class Color {
    Red = 35,
    Green = 32
};

static const char *token_type_str(Token::Type tp) {
    static const char *t2n[] = { "operation", "number", "EOF" };
    return t2n[tp];
}

static void change_color(Color c) {
    std::cout << "\033[" << int(c)   << "m";
}

static void reset_color() {
    std::cout << "\033[0m";
}

static void print_mark(int idx) {
    while (idx--) {
        std::cout << ' ';
    }
    std::cout << '^' << std::endl;
}

void print_parsing_error(ParseError err, const char *str) {
    change_color(Color::Red);
    std::cout << "Erorr: ";
    reset_color();

    std::cout << token_type_str(err.first) << " expected" << std::endl;
    std::cout << str << std::endl;

    change_color(Color::Green);
    print_mark(err.second-str);
    reset_color();
}
