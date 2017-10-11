#include <iostream>
#include <cctype>
#include <cstdlib>
#include <climits>
#include <unordered_map>
using namespace std;


unordered_map<string, double> constants =
{
    { "Pi", 3.14 },
    { "e", 2.7 }
};

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


class Calc
{
public:

    const char *s;
    int err;

    Calc(const char *t, int a)
    {
        s = t;
        err = a;
    }

    int get_prim()
    {
        skip_spaces(s);
        int flag = 0;

        if (*s == '+') {
            s++;
        }
        if (*s == '-') {
            flag = 1;
            s++;
        }

        skip_spaces(s);
        if (*s == '(') {
            s++;
            int k = get_expr(1);
            if (flag) {
                if (k == INT_MAX) {
                    err = 1;
                    return 0;
                } else {
                    k *= -1;
                }
            }
            return k;
        }

        char *t;
        if (*s == 'P' && *(s + 1) == 'i') {
            s += 2;
            skip_spaces(s);
            int k = constants["Pi"];
            if (flag) {
                k *= -1;
            }
            return k;
        }
        if (*s == 'e') {
            s += 1;
            skip_spaces(s);
            int k = constants["e"];
            if (flag) {
                k *= -1;
            }
            return k;
        }
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

    int get_term()
    {
        skip_spaces(s);
        int op1 = 0;
        op1 = get_prim();
        //cout << op1 << '\n';
        if (err) {
            return 0;
        }
        skip_spaces(s);
        while (is_mult_op(s)) {
            int flag = 0;
            if (*s == '/') {
                flag = 1;
            }
            s++;
            int op2 = get_prim();
            //cout << op2 << '\n';
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

    int get_expr(int flag)
    {
        int op1 = get_term();
        if (err) {
            return 0;
        }
        while (is_add_op(s)) {
            int op2 = get_term();
            if (err) {
                return 0;
            }
            if (__builtin_add_overflow(op1, op2, &op1)) {
                err = 1;
                return 0;
            }
        }
        if (flag) {
            if (*s == ')') {
                s++;
                skip_spaces(s);
                return op1;
            } else {
                err = 3;
                return 0;
            }
        }
        if (*s) {
            err = 3;
            return 0;
        }
        return op1;
    }

private:

};









int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "Wrong format\n";
        return 0;
    }
    char error_desc[4][30] = {
        " ",
        "overflow\n",
        "zero divide\n",
        "incorrect input\n"
    };
    const char *t = argv[1];
    //const char *t = "2+(2)";
    Calc str = Calc(t, 0);
    int ans = str.get_expr(0);
    if (str.err) {
        cout << error_desc[str.err];
    } else {
        cout << ans;
    }
    cout << '\n';
    return 0;
}
