#include <iostream>
#include <string>
#include <tuple>
#include <ctype.h>
#include <iomanip>
#include <cstring>

using namespace std;
/*
    Grammar:
    expr = term | expr + term | expr - term
    term = prim | term * prim | term / prim
    prim = number | -number
    number = [0-9]+
*/

bool unar(string& str, int position) {
    if(position == 0) {
        return true;
    }
    if(str[position - 1] == '+' || str[position - 1] == '-' ||
        str[position - 1] == '*' || str[position - 1] == '/') {
        return true;
    }
    return false;
}

tuple<int, double> num(string& str, int end) {
    double number = 0;
    int pos = end;
    int cur_len = 0;
    while(isdigit(str[pos]) && pos >= 0) {
        pos--;
        cur_len++;
    }
    for(int i = 0; i < cur_len; i++) {
        number *= 10;
        number += str[pos + i + 1] - '0';
    }
    return make_tuple(pos, number);
}

tuple<int, double> prim(string& str, int end) {
    if(isdigit(str[end])) {
        tuple<int, double> tmp = num(str, end);
        if(str[get<0>(tmp)] != '-') {
            return make_tuple(get<0>(tmp), get<1>(tmp));
        }
        if(unar(str, get<0>(tmp))) {
            return make_tuple(get<0>(tmp) - 1, -get<1>(tmp));
        } else {
            return make_tuple(get<0>(tmp), get<1>(tmp));
        }
    } else {
        throw string("Error position: " + to_string(end) + " next char: " + str[end]);
    }
    return make_tuple(0, 0);
}

tuple<int, double> term(string& str, int end) {
    tuple<int, double> tmp = prim(str, end);
    if(get<0>(tmp) == -1) {
        return make_tuple(get<0>(tmp), get<1>(tmp));
    }
    int before = get<0>(tmp);
    double buf = get<1>(tmp);
    if(str[get<0>(tmp)] == '*') {
        tie(before, buf) = term(str, get<0>(tmp) - 1);
        buf *= get<1>(tmp);
    } else if(str[get<0>(tmp)] == '/') {
        tie(before, buf) = term(str, get<0>(tmp) - 1);
        if(get<1>(tmp) == 0) {
            throw string("Division by 0");
        }
        buf /= get<1>(tmp);
    }
    return make_tuple(before, buf);
}

double expr(string& str, int end) {
    int str_len = str.size();
    if(str_len == end) {
        return 0;
    }
    tuple<int, double> tmp = term(str, end);
    if(get<0>(tmp) == -1) {
        return get<1>(tmp);
    }
    if(str[get<0>(tmp)] == '+') {
        return expr(str, get<0>(tmp) - 1) + get<1>(tmp);
    } else if(str[get<0>(tmp)] == '-') {
        return expr(str, get<0>(tmp) - 1) - get<1>(tmp);
    } else {
        throw string("Error position: " + to_string(end) + " next char: " + str[get<0>(tmp)]);
    }
}

int main(int argc, char *argv[]) {
    if(argc == 1 || strlen(argv[1]) == 0) {
        cout << "no arguments" << endl;
        return -1;
    }
    string str = "";
    int len = strlen(argv[1]);
    for(int i = 0; i < len; i++) {
        if(!isspace(argv[1][i])) {
            str += argv[1][i];
        }
    }
    try {
        cout << setprecision(6) << expr(str, str.size() - 1) << endl;
    } catch(string& s) {
        cerr << s << endl;
        return 1;
    }
    return 0;
}
