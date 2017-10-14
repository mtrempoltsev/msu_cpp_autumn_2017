// Vasilii Bodnariuk

#include <unordered_map>

// std::unordered_map<std::string, double> contants =
//     {
//         { "Pi", 3.14 },
//         { "e", 2.7 }
//     };

enum errors {
    ERR_ZERO_DIV = 0,
    ERR_UNKNOWN_SYMBOL,
    ERR_BAD_STRUCTURE,
};

class Calc {
private:
    int test_str();
    double expression(int start, bool last_plus);
    int skip_blanks(int start);
    int number(int start, int len);
    double term(int start, int len, bool last_mult);

    void binary_operator_test();

    char* _data;
    bool _binary_operator;

public:
    double calculate(char* data);
};

int digit(char c);
