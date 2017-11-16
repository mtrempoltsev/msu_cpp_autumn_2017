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
    catch (std::invalid_argument e){
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}
