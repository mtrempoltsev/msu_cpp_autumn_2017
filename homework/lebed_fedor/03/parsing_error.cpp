#include <iostream>

// terminal constants setup font color
enum class Color
{
    Red = 35,
    Green = 32
};

// terminal control sequence to setup font color
void change_color(Color c) {
    std::cout << "\033[" << int(c)   << "m";
}

// terminal control sequence to reset font color to normal
void reset_color() {
    std::cout << "\033[0m";
}

// prints mark symbol to highlight error
void print_mark(int idx) {
    while (idx--) {
        std::cout << ' ';
    }
    std::cout << '^' << std::endl;
}

// prints parsing error and diagnostic information
void print_parsing_error(const char *str, const char *mark, const char *error) {
    change_color(Color::Red);
    std::cout << "Erorr: ";
    reset_color();

    std::cout << error << std::endl;
    std::cout << str << std::endl;

    change_color(Color::Green);
    print_mark(mark-str);
    reset_color();
}
