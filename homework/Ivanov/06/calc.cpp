#include <iostream>
#include <string>
#include <tuple>
#include <ctype.h>
#include <iomanip>
#include <cstring>
#include <unordered_map>
#include <limits>
#include <math.h>

using namespace std;
/*
    Grammar:    
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | -number
    number = [0-9]+
*/

template <class T1, class T2>
struct IsSame {
    static constexpr bool result = false;
};

template <class T>
struct IsSame<T, T> {
    static constexpr bool result = true;
};

template <class T>
struct MyTypeInfo {};

template<>
struct MyTypeInfo<int> {
    static constexpr int min = numeric_limits<int>::min();
    static constexpr int max = numeric_limits<int>::max();
};

template<>
struct MyTypeInfo<long> {
    static constexpr long min = numeric_limits<long>::min();
    static constexpr long max = numeric_limits<long>::max();
};

template<>
struct MyTypeInfo<double> {
    static constexpr double min = numeric_limits<double>::min();
    static constexpr double max = numeric_limits<double>::max();
};

class IntParser {
public:
    static pair<int, int> parse(string &s, size_t start_pos) {
        long long result = 0;
        long long sign = 1;
        if (s[start_pos] == '-') {
            sign = -1;
            start_pos++;
        }
        while (start_pos < s.size() && '0' <= s[start_pos] && s[start_pos] <= '9') {
            result *= 10;
            result += s[start_pos] - '0';
            if (result * sign > MyTypeInfo<int>::max) {
                cerr << "Error while parsing int type, the input is too big!" << endl;
                break;
            } else if (result * sign < MyTypeInfo<int>::min) {
                std::cerr << "Error while parsing int type, the input is too small!" << std::endl;
                break;
            }
            start_pos++;
        }
        return std::make_pair(start_pos, result * sign);
    }
};

class LongParser {
public:
    static std::pair<int, long> parse(std::string &s, size_t start_pos) {
        double result = 0;
        double sign = 1;
        if (s[start_pos] == '-') {
            sign = -1;
            start_pos++;
        }
        while (start_pos < s.size() && '0' <= s[start_pos] && s[start_pos] <= '9') {
            result *= 10;
            result += s[start_pos] - '0';
            if (result * sign > MyTypeInfo<long>::max) {
                std::cerr << "Error while parsing long type, the input is too big!" << std::endl;
                break;
            } else if (result * sign < MyTypeInfo<long>::min) {
                std::cerr << "Error while parsing long type, the input is too small!" << std::endl;
                break;
            }
            start_pos++;
        }
        return std::make_pair(start_pos, result * sign);
    }
};

class DoubleParser {
public:
    static std::pair<int, double> parse(std::string &s, size_t start_pos) {
        long double result = 0;
        bool was_dot = false;
        long double power = 1;
        long double sign = 1;
        if (s[start_pos] == '-') {
            sign = -1;
            start_pos++;
        }
        while (start_pos < s.size() && (('0' <= s[start_pos] && s[start_pos] <= '9') || s[start_pos] == '.')) {
            if (s[start_pos] == '.') {
                if (was_dot) {
                    std::cerr << "Wrong number written by double type" << std::endl;
                    break;
                } else {
                    was_dot = true;
                }
            } else {
     
                if (was_dot) power /= 10.0;

                long double to_add = (s[start_pos] - '0');
                if (was_dot) to_add *= power;
                else result *= 10.0;
                
                result += to_add;

                if (result * sign > MyTypeInfo<double>::max) {
                    std::cerr << "Error while parsing double type, the input is too big!" << std::endl;
                    break;
                } else if (result * sign < MyTypeInfo<double>::min) {
                    std::cerr << "Error while parsing double type, the input is too small!" << std::endl;
                    break;
                }
            }
            start_pos++;
        }
        return std::make_pair(start_pos, result * sign);
    }
};

template <class T>
class Parser {
public:
    static std::pair<int, T> parse(std::string &s, size_t start_pos) {
        if (IsSame<T, int>::result) {
            return IntParser::parse(s, start_pos);
        } else if (IsSame<T, long>::result) {
            return LongParser::parse(s, start_pos);
        } else if (IsSame<T, double>::result) {
            return DoubleParser::parse(s, start_pos); 
        } else {
            std::cerr << "Unknown type in Parser" << std::endl;
            return std::make_pair(T(), start_pos);
        }
    }
};

