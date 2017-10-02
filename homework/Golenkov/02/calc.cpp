#include <iostream>

enum class Token
{
    Invalid,
    Minus,
    Plus,
    Star,
    Slash,
    Number,
    End
};

Token getToken(const char*& text)
{
    //separate token
    auto b = *text;
    while(const auto c = *text++)
    {
        switch(c)
        {
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case '*': return Token::Star;
            case '/': return Token::Slash;
            case ' ': continue;
        }
        if (c >= '0' && c <= '9')
        {
            bool is_second_digit = false;
            for (auto c = *text; c >= '0' && c <= '9'; ++text)
            {
                is_second_digit = true;
                c = *text;
            }
            //return the pointer to the last digit
            --text;
            if (is_second_digit) --text;
            return Token::Number;
        }
        return Token::Invalid;
    }
    return Token::End;
}

int getNumber(const char*& text)
{
    //read only one number
    auto token = getToken(text);
    if (token == Token::Number)
    {
        auto c = *text;
        int number = 0,
                 i = 1,                   //degree of 10
                 j = 1;                   //degree of the number
        while (c <= '9' && c >= '0')
        {
            //read digits of the number from right to left
            number += i * static_cast<int>(c - '0');
            c = *--text;
            i *= 10;
            j++;
        }
        auto v = *text;
        for (int k = 0; k < j; k++)
        {
            //set the pointer after the last digit
            v = *++text;
        }
        return number;
    }
    else if (token == Token::Minus)
    {
        return -getNumber(text);
    }
    else
    {
        throw -1;
    }
}
int processingTerms(const char*& text, Token& operation)
{
	int result = getNumber(text);
	operation = getToken(text);
	if (operation == Token::Invalid)
    {
        throw -1;
    }
    while (operation == Token::Star || operation == Token::Slash || operation == Token::Number)
	{
		if (operation == Token::Star)
        {
            result *= getNumber(text);
        }
		else if (operation == Token::Slash)
        {
            int divisor = getNumber(text);
            if (divisor != 0)
            {
                result /= divisor;
            }
            else
            {
                //case of the zero divisor
                throw -2;
            }
        }
		else
        {
            throw -3;
        }
		operation = getToken(text);
	}
	return result;
}
int processingExpression(const char*& text)
{
    Token operation = Token::Plus;
	int result = processingTerms(text, operation);
	while (operation != Token::End)
	{
	    if (operation == Token::Plus)
        {
            result += processingTerms(text, operation);
        }
	    else if (operation == Token::Minus)
        {
            result -= processingTerms(text, operation);
        }
	}
	return result;
}

int main(int argc, char* argv[])
{
    if (argc < 2){
		std::cout << "Wrong format!" << std::endl;
		return 0;
	}

    const char* text = argv[1];

    try
    {
        std::cout << processingExpression(text) << std::endl;
    }
    catch(int i)
    {
        if (i == -1)
        {
            std::cout << "Invalid symbol in expression!" << std::endl;
        }
        else if (i == -2)
        {
            std::cout << "Division by zero!" << std::endl;
        }
        else
        {
            std::cout << "Wrong expression!" << std::endl;
        }
    }
    return 0;
}
