#include <iostream>
#include <fstream>
#include "testing.cpp"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

const int MAX_TESTS = 200;

void make_test() {
    if (!fork()) {
        execl("./make_test", "./make_test", "input_test", "output_test", NULL);
    }
    wait(NULL);
}

void execute() {
    if (!fork()) {
        execl("./count", "./count", "input_test", "output", NULL);
    }
    wait(NULL);
}

bool get_diff(std::string true_output, std::string my_output) {
    std::ifstream true_stream(true_output), my_stream(my_output);
    while (true_stream.good()) {
        std::string true_s, my_s;
        if (!my_stream.good()) {
            std::cout << "End of file, test is not end!" << std::endl;
            return false;
        }
        getline(true_stream, true_s);
        getline(my_stream, my_s);
        if (true_s != my_s) {
            std::cout << "Bad answer, true: " << true_s << " get: " << my_s << std::endl;
            return false;
        }
    }
    if (my_stream.good()) {
        std::cout << "Test program has some lines, true output is end!" << std::endl;
        return false;
    }
    return true;
}

int main(void) {
    testParagraph("Good test");
    for (int i = 1; i <= MAX_TESTS; i++) {
        startTest("Test #" + std::to_string(i));
        make_test();
        execute();
        endTest();
        if (!get_diff("output_test", "output")) {
            error();
            return 1;
        } else ok();
    }
    testResult();
    return 0;
}