template <class T>
class calc {
public:
    calc() {}
    calc(string &s): str(s), pos(0), len(s.length()) {}
    void calculation() {
        checkSpaces();
        checkBracket();
        if(!(str[0] == '(' && str[len] == ')')) {
            str = "(" + str + ")";
            len += 2;
        }
        result = value();
    }
    T get_num() const {
        return result;
    }
private:
    string str;
    T result;
    int pos;
    int len;

    string unknownSymbol(char unknown, string expected) {
        string unexp;
        unexp += unknown;
        unexp = "unknown symbol: " + unexp + " expected: " + expected;
        return unexp;
    }
    void checkSpaces() {
        string ans = "";
        for(int i = 0; i < len; i++) {
            if(!isspace(str[i])) {
                ans += str[i];
            }
        }
        len = str.length();
        str = ans;
    }
    void checkBracket() {
        int balance = 0;
        int cur_len = str.length();
        for(int i = 0; i < cur_len; i++) {
            if(str[i] == '(') {
                balance++;
            }
            if(str[i] == ')') {
                balance--;
            }
            if(balance < 0) {
                throw string("Error in brackets");
            }
        }
    }

    T value() {
        T sign = 1;
        if(str[pos] == '-') {
            sign = -1;
            pos++;
        }
        if(str[pos] != '(') {
            throw string(unknownSymbol(str[pos], "("));
        }
        T buf = T();
        T cur_value;
        bool flag = false;
        if(str[pos] == '(') {
            flag = true;
            pos++;
        }
        buf = term();
        while(pos < len) {
            if(str[pos] == '-' || str[pos] == '+') {
                bool unar;
                if(str[pos] == '-') {
                    unar = true;
                } else {
                    unar = false;
                }
                if(pos + 1 == len) {
                    throw string("unknown end of line");
                }
                pos++;
                cur_value = term();
                if(!unar) {
                    buf += cur_value;
                } else {
                    buf -= cur_value;
                }
            } else if(str[pos] == ')' && flag) {
                break;
            } else {
                throw string(unknownSymbol(str[pos], "sign or bracket"));
            }
        }
        if(str[pos] != ')') {
            throw string(unknownSymbol(str[pos], ")"));
        }
        pos++;
        return buf * sign;
    }

    T term() {
        T buf, cur_value;
        if(str[pos] == '-') {
            if(pos + 1 == len) {
                throw string("unknown end of line");
            }
            if(str[pos + 1] == '(') {
                buf = value();
            } else {
                buf = prim();
            }
        } else if(str[pos] == '(') {
            buf = value();
        } else {
            buf = prim();
        }
        if(pos == len) {
            return buf;
        }
        while(pos < len) {
            if(str[pos] == '*' || str[pos] == '/') {
                bool flag;
                if(str[pos] == '*') {
                    flag = true;
                } else {
                    flag = false;
                }
                pos++;

                if(str[pos] == '-') {
                    if(pos + 1 == len) {
                        throw string("unknown end of line");
                    }
                    if(str[pos + 1] == '(') {
                        cur_value = value();
                    } else {
                        cur_value = prim();
                    }
                } else if(str[pos] == '(') {
                    cur_value = value();
                } else {
                    cur_value = prim();
                }

                if(flag) {
                    buf *= cur_value;
                } else {
                    if(cur_value == 0) {
                        throw string("Division by 0");
                    }
                    buf /= cur_value;
                }
            } else {
                return buf;
            }
        }
        return buf;
    }

    T prim() {
        if(str[pos] == '-') {
            if(pos + 1 == len) {
                throw string("unknown end of line");
            }
            pos++;

            if(isdigit(str[pos])) {
                return -num();
            } else {
                string buf;
                while(isalpha(str[pos]) && pos != len) {
                    buf.push_back(str[pos]);
                    pos++;
                }
                auto it = math_const.find(buf);
                if(it == math_const.end()) {
                    throw string("unknown constat: " + buf);
                }
                return -it->second;
            }
        } else if(isdigit(str[pos])) {
            return num();
        } else {
            string buf;
            while(isalpha(str[pos]) && pos != len) {
                buf.push_back(str[pos]);
                pos++;
            }
            auto it = math_const.find(buf);
            if(it == math_const.end()) {
                throw string("unknown constat: " + buf);
            }
            return it->second;
        }
    }
    T num() {
        T result = T();
        tie(pos, result) = Parser<T>::parse(str, pos);
        return result;
    }
    static unordered_map<string, double> math_const;
};

template <class T>
unordered_map<string, double> calc<T>::math_const = {
    { "Pi", M_PI },
    { "e", M_E }
};