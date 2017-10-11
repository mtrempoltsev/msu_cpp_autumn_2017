#include <iostream>
#include <tuple>
#include <cstring>
#include <string>
#include <ctype.h>
#include <iomanip>
#include <map>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::map;

/*
 Grammar
 expr = (sum) | -(sum)
 sum = term + term | term - term | term
 term = prim * term | prim / term | expr * term | expr / term | prim | expr
 prim = number | -number | const
 number = [0-9]+
 const = pi | e
 */

class Expression {
public:
    Expression() {}
    Expression(string &s): expr(s), cur_pos(0), len(int(s.size())) {}
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
    double getValue() const {
        return result;
    }
private:
    string expr;
    double result;
    int cur_pos;
    int len;
    // delete space symbols from expr
    void deleteSpaces() {
        string res;
        for (int i = 0; i < expr.size(); i++) {
            if (!isspace(expr[i])) {
                res += expr[i];
            }
        }
        len = int(res.size());
        expr = res;
    }

    void throwError(string s) {
        throw s;
    }
    string UnexpectedSymbol (char unexpected, string expected) {
        string unexp;
        unexp += unexpected;
        unexp = "Unexpected symbol: " + unexp + " expected: " + expected;
        return unexp;
    }

    void checkBalance() {
        int balance = 0;
        for (int i = 0; i < expr.size(); i++) {
            if (expr[i] == '(') balance++;
            else if (expr[i] == ')') balance--;
            if (balance < 0) throwError("Error in brackets!");
        }
    }

    double exprValue() {
        double sign = 1;
        if (expr[cur_pos] == '-') {
            sign = -1;
            cur_pos++;
        }
        if (expr[cur_pos] != '(') throwError(UnexpectedSymbol(expr[cur_pos], "'('"));
        double sum_value = sumValue();
        if (expr[cur_pos] != ')') throwError(UnexpectedSymbol(expr[cur_pos], ")"));
        cur_pos++;
        return sum_value * sign;
    }
    double sumValue() {
        double value = 0;
        double cur_value;
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
    double termValue() {
        double value, cur_value;
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
    double primValue() {
        if (expr[cur_pos] == '-') {
            if (cur_pos + 1 == len) throwError(EndOfLine);
            cur_pos++;
            return -numberValue();
        } else if ('0' <= expr[cur_pos] && expr[cur_pos] <= '9') {
            return numberValue();
        } else return constValue();
    }

    // get number
    double numberValue() {
        double result = 0;
        while ('0' <= expr[cur_pos] && expr[cur_pos] <= '9' && cur_pos != len) {
            result *= 10;
            result += expr[cur_pos] - '0';
            cur_pos++;
        }
        return result;
    }

    // get constant
    double constValue() {
        string Const;
        while ((('a' <= expr[cur_pos] && expr[cur_pos] <= 'z') ||
               ('A' <= expr[cur_pos] && expr[cur_pos] <= 'Z')) && cur_pos != len) {
            Const += expr[cur_pos];
            cur_pos++;
        }
        if (consts.find(Const) == consts.end()) {
            throwError("Unkown constat: " + Const);
        } else {
            return consts[Const];
        }
        return 0;
    }
    static string EndOfLine;
    static map<string, double> consts;
};

string Expression::EndOfLine = "Unexpected end of line";
map<string, double> Expression::consts = {
    { "Pi", 3.14 },
    { "e", 2.7 }
};

int main(int argc, char **argv) {
    if (argc == 1 || strlen(argv[1]) == 0) {
        cerr << "Empty argument!" << endl;
        return 1;
    }
    
    string expr_str(argv[1]);
    // evaluate expression
    try {
        Expression expr(expr_str);
        expr.eval();
        cout << std::fixed << std::setprecision(5) << expr.getValue() << endl;
    } catch (std::string & s) {
        cerr << s << endl;
        return 1;
    }
    return 0;
}
