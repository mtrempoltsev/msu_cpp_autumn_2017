/**
 Калькулятор.
 БНФ (скобки и константы Pi (3.14) и e (2.7)):
 expr = term | expr + term | expr - term 
 term = prim | term * prim | term / prim 
 prim = - number | number | name 
 number = [0,9]+
 name = [a-z.A-Z]+
 */
#include <iostream>
#include <unordered_map>

enum class Token
{
	Invalid, 
	Minus,  
	Plus,
	Mul,
	Div,
	Number,
	Left_Bracket,
	Right_Bracket,
	Name,
	End
};

class Tokenizer
{
public:
	/**
	 Получить следующий токен. Не менять text.
	 */
	static Token nextToken(const char*& text)
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
				case '(':return Token::Left_Bracket;
				case ')':return Token::Right_Bracket;
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
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')  ) 
			{	
				auto c1 = *tmp;
				while ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
				{				
					c1 = *(++tmp);
				}
				return Token::Name;
			}
			return Token::Invalid;
		}
		return Token::End;
	}

	/**
	 Получить токен. Продвинуть text.
	 */
	static Token passToken(const char*& text)
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
				case '(':return Token::Left_Bracket;
				case ')':return Token::Right_Bracket;
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
			if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
			{	
				auto c1 = *text;
				while ((c1 >= 'a' && c1 <= 'z') || (c1 >= 'A' && c1 <= 'Z'))
				{				
					c1 = *(++text);
				}
				return Token::Name;
			}
			return Token::Invalid;
		}
		return Token::End;
	}
};

class Calculator
{	
public:
	/**
      Вычислить целое значение выражения expression.
	 */
	int calculate(const char*& expression)
	{	
		text = expression;
		result = expr();
		return result;
	}

private:	
	/**
	 Вывести сообщение об ошибке.
	 */
	int error(const char* err_msg)
	{
		std::cerr << err_msg << std::endl;
		exit(1);
	}

	/**
	 Обработать выражение expr, выдать его результат.
	 */
	double expr()
	{
		double value = term();
		for(;;)
		{
			switch (Tokenizer::nextToken(text))
			{
				case Token::Plus : 
				{	
					Tokenizer::passToken(text);
					value += term();
					break;
				}
				case Token::Minus :
				{	
					Tokenizer::passToken(text);
					value -= term();
					break;
				}
				case Token::End: case Token::Right_Bracket:
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

	/**
	 Обработать выражение term, выдать его результат.
	 */
	double term()
	{	
		double value = prim();
		for(;;)
		{
			switch (Tokenizer::nextToken(text))
			{
				case Token::Mul : 
				{	
					Tokenizer::passToken(text);
					value *= prim();
					break;
				}
				case Token::Div :
				{	
					Tokenizer::passToken(text);
					double d = prim();
					if (d == 0)
					{
						return error("Divide by zero");
					}
					value /= d;
					break;
				}
				case Token::Plus: case Token::Minus: case Token::End: case Token::Right_Bracket:
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

	/**
	 Обработать выражение prim, выдать его результат.
	 */
	double prim()
	{   
		double value = 0;
		bool is_minus = false;

		if (Tokenizer::nextToken(text) == Token::Minus)
		{
			is_minus = true;
			Tokenizer::passToken(text);
		}

		switch (Tokenizer::nextToken(text))
		{	
			case Token::Left_Bracket:
			{
				Tokenizer::passToken(text);
				value = expr();
				if (Tokenizer::nextToken(text) != Token::Right_Bracket)
				{
					return error("Invalid brackets");
				}
				Tokenizer::passToken(text);
				break;
			}
			case Token::Number :
			{	
				value = number();
				Tokenizer::passToken(text);
				break;
			}
			case Token::Name:
			{
				value = name();
				Tokenizer::passToken(text);
				break;				
			}
			default:
			{
				return error("no number");
			}
		}

		if (is_minus)
		{
			return -value;
		} 
		else
		{
			return value;
		}
	}

	/**
	 Обработать выражение number, выдать его результат, сдвинуть указатель на следующий.
	 */
	int number()
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

	/**
	 Обработать выражение name, выдать его результат, сдвинуть указатель на следующий.
	 */
	double name()
	{
		const char* tmp = text;
		std::string iden = "";

		auto c = *tmp;
		while (c == ' ')
		{
			tmp++;
			c = *tmp;
		}

		while( (c >= 'a' && c <= 'z') || (c >= 'A' && c < 'Z'))
		{	
			iden += c;
			tmp++;
			c = *tmp;
		}

		auto it = constants.find(iden);

		if (it == constants.end())
		{
			return error("Invalid name");
		}
		else
		{
			return (*it).second;
		}
	}



//--------------------------------------//

	Tokenizer tokenizer();
	const char* text = "2 + 2";
	int result = 0;
	std::unordered_map<std::string, double> constants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

};


int main(int argc,char** argv)
{
	const char* text = argv[1];
	Calculator calc;
	std::cout << calc.calculate(text) << std::endl;
	return 0; 
}