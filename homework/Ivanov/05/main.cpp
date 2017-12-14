/*#include <iostream>
#include "matrix.h"

void check(bool value)
{
    if (!value)
        std::cout << "error" << std::endl;
}

void checkGetSet()
{
    Matrix m(2, 3);
    m[0][0] = 1;
    m[0][1] = 2;
    m[0][2] = 3;
    m[1][0] = 4;
    m[1][1] = 5;
    m[1][2] = 6;
    
    check(m[0][0] == 1);
    check(m[0][1] == 2);
    check(m[0][2] == 3);
    check(m[1][0] == 4);
    check(m[1][1] == 5);
    check(m[1][2] == 6);
    
    m[1][2] = 100; 
    
    check(m[1][2] == 100);
}

int
main()
{
	checkGetSet();
	Matrix m1(3, 3), m2(3, 3);
	m1[0][0] = 1; m2[0][0] = 1;
	m1[0][1] = -100; m2[0][1] = -100;
	if (m1 != m2) {
		std::cout << "error2" << std::endl;
	}
	std::vector<double> d1 = {100, 500, -1000};
	std::vector<double> d2 = {0.1, 1.5436, 5.6574};
	(m1 *= d1) *= d2;
	(m2 *= 0.4) *= -500;
	return 0;
}*/

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

    bool was_error = false;
    startTest("test template");
    Matrix<long long> ll_m(5, 5);
    long long ll_num = 1e18;
    for (int i = 0; i < 5; i++) {
        ll_m[i][i] = ll_num;
    }
    for (int i = 0; i < 5; i++) {
        if (ll_m[i][i] != ll_num) {
            error();
        }
    }
    if (!was_error) { 
        Matrix<char> char_m(1, 10);
        for (int i = 0; i < 10; i++) {
            char_m[0][i] = 'a';
        }

        for (int i = 0; i < 10; i++) {
            if (char_m[0][i] != 'a') {
                error();
            }
        }
        ok();
    }
    endTest();

    startTest("move tests");
    was_error = false;
    Matrix<int> from_move(2, 2);
    from_move[0][0] = 1;
    from_move[0][1] = 2;
    from_move[1][0] = 3;
    from_move[1][1] = 4;
    Matrix<int> to_move;

    to_move = std::move(from_move);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (to_move[i][j] != 2 * (i + 1) + (j + 1)) {
                was_error = false;
                break;
            }
        }
        if (was_error) break;
    }
    if (was_error) {
        error();
    } else {
        ok();
    }
    endTest();

    Matrix<double> m(3, 4);

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
    Matrix<double> p(2, 2);
    p[0][0] = 1;
    p[0][1] = 2;
    p[1][0] = 3;
    p[1][1] = 4;

    Matrix<double> p_copy(2, 2);
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

    startTest("catch bad index bound exception");
    was_error = false;
    try {
        m[123123][12312] = 121;
    } catch (string &s) {
        was_error = true;
        std::cerr << s;
    }
    if (was_error) {
        ok();
    } else {
        error();
    }
    endTest();

    testResult();
    return 0;
}
