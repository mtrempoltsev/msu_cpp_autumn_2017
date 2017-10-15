// Vasilii Bodnariuk

#include <unordered_map>

extern std::unordered_map<std::string, double> contants;

enum errors {
    ERR_ZERO_DIV = 0,
    ERR_UNBALANCED_PAR,
    ERR_BAD_STRUCTURE,
};

class Calc {
private:
    int test_str();
    double expression(int start, bool last_plus);
    int skip_blanks(int start);
    double number(int start, int len);
    double term(int start, int len, bool last_mult);

    void binary_operator_test();

    char* _data;
    bool _binary_operator;
    int _expr_level;

public:
    double calculate(char* data);
};

int digit(char c);
