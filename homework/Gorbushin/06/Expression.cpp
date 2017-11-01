#include <iostream>
#include <tuple>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <map>

using namespace std;

/*
 Grammar
 expr = (sum) | -(sum)
 sum = term + term | term - term | term
 term = prim * term | prim / term | expr * term | expr / term | prim | expr
 prim = number | -number | const
 number = [0-9]+
 const = pi | e
 */

// Class for checking the same typenames
template <class T1, class T2>
struct IsSame {
    static constexpr bool result = false;
};

template <class T>
struct IsSame<T, T> {
    static constexpr bool result = true;
};

// Class for type max min info
template <class T>
struct MyTypeInfo {};

// For int type
template<>
struct MyTypeInfo<int> {
    static constexpr int min = -2147483648;
    static constexpr int max = 2147483647;
};

// For long type
template<>
struct MyTypeInfo<long> {
    static constexpr long min = int64_t(-9223372036854775808ull);
    static constexpr long max = int64_t(9223372036854775807);
};

// For double type
template<>
struct MyTypeInfo<double> {
    static constexpr double min = -1.79769e+308;
    static constexpr double max = 1.79769e+308;
};

// Int parse
class IntParser {
public:
    // Return the next position in string, and the result of parsing
    static std::pair<int, int> parse(std::string &s, int start_pos) {
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
                std::cerr << "Error while parsing int type, the input is too big!" << std::endl;
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

// Long parse
class LongParser {
public:
    // Return the next position in string, and the result of parsing
    static std::pair<int, long> parse(std::string &s, int start_pos) {
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

// Double parse
class DoubleParser {
public:
    // Return the next position in string, and the result of parsing
    static std::pair<int, double> parse(std::string &s, int start_pos) {
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
    // Return the value, that parsed and the next position
    static std::pair<int, T> parse(std::string &s, int start_pos) {
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
class Expression {
public:
    // Empty constructor
    Expression() {}

    // Constructor by std::string - expression for eval
    Expression(std::string &s): expr(s), cur_pos(0), len(int(s.size())) {}
    
    // Calculate the expression, store the answer in result variable
    void eval() {
        deleteSpaces();
        checkBalance();
        // turn around expession to brackets
        if (!(expr[0] == '(' && expr[len] == ')')) {
            expr = "(" + expr + ")";
            len += 2;
        }
        result = exprValue();
    }

    // Getter for get answer
    T getValue() const {
        return result;
    }

private:
    std::string expr;
    T result;
    int cur_pos;
    int len;

    // delete space symbols from expr
    void deleteSpaces() {
        std::string res;
        for (int i = 0; i < expr.size(); i++) {
            if (!isspace(expr[i])) {
                res += expr[i];
            }
        }
        len = int(res.size());
        expr = res;
    }

    // throw error by std::string
    void throwError(std::string s) {
        throw s;
    }
    
    // Get error message about unexpected symbol
    std::string UnexpectedSymbol (char unexpected, std::string expected) {
        std::string unexp;
        unexp += unexpected;
        unexp = "Unexpected symbol: " + unexp + " expected: " + expected;
        return unexp;
    }

    // check the brackets balance of expression
    void checkBalance() {
        int balance = 0;
        for (int i = 0; i < expr.size(); i++) {
            if (expr[i] == '(') balance++;
            else if (expr[i] == ')') balance--;
            if (balance < 0) throwError("Error in brackets!");
        }
    }

    // Get expr value (look at grammar)
    T exprValue() {
        T sign = 1;
        if (expr[cur_pos] == '-') {
            sign = -1;
            cur_pos++;
        }
        if (expr[cur_pos] != '(') throwError(UnexpectedSymbol(expr[cur_pos], "'('"));
        T sum_value = sumValue();
        if (expr[cur_pos] != ')') throwError(UnexpectedSymbol(expr[cur_pos], ")"));
        cur_pos++;
        return sum_value * sign;
    }

    // Get sum value (look at grammar)
    T sumValue() {
        T value = T();
        T cur_value;
        bool isBracketStart = false;
        if (expr[cur_pos] == '(') {
            isBracketStart = true;
            cur_pos++;
        }
        // get first term
        value = termValue();
        while (cur_pos < len) {
            if (expr[cur_pos] == '-' || expr[cur_pos] == '+') {
                bool wasMinus = (expr[cur_pos] == '-') ? true : false;
                if (cur_pos + 1 == len) throwError(EndOfLine);
                cur_pos++;

                // start to get all others terms, look to grammar
                cur_value = termValue();

                if (wasMinus) value -= cur_value;
                else value += cur_value;
            } else if (expr[cur_pos] == ')' && isBracketStart) {
                break;
            } else throwError(UnexpectedSymbol(expr[cur_pos], "'+' or '-' or ')'"));
        }
        return value;
    }

    //get term token
    T termValue() {
        T value, cur_value;
        // retrive first prim or expr
        if (expr[cur_pos] == '-') {
            if (cur_pos + 1 == len) throwError(EndOfLine);
            if (expr[cur_pos + 1] == '(') {
                value = exprValue();
            } else {
                value = primValue();
            }
        } else if (expr[cur_pos] == '(') {
            value = exprValue();
        } else {
            value = primValue();
        }
        
        // end if end of line
        if (cur_pos == len) return value;
        while (cur_pos < len) {
            if (expr[cur_pos] == '*' || expr[cur_pos] == '/') {
                bool isMult = (expr[cur_pos] == '*') ? true : false;
                cur_pos++;
                
                // start get prim or expr           
                if (expr[cur_pos] == '-') {
                    if (cur_pos + 1 == len) throwError(EndOfLine);
                    if (expr[cur_pos + 1] == '(') cur_value = exprValue();
                    else cur_value = primValue();
                } else if (expr[cur_pos] == '(') cur_value = exprValue();
                else cur_value = primValue();
                
                if (isMult) value *= cur_value;
                else {
                    if (cur_value == 0) {
                        throwError("Zero division!");
                    }
                    value /= cur_value;
                }
                    
                
            } else return value;
        }
        return value;
    }

    // get prim
    T primValue() {
        int pos = cur_pos;
        if (expr[cur_pos] == '-') {
            if (cur_pos + 1 == len) throwError(EndOfLine);
            pos++;
        }
        if ('0' <= expr[pos] && expr[pos] <= '9') {
            return numberValue();
        } else return constValue();
    }

    // get number
    T numberValue() {
        T result = T();
        std::tie(cur_pos, result) = Parser<T>::parse(expr, cur_pos);
        return result;
    }

    // get constant
    T constValue() {
        if (!IsSame<T, double>::result) {
            throwError("Try to use constant in no-double type");
            return T();
        }
        double sign = 1;
        if (expr[cur_pos] == '-') {
            sign = -1;
            cur_pos++;
        }
        std::string Const;
        while ((('a' <= expr[cur_pos] && expr[cur_pos] <= 'z') ||
               ('A' <= expr[cur_pos] && expr[cur_pos] <= 'Z')) && cur_pos != len) {
            Const += expr[cur_pos];
            cur_pos++;
        }
        if (consts.find(Const) == consts.end()) {
            throwError("Unkown constat: " + Const);
        } else {
            return consts[Const] * sign;
        }
        return 0;
    }

    static std::string EndOfLine;
    static std::map<std::string, double> consts;
};

template <class T>
std::string Expression<T>::EndOfLine = "Unexpected end of line";

template <class T>
std::map<std::string, double> Expression<T>::consts = {
    { "Pi", 3.14 },
    { "e", 2.7 }
};
