#include <iostream>
#include <string>

int bad = 0;
int N = 1;
string s;

void startTest(string name) {
    s = name;
    if (N == 1) std::cout << "===========================================" << std::endl;
    std::cout << "Start test: " << N << " - " << s << std::endl;
    N++;
}

void endTest() {
    std::cout << "End test: " << N - 1 << std::endl;
    std::cout << "===========================================" << std::endl;
}

void ok() {
    std::cout << s << " -- OK" << std::endl;
}

void error() {
    bad++;
    std::cout << s << " -- ERROR" << std::endl;
}

void testResult() {
    N--;
    std::cout << (N - bad) << " / " << N << " passed" << std::endl;
}

void testParagraph(string p) {
    std::cout << "==============[" << p << "]==============" << std::endl;
}
