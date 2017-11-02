#include <iostream>
#include <string>
#include <tuple>
#include <ctype.h>
#include <iomanip>
#include <cstring>
#include <unordered_map>

using namespace std;
/*
    Grammar:
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | -number
    number = [0-9]+
*/

unordered_map<string, double> contants =
{
    { "Pi", 3.14 },
    { "e", 2.7 }
};

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
    double get_num() const {
        return result;
    }
private:
    string str;
    double result;
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
    double value() {
        double sign = 1;
        if(str[pos] == '-') {
            sign = -1;
            pos++;
        }
        if(str[pos] != '(') {
            throw string(unknownSymbol(str[pos], "("));
        }
        double buf = 0;
        double cur_value;
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
    double term() {
        double buf, cur_value;
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
    double prim() {
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
                auto it = contants.find(buf);
                if(it == contants.end()) {
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
            auto it = contants.find(buf);
            if(it == contants.end()) {
                throw string("unknown constat: " + buf);
            }
            return it->second;
        }
    }
    double num() {
        double result = 0;
        while(isdigit(str[pos]) && pos != len) {
            result *= 10;
            result += str[pos] - '0';
            pos++;
        }
        return result;
    }
};

int main(int argc, char **argv) {
    if(argc == 1 || strlen(argv[1]) == 0) {
        cout << "no arguments" << endl;
        return -1;
    }
    if(strlen(argv[1]) == 2 && argv[1][0] == '-' && argv[1][1] == '0') {
        cout << 0 << endl;
        return 0;
    }
    string str(argv[1]);
    try {
        calc expr(str);
        expr.calculation();
        cout << setprecision(6) << expr.get_num() << endl;
    } catch (string & s) {
        cerr << s << endl;
        return 1;
    }
    return 0;
}
