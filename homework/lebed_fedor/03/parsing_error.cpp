#include <iostream>

// terminal constants setup font color
enum class Color
{
    Red = 35,
    Green = 32
};

// terminal control sequence to setup font color
void change_color(Color c) {
    std::cerr << "\033[" << int(c)   << "m";
}

// terminal control sequence to reset font color to normal
void reset_color() {
    std::cerr << "\033[0m";
}

// prints mark symbol to highlight error
void print_mark(int idx) {
    while (idx--) {
        std::cerr << ' ';
    }
    std::cerr << '^' << std::endl;
}

// prints parsing error and diagnostic information
void print_parsing_error(const char *str, const char *mark, const char *error) {
    change_color(Color::Red);
    std::cerr << "Erorr: ";
    reset_color();

    std::cerr << error << std::endl;
    std::cerr << str << std::endl;

    change_color(Color::Green);
    print_mark(mark-str);
    reset_color();
}
