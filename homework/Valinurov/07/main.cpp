#include "calculator.cpp"

int main(int argc, char* argv[])
{
    if (argc < 2){
        std::cout << "format is ./calc string" << std::endl;
        return 1;
    }

    const char* text = argv[1];
    Calculator<double> calc(text);

    try
    {
        double result = calc.Expr();
        std::cout << result << std::endl;
    }
    catch (const char* ms){
        std::cout << ms << std::endl;
        return 1;
    }

    return 0;
}
