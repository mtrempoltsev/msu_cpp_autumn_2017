#include <iostream>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <cassert>

enum class Token
{
    Invalid,
    Minus,
    Plus,
    Star,
    Slash,
    Number,
    Opening_Parenthesis,
    Closing_Parenthesis,
    Constant,
    End
};

std::unordered_map<std::string, double> constants = {
    { "Pi", 3.14 },
    { "e", 2.7 }
};

template<class T>
class Parser{};

template<>
class Parser<int>
{
    public:
    static int parse(const char*& text)
    {
        auto c = *text;
        int number = 0,
                 i = 1,                   //degree of 10
                 j = 1;                   //degree of the number
        while (c <= '9' && c >= '0')
        {
            number += i * static_cast<int>(c - '0');
            c = *--text;                               //read number from right to left
            i *= 10;
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            ++text;                               //set the pointer after the last digit
        }
        if (number > std::numeric_limits<int>::max() || number < std::numeric_limits<int>::min())
        {
            throw "Wrong size of int!";
        }
        return number;
    }
};
template<>
class Parser<long>
{
    public:
    static long parse(const char*& text)
    {
        auto c = *text;
        long number = 0,
                 i = 1,                   //degree of 10
                 j = 1;                   //degree of the number
        while (c <= '9' && c >= '0')
        {
            number += i * static_cast<int>(c - '0');
            c = *--text;                               //read number from right to left
            i *= 10;
            j++;
        }
        for (int k = 0; k < j; k++)
        {
            ++text;                               //set the pointer after the last digit
        }
        if (number > std::numeric_limits<long>::max() || number < std::numeric_limits<long>::min())
        {
            throw "Wrong size of long!";
        }
        return number;
    }
};
template<>
class Parser<double>
{
    public:
    static double parse(const char*& text)
    {
        auto c = *text;
        double number = 0;
        int i = 1,                   //degree of 10
            j = 1,                   //degree of the number
            k = 1;                   //number of digits after the dot
        bool is_point = false;
        while (c <= '9' && c >= '0' || c == '.')
        {
            if (c!='.')
            {
                number += i * static_cast<int>(c - '0');
                c = *--text;
                i *= 10;
                j++;
            }
            else
            {
                c = *--text;
                if (!is_point)
                {
                    k = j;
                    is_point = true;
                }
                else
                {
                    throw "Wrong expression!";
                }
            }
        }
        for (int n = 1; n < k; n++)
        {
            number /= 10;
        }
        for (int m = 0; m < j; m++)
        {
            ++text;                               //set the pointer after the last digit
        }
        if (k != 1)
        {
            ++text;
        }
        if (number > std::numeric_limits<double>::max() || number < std::numeric_limits<double>::min())
        {
            throw "Wrong size of double!";
        }
        return number;
    }
};

template<class T>
class Tokenizator
{
public:
    Tokenizator (const char*& str): text(str) {}
    Token getToken()
    {
        while(const auto c = *text++)
        {
            switch(c)
            {
                case '-': return Token::Minus;
                case '+': return Token::Plus;
                case '*': return Token::Star;
                case '/': return Token::Slash;
                case '(': return Token::Opening_Parenthesis;
                case ')': return Token::Closing_Parenthesis;
                case 'e': return Token::Constant;
                case ' ': continue;
            }
            if (c >= '0' && c <= '9')
            {
                // number recognition
                bool is_second_digit = false;
                for (auto c = *text; c >= '0' && c <= '9' || c == '.'; ++text)
                {
                    if (c != '.') is_second_digit = true;
                    c = *text;
                }
                --text;
                if (is_second_digit) --text;
                return Token::Number;
            }
            if (c == 'P')
            {
                // Pi recognition
                if (*text == 'i')
                {
                    return Token::Constant;
                }
            }
            return Token::Invalid;
        }
        return Token::End;
    }
    T getNumber()
    {
        return Parser<T>::parse(text);
    }

    T getConstant()
    {
         // obtaining constants
            auto c = *--text;
            text++;
            T result = 0;
            if (c == 'e')
            {
                result = constants["e"];
            }
            else if (c == 'P')
            {
                text++;
                result = constants["Pi"];
            }
            return result;
    }
private:
    const char* text;
};

