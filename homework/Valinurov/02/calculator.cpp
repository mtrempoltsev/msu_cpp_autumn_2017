#include <iostream>
#include <ctype.h>

enum class Token
{
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
};

Token getToken(const char*& text, int& number)
{
    while(auto c = *text++)
    {
       switch(c)
       {
           case '-': return Token::Minus;
           case '+': return Token::Plus;
           case '*': return Token::Mul;
           case '/': return Token::Div;
       }
        if (c>='0'&&c<='9') {
			number = 0;

			while (c >= '0' && c <= '9')
			{
				number = number * 10 + c - '0';
				c = *text++;
			}
			text --; // взяли лишний символ
            return Token::Number;
        }
        if (!isspace(c)) // если символ не среди разрешённых и не пробельный бросаем исключение
			throw "Invalid Token\n";
    }
    return Token::End;
}

//Вычисляет числа, в том числе с унарным минусом
int Number(const char*& text)
{
	int result;
	Token new_token = getToken(text, result);
	if (new_token == Token::Number)
		return result;
	else if (new_token == Token::Minus){
		return -Number(text);
	} else
		throw "Invalid Number\n";
}

//Вычисляет */
int Term(Token& last_token, const char*& text)
{
	int new_number;
	int result = Number(text);
	last_token = getToken(text, new_number); 

	while (last_token == Token::Mul || last_token == Token::Div || last_token == Token::Number)
	{
		if (last_token == Token::Mul)
				result *= Number(text);
		else if (last_token == Token::Div)
				result /= Number(text);
		else
			throw "Invalid Term\n";

		last_token = getToken(text, new_number);
	}

	return result;
}

//Вычисляет +-
int Expr(const char*& text)
{
	Token last_token; // last_token - возвращается из Term, когда Term встретит +-
	int result = Term(last_token, text);

	while (last_token != Token::End)
	{
		if (last_token == Token::Plus)
			result += Term(last_token, text);
		else if (last_token == Token::Minus)
			result -= Term(last_token, text);
		else
			throw "Invalid Expression\n";
	}

	return result;
}

int main(int argc, char* argv[])
{
	if (argc < 2){
		std::cout << "format is ./calc string" << std::endl;
		return 0;
	}

    const char* text = argv[1];
	
	try 
	{
		int result = Expr(text);
		std::cout << result << std::endl;
	} 
	catch (const char*){
		std::cout << "Invalid String" << std::endl;
	}
	
    return 0;
}
