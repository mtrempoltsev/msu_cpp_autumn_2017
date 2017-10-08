#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;


void skip_spaces(const char *&s)
{
    while(isspace(*s)) {
        s++;
    }
}

int is_mult_op(const char *&s)
{
    return *s == '*' || *s == '/';
}

int is_add_op(const char *&s)
{
    return *s == '+' || *s == '-';
}

int get_prim(const char *&s, int &err)
{
    skip_spaces(s);
    int flag = 0;
    if (*s == '-') {
        flag = 1;
    }
    skip_spaces(s);
    char *t;
    long long int res = strtoll(s, &t, 0);
    if (flag) {
        res *= -1;
    }
    s = t;
    if (res > INT_MAX || res < INT_MIN) {
        err = 1;
        return 0;
    }

    skip_spaces(s);
    return res;
}

int get_term(const char *&s, int &err)
{
    int op1 = get_prim(s, err);
    if (err) {
        return 0;
    }
    while (is_mult_op(s)) {
        int flag = 0;
        if (*s == '/') {
            flag = 1;
        }
        int op2 = get_prim(s, err);
        if (err) {
            return 0;
        }
        if (flag) {
            if ((op1 != INT_MIN || op2 != -1) && op2) {
                op1 /= op2;
            } else if (op2 == 0){
                err = 2;
                return 0;
            } else {
                err = 1;
                return 0;
            }
        } else if (__builtin_mul_overflow(op1, op2, &op1)) {
            err = 1;
            return 0;
        }
    }
    return op1;
}

int get_expr(const char *&s, int &err)
{
    int op1 = get_term(s, err);
    if (err) {
        return 0;
    }
    while (is_add_op(s)) {
        int op2 = get_term(s, err);
        if (err) {
            return 0;
        }
        if (__builtin(op1, op2, &op1)) {
            err = 1;
            return 0;
        }
    }
    if (*s) {
        err = 3;
        return 0;
    }
    return op1;
}



int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Wrong format\n";
        return 0;
    }
    char error_desc[4][30] = {
        " ",
        "overflow",
        "zero divide",
        "incorrect input"
    };
    int err = 0;
    const char *t = argv[1];
    int ans = get_expr(t, err);
    if (err) {
        cout << error_desc[err];
    } else {
        cout << ans;
    }
    return 0;
}
