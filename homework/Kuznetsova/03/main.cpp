#include "calculator.h"
const char* message = "Usage: calc \"(5 + 3 * (8 / Pi) * 4) + (1)\"";
unordered_map<string, double> constants = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << message << endl;
        return -1;
    }
    if (argc == 2) {
        
        Parser parser(argv[1], constants);
        cout << parser.calculate() << endl;

        return 0;
    } else {
        cout << message << endl;
        cerr << "Incorrect arguments\n";
        exit(1);
    }
}
