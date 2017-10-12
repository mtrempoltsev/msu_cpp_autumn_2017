#include "TCalculator.h"

int main(int argc, char* argv[]) {
    if (argc != 2)
        return static_cast<int>(TExitCode::INCORRECT_PARAMS);
    try {
        std::cout << TCalculator::ToCalculate(argv[1]) << std::endl;
    }
    catch (ExitCodeException ex) {
        std::cerr << ex.what() << std::endl;
        return static_cast<int>(ex.GetExitCode());
    }

    return 0;
}