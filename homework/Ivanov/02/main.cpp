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
    int len = 0;
    while(str[end] >= '0' && str[end] <= '9' && end) {
        end--;
        len++;
    }
    for(int i = 0; i < len; i++) {
        number *= 10;
        number += str[end + i + 1] - '0';
    }
    return make_tuple(end, number);
}

tuple<int, double> prim(string& str, int end) {
    if(str[end] >= '0' && str[end] <= '9') {
        tuple<int, double> tmp = num(str, end);
        if(str[get<0>(tmp)] != '-') {
            return make_tuple(get<0>(tmp), get<1>(tmp));
        }
        if(unar(str, get<0>(tmp))) {
            return make_tuple(get<0>(tmp) - 1, -get<1>(tmp));
        } else {
            return make_tuple(get<0>(tmp), get<1>(tmp));
        }
    return make_tuple(get<0>(tmp), get<1>(tmp));
    }
}

tuple<int, double> term(string& str, int end) {
    tuple<int, double> tmp = prim(str, end);
    if(get<0>(tmp) == -1) {
        return make_tuple(get<0>(tmp), get<1>(tmp));
    }
    double left = get<1>(tmp);
    int before = get<0>(tmp);
    if(str[get<0>(tmp)] == '*') {
        tie(before, left) = term(str, get<0>(tmp) - 1);
        left *= get<1>(tmp);
    } else {
        if(str[get<0>(tmp)] == '/') {
            tie(before, left) = term(str, get<0>(tmp) - 1);
            left /= get<1>(tmp);
        }
    }
    return make_tuple(before, left);
}

double expr(string& str, int end) {
    int len = str.size();
    if(len == end) {
        return 0;
    }
    tuple<int, double> tmp = term(str, end);
    if(get<0>(tmp) == -1) {
        return get<1>(tmp);
    }
    if(str[get<0>(tmp)] == '+') {
        return expr(str, get<0>(tmp) - 1) + get<1>(tmp);
    } else {
        if(str[get<0>(tmp)] == '-') {
            return expr(str, get<0>(tmp) - 1) - get<1>(tmp);
        }
    }
}

int main(int argc, char *argv[]) {
    if(argc == 1 || strlen(argv[1]) == 0) {
        cout << "no arguments" << endl;
        return -1;
    }
    string str = "0";
    int len = strlen(argv[1]);
    for(int i = 0; i < len; i++) {
        if(!isspace(argv[1][i])) {
            str += argv[1][i];
        }
    }
    cout << setprecision(6) << expr(str, str.size() - 1) << endl;
    return 0;
}
