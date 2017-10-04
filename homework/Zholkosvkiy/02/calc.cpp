#include <iostream>
#include<stdio.h>


/*
expr = term
| expr + term
| expr - term
term = getPrim
| term * getPrim
| term / getPrim
getPrim = number
| -number
number = [0 - 9] +
*/

using namespace std;

//Token class
enum class Token
{
	Minus,
	Plus,
	Mul,
	Div,
	Number,
	End,
	Invalid
};

//get the next Token. If Token::Num  - val is the number
Token _getToken(const char*& text, int &val)
{
	while (const auto c = *text++)
	{
		switch (c)
		{
			case ' ': continue;
			case '-': return Token::Minus;
			case '+': return Token::Plus;
			case '*': return Token::Mul;
			case '/': return Token::Div;
		}
		//if c is number
		if (c >= '0' && c < '9')
		{
			val = c - '0';
			//get number
			for (auto c = *text;  c >= '0' && c <= '9';)
			{
				val = val * 10 + (c - '0');
				c = *++text;
			}
			return Token::Number;
		}
		throw "Invalid character";
		return Token::Invalid;
	}
	return Token::End;
}

//returns number if is number and nextToken
int getToken(const char*&text, Token& nextToken)
{
	int val = 0;
	nextToken = _getToken(text, val);
	return val;
}

//returns number with its sign
int getNumber(const char*& text, Token& nextToken)
{
	int number = getToken(text,nextToken);

	//only number or minus before negative number
	if( (nextToken != Token::Number) && (nextToken != Token::Minus))
	{
		throw "Error! Invalid expression";
	}
	//if it's just a number
	if( nextToken == Token::Number)
	{
 		getToken(text,nextToken);
		return number;
	}
	//may be negative number
	else if ( nextToken == Token::Minus)
	{
		number = getToken(text,nextToken);
		//if the next is a number
		if( nextToken == Token::Number)
		{
 			getToken(text,nextToken);
			return (-1)*number;
		}
		else
		{
			throw "Error! Invalid expression";
		}
	}
	return 1;
}
//multiply or divide
int getPrim(const char*& text, Token& nextToken)
{
	int result = getNumber(text, nextToken);

	while (nextToken == Token::Mul || nextToken == Token::Div)
	{
		//if multiply
		if (nextToken == Token::Mul)
		{
			int number = getNumber(text, nextToken);
			result *= number;
		}
		//if divide
		else
		{
			int number = getNumber(text, nextToken);
			if (number == 0)
			{
				throw "Error! Invalid expression";
			}
			else
			{
				result /= number;
			}
		}
	}

	return result;
}

int calc(const char* text)
{
	Token nextToken;

	int expr = getPrim(text, nextToken);

	while (nextToken == Token::Plus || nextToken == Token::Minus)
	{
		//if add
		if (nextToken == Token::Plus)
		{
			expr += getPrim(text, nextToken);
		}
		//if substract
		else
		{
			expr -= getPrim(text, nextToken);
		}
	}
	return expr;
}
int main(int argc, char *argv[])
{
	int result;
	//no expression
	if (argc != 2)
	{
		//cout << "Please enter your expression!" << endl;
		return 1;
	}
	else
	{
	//	cout << argv[1] << endl;
	}
	//try to calculate
	try
	{
	 	result = calc(argv[1]);
	}

	//error mesage
	catch(const char* error)
	{
	//	cout << error << endl;
		return 1;
	}
	//it's ok!
	cout << result << endl;

	return 0;
}
