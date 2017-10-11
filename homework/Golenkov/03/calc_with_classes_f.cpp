#include <iostream>
#include <unordered_map>

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

class Tokenizator
{
public:
    Tokenizator (const char*& str): text(str) {}
    Token getToken();
    int getNumber();
    int getConstant();
private:
    const char* text;
};

class Calculator
{
public:
    Calculator(const char*& str);
    int processingExpressions();
    ~Calculator();
private:
    int brackets;                 // number of uncapped parentheses
    Token operation;
    Tokenizator* tokenizator;

    int processingPrimitives();
    int processingTerms();
};

Calculator::Calculator(const char*& str)
{
    tokenizator = new Tokenizator(str);
    brackets = 0;
    operation = Token::Plus;
}

Calculator::~Calculator()
{
    delete tokenizator;
}

Token Tokenizator::getToken()
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
            for (auto c = *text; c >= '0' && c <= '9'; ++text)
            {
                is_second_digit = true;
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

int Tokenizator::getNumber()
{
    // read only one number without sign
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
    return number;
}

int Tokenizator::getConstant()
{
    // obtaining constants
        auto c = *--text;
        text++;
        int result = 0;
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

int Calculator::processingPrimitives()
{
    // get number or constant from tokenizator, implements unary minus and parses parentheses
    auto token = tokenizator->getToken();
    if (token == Token::Number)
    {
        return tokenizator->getNumber();
    }
    else if (token == Token::Constant)
    {
        return tokenizator->getConstant();
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
        throw -1;
    }
}
int Calculator::processingTerms()
{
	int result = processingPrimitives();
	operation = tokenizator->getToken();
	if (operation == Token::Invalid)
    {
        throw -1;
    }
	while (operation == Token::Star || operation == Token::Slash || operation == Token::Number)
	{
		if (operation == Token::Star)
        {
			result *= processingPrimitives();
        }
		else if (operation == Token::Slash)
        {
            result /= processingPrimitives();
        }
		else
        {
            throw -1;
        }
		operation = tokenizator->getToken();
	}
	return result;
}
int Calculator::processingExpressions()
{
	int result = processingTerms();
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
                throw -1;
            }
            brackets--;
            break;
        }
        else
        {
            throw -1;
        }
	}
	return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2){
        std::cout << "Wrong format!" << std::endl;
        return 1;
    }

    const char* text = argv[1];

    Calculator calc(text);
    try
    {
        std::cout << calc.processingExpressions() << std::endl;
    }
    catch(int i)
    {
        if (i == -1)
        {
            std::cout << "Wrong expression!" << std::endl;
        }
        else
        {
            std::cout << "Division by zero!" << std::endl;
        }
        return 1;
    }
    return 0;
}
