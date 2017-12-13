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
        }
        catch (const invalid_argument& e) {
            std::cerr << "Input error: " << e.what() << '\n';
            error_while_processing = true;
        }
    }

    return error_while_processing ? -1 : 0;
}
