// Vasilii Bodnariuk

#include <unordered_map>

#include <math.h>
#include <iostream>
#include <string>

#include <limits>

#include <stdexcept>      // std::invalid_argument
using namespace std;

extern std::unordered_map<std::string, double> contants;

enum errors {
    ERR_ZERO_DIV = 0,
    ERR_UNBALANCED_PAR,
    ERR_BAD_STRUCTURE,
    ERR_LIMITS_ABUSE,
};

std::unordered_map<errors, string> error_text = {
   { ERR_ZERO_DIV, "zero division" },
   { ERR_UNBALANCED_PAR, "arentheses unbalanced" },
   { ERR_BAD_STRUCTURE, "not an arithmetic expression of integers" },
   { ERR_LIMITS_ABUSE, "type restrictions abused" },

};

std::unordered_map<std::string, double> constants =
    {
       { "Pi", 3.14 },
       { "e", 2.7 }
    };

// strategy
template <class T>
class Parser
{
public:
    T parse(char* data, int start, int len);
};

template <typename T>
class Calc {
private:
    char* _data;
    bool _binary_operator;
    int _expr_level;
    int _end_pointer;
    Parser<T> parser;

    void binary_operator_test();

    int skip_blanks(int start);
    T number(int start, int len);
    T term(int start, int len, bool last_mult);
    T expression(int start, bool last_plus);
    T p_expr(int start, int len);

public:
    T calculate(char* data);
};

int digit(char c) {
    return int(c) - '0';
}

int skip_blanks(char* data, int start) {
    while(data[start] == ' ') {
        ++start;
    }

    return start;
}

// property template
template <typename T>
struct NumericTraits
{
};

template <>
struct NumericTraits<int>
{
    static constexpr auto last_min = std::numeric_limits<int>::min() / 10;
    static constexpr auto last_max = std::numeric_limits<int>::max() / 10;
};

template <>
struct NumericTraits<long>
{
    static constexpr auto last_min = std::numeric_limits<long>::min() / 10;
    static constexpr auto last_max = std::numeric_limits<long>::max() / 10;
};

template <>
struct NumericTraits<double>
{
    static constexpr auto last_min = -std::numeric_limits<double>::max() / 10;
    static constexpr auto last_max = std::numeric_limits<double>::max() / 10;
};


template<typename T>
T Parser<T>::parse(char* data, int start, int len) {
    T accumulator = 0;
    int i = skip_blanks(data, start);
    bool negative = data[i] == '-';
    if (negative) {
        ++i;
        i = skip_blanks(data, i);
    }

    if(i == len) {
        throw invalid_argument(error_text[ERR_BAD_STRUCTURE]);
    }

    switch (data[i]) {
        case 'e':
            return constants["e"];
        case 'P':
            if(data[i + 1] == 'i') {
                return constants["Pi"];
            }
    }

    bool overflow = false;
    while(i < len && data[i] != ' ') {
        overflow = NumericTraits<T>::last_max <= accumulator;
        overflow |= NumericTraits<T>::last_min >= accumulator;
        if(data[i] >= '0' && data[i] <= '9') {
            accumulator = 10 * accumulator + digit(data[i]);
            ++i;
        } else {
            throw invalid_argument(error_text[ERR_BAD_STRUCTURE]);
        }

    }

    if(overflow) {
        throw invalid_argument(error_text[ERR_LIMITS_ABUSE]);
    }

    if(data[i] == ' ') {
        if (skip_blanks(data, i) < len) {
            throw invalid_argument(error_text[ERR_BAD_STRUCTURE]);
        }
    }

    auto result = negative ? -accumulator : accumulator;

    return result;
}

template<typename T>
T Calc<T>::calculate(char* data) {
    _data = data;
    _expr_level = 0;
    _end_pointer = 0;

    auto result = expression(0, true);
    if(_data[_end_pointer] != '\0') {
        throw invalid_argument(error_text[ERR_UNBALANCED_PAR]);
    }
    return result;
}

template<typename T>
int Calc<T>::skip_blanks(int start) {
    while(_data[start] == ' ') {
        ++start;
    }

    return start;
}
template<typename T>
T Calc<T>::p_expr(int start, int len) {
    start = skip_blanks(start);
    while(_data[len - 1] == ' ' && len > 0) {
        --len;
    }
    if(_data[start] == '(' && _data[len - 1] == ')') {
        return expression(start + 1, true);
    } else {
        return number(start, len);
    }
}
template<typename T>
T Calc<T>::number(int start, int len) {
    return parser.parse(_data, start, len);
}
template<typename T>
T Calc<T>::term(int start, int len, bool last_mult) {
    _binary_operator = true;
    start = skip_blanks(start);
    int i = start;

    int p_level = 0;
    while(i < len) {
        switch (_data[i]) {
            case '(':
                ++p_level;
                break;
            case ')':
                --p_level;
                break;
            case '*':
            case '/':
                if(p_level == 0){
                    binary_operator_test();
                    double tail = term(i + 1, len, _data[i] == '*');
                    if((_data[i] == '/') == last_mult) {
                        double result = p_expr(start, i) / tail;
                        if(isinf(result)) {
                            throw invalid_argument(error_text[ERR_ZERO_DIV]);
                        }
                        return result;
                    }
                    else {
                        return p_expr(start, i) * tail;
                    }
                }
        }
        ++i;
        i = skip_blanks(i);
        _binary_operator = false;
    }

    return p_expr(start, len);
}
template<typename T>
T Calc<T>::expression(int start, bool last_plus) {
    _binary_operator = true;
    start = skip_blanks(start);
    int i = start;
    int p_level = 0;
    bool looping;
    bool close_par = false;

    do {
        switch (_data[i]) {
            case '-':
                if(_binary_operator) {
                    break;
                }
            case '+':
                if(p_level == 0){
                    binary_operator_test();
                    double tail = expression(i + 1, _data[i] == '+');
                    if((_data[i] == '-') == last_plus) {
                        tail = - tail;
                    }
                    auto result = term(start, i, true) + tail;
                    return result;
                }
            case '*':
            case '/':
                binary_operator_test();
                break;
            case '(':
                if(close_par) {
                    throw invalid_argument(error_text[ERR_BAD_STRUCTURE]);
                }
                ++p_level;
                break;
            case ')':
                --p_level;
                break;
            default:
                _binary_operator = false;
        }

        looping = (_data[i] != '\0') && !(_data[i] == ')' && p_level == -1);
        if(looping) {
            close_par = _data[i] == ')';
            ++i;
            i = skip_blanks(i);
        }
    } while(looping);


    if(_data[i] == '\0' && p_level != 0) {
        throw invalid_argument(error_text[ERR_UNBALANCED_PAR]);
    }

    if(i > _end_pointer) {
        _end_pointer = i;
    }

    return term(start, i, true);
}
template<typename T>
void Calc<T>::binary_operator_test() {
    if(_binary_operator) {
        throw invalid_argument(error_text[ERR_BAD_STRUCTURE]);
    }
    _binary_operator = true;
}
