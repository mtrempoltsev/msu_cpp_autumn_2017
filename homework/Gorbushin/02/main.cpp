#include <iostream>
#include <tuple>
#include <cstring>
#include <string>
#include <ctype.h>
#include <iomanip>

using std::cout;
using std::cerr;
using std::endl;
using std::string;

std::tuple<int, double> getNumber(string &, int);
std::tuple<int, double> getPrim(string &, int);
std::tuple<int, double> getTerm(string &, int);
double getExpr(string &, int);

/*
    Grammar
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | -number
    number = [0-9]+
*/


// getExpr - return value of expression written in {str} from 0 to {end_pos}
double getExpr(string & str, int end_pos) {
    int pos, str_len = str.size();
    double right_value;

    // Value of empty string is 0    
    if (str_len == end_pos) return 0;

    //get right term (look to grammar) and receive the index before this term (pos)
    std::tie(pos, right_value) = getTerm(str, end_pos);

    //return if term is first 
    if (pos == -1) {
        return right_value;
    }

    // look to grammar
    if (str[pos] == '+') {
        return getExpr(str, pos - 1) + right_value;
    } else if (str[pos] == '-') {
        return getExpr(str, pos - 1) - right_value;
    } else {
        return right_value;
    }
}

// getTerm - return value of term and return the index before this term
std::tuple<int, double> getTerm(string & str, int end_pos) {
    int pos;
    double right_value;
    // look to grammar
    std::tie(pos, right_value) = getPrim(str, end_pos);
    
    // return if term is first
    if (pos == -1) {
        return std::make_tuple(pos, right_value);
    }

    double left_value = right_value;
    int pos_before_term = pos;
    // look to grammar
    if (str[pos] == '*') {
        std::tie(pos_before_term, left_value) = getTerm(str, pos - 1);
        left_value *= right_value;
    } else if (str[pos] == '/') {
        std::tie(pos_before_term, left_value) = getTerm(str, pos - 1);
        if (right_value == 0) {
            string error = "Zero division!";
            throw error;
        }
        left_value /= right_value;
    }

    return std::make_tuple(pos_before_term, left_value);
}

// isUnaryMinus dedect if the symbol str[pos] is unary minus, the
// truth of this function follows from grammar
bool isUnaryMinus(string & str, int pos) {
    if (pos == 0) return true;
    if (str[pos - 1] == '-' || 
        str[pos - 1] == '+' ||
        str[pos - 1] == '*' ||
        str[pos - 1] == '/') return true;

    return false;
}

// getPrim - return value of prim and return the index before this prim
std::tuple<int, double> getPrim(string & str, int end_pos) {
    int pos;
    double value;

    // up to grammar here should be only digit
    if ('0' <= str[end_pos] && str[end_pos] <= '9') {
        std::tie(pos, value) = getNumber(str, end_pos);
        if (str[pos] != '-') return std::make_tuple(pos, value);
        
        if (isUnaryMinus(str, pos)) return std::make_tuple(pos - 1, -value);
        else return std::make_tuple(pos, value);
    } else {
        std::string error = "Error is expr, position: " + std::to_string(end_pos) + " find next char: ";
        error += str[end_pos];
        error += " expected [0-9] or -";
        throw error;
    }

    return std::make_tuple(pos, value);
}

// getNumber - return value of number and return the index before this number
std::tuple<int, double> getNumber(string & str, int end_pos) {
    double number = 0;
    int pos = end_pos;
    int num_len = 0;
    while ('0' <= str[pos] && str[pos] <= '9' && pos >= 0) {
        pos--;
        num_len++;
    }
    for (int i = 0; i < num_len; i++) {
        number *= 10;
        number += str[pos + i + 1] - '0';
    }
    return std::make_tuple(pos, number);
}

int main(int argc, char **argv) {
    if (argc == 1 || strlen(argv[1]) == 0) {
        cerr << "Empty argument!" << endl;
        return 1;
    }

    string no_space_expr = "";
    int len = strlen(argv[1]);

    // delete space symbols from input string
    for (int i = 0; i < len; i++) {
        if (!isspace(argv[1][i])) {
            no_space_expr += argv[1][i];
        }
    }

    // evaluate expression
    try {
        cout << std::fixed << std::setprecision(5) << getExpr(no_space_expr, no_space_expr.size() - 1) << endl;
    } catch (std::string & s) {
        cerr << s << endl;
        return 1;   
    }
    return 0;
}
