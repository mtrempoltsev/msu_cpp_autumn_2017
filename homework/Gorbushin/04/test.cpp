#include <iostream>
#include <vector>
#include "matrix.h"
#include <string>
#include <unistd.h>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int bad = 0;
int N = 1;
string s;

void startTest(string name) {
    s = name;
    if (N == 1) cout << "===========================================" << endl;
    cout << "Start test: " << N << " - " << s << endl;
    N++;
}

void endTest() {
    cout << "End test: " << N - 1 << endl;
    cout << "===========================================" << endl;
}

void ok() {
    cout << s << " -- OK" << endl;
}

void error() {
    bad++;
    cout << s << " -- ERROR" << endl;
}

void testResult() {
    N--;
    cout << (N - bad) << " / " << N << " passed" << endl;
}

int main(void) {

    Matrix m(3, 4);

    startTest("do m[0][1] = 4");
    m[0][1] = 4;

    if (m[0][1] == 4) {
        ok();
    } else {
        error();
    }
    endTest();

    startTest("do double x = m[0][1]");
    double x = m[0][1];
    if (x == 4) {
        ok();
    } else {
        error();
    }
    endTest();

    startTest("compare two equal matrix");
    Matrix p(2, 2);
    p[0][0] = 1;
    p[0][1] = 2;
    p[1][0] = 3;
    p[1][1] = 4;

    Matrix p_copy(2, 2);
    p_copy[0][0] = 1;
    p_copy[0][1] = 2;
    p_copy[1][0] = 3;
    p_copy[1][1] = 4;

    if (p == p_copy && m != p) {
        ok();
    } else {
        error();
    }
    endTest();

    startTest("assignment");
    m = p;
    if (m == p_copy) {
        ok();
    } else {
        error();
    }
    endTest();

    startTest("multiply by number");
    m *= 5;
    if (m[0][0] == 5 && m[0][1] == 10 && m[1][0] == 15 && m[1][1] == 20) {
        ok();
    } else {
        error();
    }
    endTest();

    startTest("multiply by std::vector");
    vector<double> v = { 3, 5 };
    m *= v;
    if (m[0][0] == 65 && m[1][0] == 145) {
        ok();
    } else {
        error();
    }
    endTest();

    startTest("catch bad index bound");
    if (!fork()) {
        m[123123][12312] = 121;
        return 0;
    } else {
        int status;
        wait(&status);
        if (WTERMSIG(status) == 6) { // abort
            ok();
        } else {
            error();
        }
    }
    endTest();

    testResult();
    return 0;
}
