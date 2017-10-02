#include "calculator.h"
const char* message = "Usage: calc \"2 + 3 * 4 - -2\"";

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << message << endl;
        return -1;
    }
    if (argc == 2) {
        const char* input = argv[1];
        cout << parse_expression(input) << endl;

        return 0;
    } else {
        cout << message << endl;
        cerr << "Incorrect arguments\n";
        exit(1);
    }
}
