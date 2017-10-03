#include "calculator.h"
const char* message = "Usage: calc \"2 + 3 * 4 - -2\"";

int main() {
    int n = 0;
    const char* input1 = "2 + 3 * 4 - -6/2";
    const char* input2 = "8 - 6 / 2 * -2";
    const char* input3 = "2/0";
    const char* input4 = "abcde";
    const char* input5 = "2 ** 2"; 

    cout << "Select number:" << endl;
    cout << "1) " << input1 << endl;
    cout << "2) " << input2 << endl;
    cout << "3) " << input3 << endl;
    cout << "4) " << input4 << endl;
    cout << "5) " << input5 << endl;

    cin >> n;

    switch (n) {
        case 1:
            cout << "input: " << input1 << endl;
            cout << parse_expression(input1) << endl;
            break;
        case 2:
            cout << "input: " << input2 << endl;
            cout << parse_expression(input2) << endl;
            break;
        case 3:
            cout << "input: " << input3 << endl;
            cout << parse_expression(input3) << endl;
            break;
        case 4:
            cout << "input: " << input4 << endl;
            cout << parse_expression(input4) << endl;
            break;
        case 5:
            cout << "input: " << input5 << endl;
            cout << parse_expression(input5) << endl;
            break;

        default:
            break;
    }
    return 0;
}
