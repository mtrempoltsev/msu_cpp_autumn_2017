#include <iostream>
#include "Vector.cpp"
#include <vector>
#include "testing.cpp"

using std::cout;
using std::endl;

int main(void) {
    testParagraph("constructor");
    {
        startTest("empty");
        Vector<int> a;
        if (a.size() == 0) ok();
        else error();
        endTest();
    };
    {
        startTest("from size");
        Vector<int> a(3);
        cout << a.size() << endl;
        if (a.size() == 0) ok();
        else error();
        endTest();
    };
    {
        startTest("from size and def value");
        bool was_error = false;
        Vector<int> a(3, 321);
        for (int i = 0; i < 3; i++) {
            if (a[i] != 321) {
                was_error = true;
            }
        }
        if (was_error) error();
        else ok();
        endTest();
        startTest("get elem by index");
        if (a[2] == 321) ok();
        else error();
        endTest();
        startTest("change elem by index");
        a[2] = 111;
        if (a[2] == 111) ok();
        else error();
        endTest();
    };
    {
        startTest("copy constructor");
        Vector<int> a(3, 1);
        Vector<int> b(a);
        if (b[0] == 1 && b[1] == 1 && b[2] == 1 && b.size() == 3) ok();
        else error();
        endTest();
    };
    {
        startTest("move constructor");
        Vector<int> a(2, 1);
        Vector<int> b;
        b = std::move(a);
        if (b[0] == 1 && b[1] == 1 && b.size() == 2 && a.size() == 0) ok();
        else error();
        endTest();
    };
    testParagraph("methods");
    {
        startTest("test push_back");
        Vector<int> a;
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        a.push_back(1);
        if (a.size() != 12) error();
        else {
            bool was_error = false;
            for (int i = 0; i < 12; i++) {
                if (a[i] != 1) {
                    was_error = true;
                    break;
                }
            }
            was_error ? error() : ok();
        }
        endTest();
    };
    {
        startTest("test resize");
        Vector<int> a;
        bool was_error = false;
        try {
            a.resize(10);
            for (int i = 0; i < 10; i++) {
                a[i] = i;
            }
        } catch (...) {
            was_error = true;
        }
        was_error ? error() : ok();
        endTest();
    };
    {
        startTest("test empty + clear");
        Vector<int> a;
        if (a.empty()) {
            a.push_back(1);
            a.push_back(1);
            a.push_back(1);
            a.push_back(1);
            if (!a.empty()) {
                a.clear();
                if (a.empty()) {
                    ok(); 
                } else {
                    error();
                }
            } else {
                error();
            }
        } else {
            error();
        }
        endTest();
    };
    {
        startTest("pop back");
        Vector<int> a;
        a.push_back(1);
        if (a.size() == 1) {
            a.pop_back();
            if (a.empty()) {
                ok();
            } else error();
        } else error();
        endTest();
    };
    testParagraph("iterators");
    {
        startTest("iterator");
        Vector<int> a(10, 2);
        int cnt = 0;
        bool was_error = false;
        for (auto i : a) {
            if (i != 2) was_error = true;
            cnt++;
        }
        if (cnt != 10) was_error = true;
        was_error ? error() : ok();
        endTest();
    };
    {
        startTest("reverse iterator");
        Vector<int> a(3);
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        auto rbegin = a.rbegin();
        auto rend = a.rend();
        int ans = 3;
        bool was_error = false;
        while (rbegin != rend) {
            if (*rbegin != ans) {
                was_error = true;
            }
            ans--;
            rbegin++;
        }
        was_error ? error() : ok();
        endTest();
    };
    {
        startTest("iterator by index");
        Vector<int> a(3);
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        auto it = a.begin();
        int x = *(it + 1);
        if (x == 2) ok();
        else error();
        endTest();
    };
    {
        startTest("reverse iterator by index");
        Vector<int> a(3);
        a.push_back(1);
        a.push_back(2);
        a.push_back(3);
        auto it = a.rbegin();
        int x = *(it + 2);
        if (x == 1) ok();
        else error();
        endTest();
    };
    testResult();
    return 0;
}
