/**
 Калькулятор.
 БНФ:
 expr = term | expr + term | expr - term
 term = prim | term * prim | term / prim
 prim = - number | number
 number = [0,9]+
 */
#include <iostream>

/**
 Вывести сообщение об ошибке.
 */
int error(const char* err_msg)
{
	std::cerr << err_msg << std::endl;
	return 1;
}

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

/**
 Получить следующий токен. Не менять text.
 */
Token nextToken(const char*& text)
{
 const char* tmp = text;
 while(const auto c = *tmp++)
	{ 	
		switch (c)
		{	
			case ' ': continue;
			case '-':return Token::Minus;
			case '+':return Token::Plus;
			case '*':return Token::Mul;
			case '/':return Token::Div;
		}
		if (c >= '0' && c <= '9') 
		{	
			auto c1 = *tmp;
			while( c1 >= '0' && c1 <= '9')
			{				
				c1 = *(++tmp);
			}
			return Token::Number;
		}
		return Token::Invalid;
	}
	return Token::End;
}

/**
 Получить токен. Продвинуть text.
 */
Token passToken(const char*& text)
{
 while(const auto c = *text++)
	{	
		switch (c)
		{	
			case ' ': continue;
			case '-':return Token::Minus;
			case '+':return Token::Plus;
			case '*':return Token::Mul;
			case '/':return Token::Div;
		}
		if (c >= '0' && c <= '9') 
		{	
			auto c1 = *text;
			while( c1 >= '0' && c1 <= '9')
			{			
				c1 = *(++text);
			}
			return Token::Number;
		}
		return Token::Invalid;
	}
	return Token::End;
}

/**
 Обработать выражение expr, выдать его результат.
 */
int expr(const char*& text);

/**
 Обработать выражение term, выдать его результат.
 */
int term(const char*& text);

/**
 Обработать выражение prim, выдать его результат.
 */
int prim(const char*& text);

/**
 Обработать выражение number, выдать его результат, сдвинуть указатель на следующий.
 */
int number(const char*& text);


int expr(const char*& text)
{
	int value = term(text);
	for(;;)
	{
		switch (nextToken(text))
		{
			case Token::Plus : 
			{	
				passToken(text);
				value += term(text);
				break;
			}
			case Token::Minus :
			{	
				passToken(text);
				value -= term(text);
				break;
			}
			case Token::End:
			{	
				return value;
				break;
			}
			default:
			{
				return error("invalid operation in expr");
			}
		}
	}
}


int term(const char*& text)
{
	int value = prim(text);
	for(;;)
	{
		switch (nextToken(text))
		{
			case Token::Mul : 
			{	
				passToken(text);
				value *= prim(text);
				break;
			}
			case Token::Div :
			{	
				passToken(text);
				int d = prim(text);
				if (d == 0)
				{
					return error("Divide by zero");
				}
				value /= d;
				break;
			}
			case Token::Plus: case Token::Minus: case Token::End:
			{	
				return value;
				break;
			}
			default:
			{
				return error("Invalid operation in term");
			}
		}
	}
}


int prim(const char*& text)
{   
	int value = 0;
	switch (nextToken(text))
	{
		case Token::Minus : 
		{	
			passToken(text);
			if (nextToken(text) == Token::Number) 
		    {
		    	value = -number(text);
				passToken(text);
				break;
			}
			else
			{
				return error("minus without number");
			}
			break;
		}
		case Token::Number :
		{	
			value = number(text);
			passToken(text);
			break;
		}
		default:
		{
			return error("no number");
		}
	}
	return value;
}


int number(const char*& text)
{	
	const char* tmp = text;
	int value = 0;

	auto c = *tmp;
	while (c == ' ')
	{
		tmp++;
		c = *tmp;
	}

	while( c >= '0' && c <= '9')
	{	
		value = value*10 + c - '0';
		tmp++;
		c = *tmp;
	}
	return value;
}


int main(int argc,char** argv)
{
	const char* text = argv[1];
	std::cout << expr(text);
	return 0; 
}