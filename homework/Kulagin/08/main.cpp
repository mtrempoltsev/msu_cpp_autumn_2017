#include "src/Vector.cpp"
#include <iostream>

using namespace std;


void is_ok(bool expr, std::string msg = "") {
    if (expr) {
        cout << "ok - " << "'" << msg << "'" << endl;
    } else {
        cout << "not ok - " << "'" << msg << "'; " << "\n\tgot: " << expr << endl;
    }
}

void check_constructors() {
    Vector<int> v1 = { 1, 2, 3 };
    is_ok(v1.size() == 3, "v1.size() == 3");
    is_ok(v1[0] == 1, "v1[0] == 1");
    is_ok(v1[1] == 2, "v1[1] == 2");
    is_ok(v1[2] == 3, "v1[2] == 3");

    Vector<int> v2;
    is_ok(v2.size() == 0, "vec2.size() == 0");

    Vector<double> v3 = {3.14, 2.7};
    is_ok(v3.size() == 2, "v3.size() == 2");
    is_ok(v3[0] == 3.14, "v3[0] == 3.14");
    is_ok(v3[1] == 2.7,  "v3[1] == 2.7");
    v3[0] = 1.7;
    is_ok(v3[0] == 1.7,  "v3[0] == 1.7");
}

void check_push_pop() {
    Vector<int> v;

    for (int i = 0; i < 5; i++) {
        v.push_back(i);
    }

    is_ok(v.size() == 5, "v.size() == 5");

    for (int i = 0; i < 5; i++) {
        is_ok((int)v[i] == i, "v[" + std::to_string(i) + "] == i");
    }

    int i = 5;

    while (!v.empty()) {
        v.pop_back();

        i--;

        is_ok((int)v.size() == i, "v.size() == " + std::to_string(i));
    }

    is_ok(v.size() == 0, "v.size() == 0");
    is_ok(v.empty(), "v.empty()");
}

void check_iterators() {
    Vector<int> v = { 1, 2, 3};

    int i = 1;

    for (auto it = v.begin(); it != v.end(); ++it) {
        is_ok(*it == i, "*it == " + std::to_string(i));
        i++;
    }

    i = 3;

    for (auto it = v.rbegin(); it != v.rend(); ++it) {
        is_ok(*it == i, "*it == " + std::to_string(i));
        i--;
    }
}

int main(int argc, char** argv) {
    check_constructors();
    check_push_pop();
    check_iterators();

    return 0;
}
