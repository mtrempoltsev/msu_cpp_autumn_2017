#include <iostream>
#include<stdio.h>


/*
expr = term
| expr + term
| expr - term
term = prim
| term * prim
| term / prim
prim = number
| -number
number = [0 - 9] +
*/

using namespace std;

//Token class
enum class Token
{
	Invalid,
	Minus,
	Plus,
	Mul,
	Div,
	Number,
	End
};

//get the next Token. If Token::Num  - val is the number, else val is 0
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
		val = 0;
		//if c is number
		if (c >= '0' && c < '9')
		{
			val = c - '0';
			//
			for (auto c = *text;  c >= '0' && c <= '9';)
			{
				val = val * 10 + (c - '0');
				c = *++text;
			}
			return Token::Number;
		}
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
	int number = getToken(text, nextToken);
	int sign = 1; //sign before the number
	while (nextToken == Token::Minus || nextToken == Token::Plus)
	{
		if (nextToken == Token::Minus)
		{
			sign = -sign;
		}
		number = getToken(text, nextToken);
	}
	getToken(text, nextToken);
	return sign * number;
}

//multiply or divide
int Prim(const char*& text, Token& nextToken)
{
	int result = getNumber(text, nextToken);

	while (nextToken == Token::Mul || nextToken == Token::Div)
	{
		if (nextToken == Token::Mul)
		{
			result *= getNumber(text, nextToken);
		}
		else
		{
			result /= getNumber(text, nextToken);
		}
	}
	return result;
}
int calc(const char* text)
{
	Token nextToken;
	int expr = Prim(text, nextToken);
	while (nextToken == Token::Plus || nextToken == Token::Minus)
	{
		if (nextToken == Token::Plus)
		{
			expr += Prim(text, nextToken);
		}
		else
		{
			expr -= Prim(text, nextToken);
		}
	}
	return expr;
}
int main(int argc, char *argv[])
{

	cout << argv[1] << endl;
	cout << calc(argv[1]) << endl;
	return 0;
}