template<class T>
class Calculator
{
public:
    Calculator(const char*& str):tokenizator(str)
    {
        brackets = 0;
        operation = Token::Plus;
    }
    T processingExpressions()
    {
	    T result = processingTerms();
	    while (operation != Token::End)
	    {
	        if (operation == Token::Plus)
            {
                result += processingTerms();
            }
	        else if (operation == Token::Minus)
            {
                result -= processingTerms();
            }
            else if (operation == Token::Closing_Parenthesis)
            {
                if (brackets == 0)
                {
                    throw "Wrong expression!";
                }
                brackets--;
                break;
            }
            else
            {
                 throw "Wrong expression!";
            }
	    }
	    return result;
    }

private:
    int brackets;                 // number of uncapped parentheses
    Token operation;
    Tokenizator<T> tokenizator;

    T processingPrimitives()
    {
        // get number or constant from tokenizator, implements unary minus and parses parentheses
        auto token = tokenizator.getToken();
        if (token == Token::Number)
        {
            return tokenizator.getNumber();
        }
        else if (token == Token::Constant)
        {
            return tokenizator.getConstant();
        }
        else if (token == Token::Minus)
        {
            return -processingPrimitives();
        }
        else if (token == Token::Opening_Parenthesis)
        {
            brackets++;
            return processingExpressions();
        }
        else
        {
            throw "Wrong expression!";
        }
    }
    T processingTerms()
    {
        T result = processingPrimitives();
        operation = tokenizator.getToken();
        if (operation == Token::Invalid)
        {
            throw "Wrong expression!";
        }
        while (operation == Token::Star || operation == Token::Slash || operation == Token::Number)
        {
            if (operation == Token::Star)
            {
                result *= processingPrimitives();
            }
            else if (operation == Token::Slash)
            {
                T prim = processingPrimitives();
                if (prim != 0)
                {
                    result /= prim;
                }
                else
                {
                    throw "Division by zero!";
                }
            }
		    else
            {
                throw "Wrong expression!";
            }
            operation = tokenizator.getToken();
	    }
        return result;
    }
};

template<class T>
void testing(const char* text, T answer)
{
    Calculator<T> calc(text);
    try
    {
        T result = calc.processingExpressions();
        if (fabs(result - answer) > 1e-9)
        {
            std::cout << "Test " << text << " failed" << std::endl;
            assert(!"Wrong answer!");
        }
    }
    catch(const char* error)
    {
        std::cout << "Test " << text << " failed" << std::endl;
        assert(error);
    }
}

void doTests()
{
    testing<int>("2", 2);
    testing<int>("2 + 2", 4);
    testing<int>("-2", -2);
    testing<int>("-2 - 2", -4);
    testing<int>("100 + 1", 101);
    testing<int>("(2 + 3) * 4 - -(2)", 22);
    testing<int>("8 - 6 * 2 / 2", 2);
    testing<int>("8 - 6 / 2 * 2", 2);
    testing<int>("8 - 6 / 2 * -2", 14);

    testing<long>("8 - --2", 6);
    testing<long>("6 / 3 * 3", 6);
    testing<long>("8 / 4 / 2", 1);

    testing<double>("-2", -2);
    testing<double>("-2.4", -2.4);
    testing<double>("21.33", 21.33);
    testing<double>("Pi + e", 5.84);
    testing<double>("1.5 + 1.5", 3);
    testing<double>("--( 2 + 3) * 4 - -e", 22.7);
    testing<double>("((2.0 + Pi) - 3.0) * (4.0 - -2.0)", 12.84);

    std::cout << "All tests passed successfully" << std::endl;
    std::cout << std::endl;
}
int main(int argc, char* argv[])
{
    doTests();

    if (argc < 2){
        std::cout << "Wrong format!" << std::endl;
        return 1;
    }

    const char* text = argv[1];
    Calculator<double> calc(text);
    try
    {
        std::cout << calc.processingExpressions() << std::endl;
    }
    catch(const char* error)
    {
        std::cout << error << std::endl;
        return 1;
    }
    return 0;
}
