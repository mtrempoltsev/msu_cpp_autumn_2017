// Vasilii Bodnariuk

#include <iostream>
#include <string>

#include "calc.hpp"
#include "type_definer.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    bool error_while_processing = false;
    if(argc != 2) {
        error_while_processing = true;
        cout << "usage:" << '\n';
        cout << argv[0] << " expression" << '\n';
        cout << "example:" << '\n';
        cout << argv[0] << " \"-12 * 2 / 3 + 8 * 2 / 1\"" << '\n';
    } else {
        auto data = argv[1];
        auto calc = Calc<CALC_TYPE>();

        try {
            auto result = calc.calculate(data);
            cout << result << '\n';
        } catch(errors e) {
            switch (e) {
                case ERR_ZERO_DIV:
                    cout << "Zero division error!" << '\n';
                    break;
                case ERR_UNBALANCED_PAR:
                    cout << "Parentheses unbalanced!" << '\n';
                    break;
                case ERR_BAD_STRUCTURE:
                    cout << "The program processes an arithmetic expression of integers!" << '\n';
                    break;
                case ERR_LIMITS_ABUSE:
                    cout << "The number is too big!" << '\n';
                    break;
            }
            error_while_processing = true;
        }
    }

    return error_while_processing ? -1 : 0;
}
