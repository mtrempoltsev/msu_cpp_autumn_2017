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

    int get_prim(int op_allowed)
    {
        skip_spaces(s);
        int m_flag = 0;
        if (op_allowed == 2) {
            if (*s == '+') {
                s++;
                skip_spaces(s);
                if (*s == '-') {
                    m_flag = 1;
                    s++;
                    skip_spaces(s);
                }

            } else if (*s == '-') {
                m_flag = 1;
                s++;
                skip_spaces(s);
                if (*s == '-') {
                    m_flag = 0;
                    s++;
                    skip_spaces(s);
                }
            }

        } else {
            if (*s == '-') {
                m_flag = 1;
                s++;
                skip_spaces(s);
            }
        }
        if (*s == '(') {
            s++;
            int k = get_expr(1);
//            if (err) {
//                return 0;
//            }
            if (m_flag) {
                if (k == INT_MAX) {
                    err = 1;
                    exit(1);
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
            if (m_flag) {
                k *= -1;
            }
            return k;
        }
        if (*s == 'e') {
            s += 1;
            skip_spaces(s);
            int k = constants["e"];
            if (m_flag) {
                k *= -1;
            }
            return k;
        }
        if (!isdigit(*s)) {
            err = 3;
            exit(1);
        }
        long long int res = strtoll(s, &t, 0);
        if (m_flag) {
            res *= -1;
        }
        s = t;
        if (res > INT_MAX || res < INT_MIN) {
            err = 1;
            exit(1);
        }

        skip_spaces(s);
        return res;
    }

    int get_term(int flag)
    {
        skip_spaces(s);
        int op1 = 0;
        op1 = get_prim(flag);
        //cout << op1 << '\n';
//        if (err) {
//            return 0;
//        }
        skip_spaces(s);
        while (is_mult_op(s)) {
            int flag = 0;
            if (*s == '/') {
                flag = 1;
            }
            s++;
            int op2 = get_prim(1);
            //cout << op2 << '\n';
//            if (err) {
//                return 0;
//            }
            if (flag) {
                if ((op1 != INT_MIN || op2 != -1) && op2) {
                    op1 /= op2;
                } else if (op2 == 0){
                    err = 2;
                    exit(1);
                } else {
                    err = 1;
                    exit(1);
                }
            } else if (__builtin_mul_overflow(op1, op2, &op1)) {
                err = 1;
                exit(1);
            }
        }
        return op1;
    }

    int get_expr(int flag)
    {
        int op1 = get_term(1);
//        if (err) {
//            return 0;
//        }
        while (is_add_op(s)) {
            int op2 = get_term(2);
//            if (err) {
//                return 0;
//            }
            if (__builtin_add_overflow(op1, op2, &op1)) {
                err = 1;
                exit(1);
            }
        }
        if (flag) {
            if (*s == ')') {
                s++;
                skip_spaces(s);
                return op1;
            } else {
                err = 3;
                exit(1);
            }
        }
        if (*s) {
            err = 3;
            exit(1);
        }
        return op1;
    }

private:

};


//All exceptions are now ending with exit(1) instead of error_desk print, but err variable is
//still in code for fast refactoring it to see, what issue did you get





int main(int argc, char *argv[])
{
    if (argc != 2) {
        //cout << "Wrong format\n";
        exit(1);
    }
    char error_desc[4][30] = {
        " ",
        "overflow",
        "zero divide",
        "incorrect input"
    };
    const char *t = argv[1];
    //const char *t = "2+(2)";
    Calc str = Calc(t, 0);
    int ans = str.get_expr(0);
//    if (str.err) {
//        cout << error_desc[str.err];
//    } else {
//        cout << ans;
//    }
    cout << ans << '\n';
    return 0;
}

