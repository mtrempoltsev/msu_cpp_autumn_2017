#include <iostream>
#include <unordered_map>
#include <cstdlib>
#include <limits>

void error(const char* err_msg)
{
	std::cerr << err_msg << std::endl;
	exit(1);
}

template <typename T>
struct NumericTraits
{
};

template <> 
struct NumericTraits<int>
{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
};

template <> 
struct NumericTraits<long>
{
    static constexpr long min = std::numeric_limits<long>::min();
    static constexpr long max = std::numeric_limits<long>::max();
};

template <> 
struct NumericTraits<double>
{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();;
};


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

template<typename T>
class Tokenizer
{
};

template<>
class Tokenizer<int>
{
public:

	int parse(const char* text)
	{	
		const char* tmp = text;
		long long value = 0;

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
		if (value <= NumericTraits<int>::max && value >= NumericTraits<int>::min)
		{
			return value;
		}
		else error("Wrong int");
	}
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
			return Token::Invalid;
		}
		return Token::End;
	}
};

template<>
class Tokenizer<long>
{
public:

	long parse(const char* text)
	{	
		const char* tmp = text;
		long long value = 0;

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

		if (value <= NumericTraits<long>::max && value >= NumericTraits<long>::min)
		{
			return value;
		}
		else error("Wrong long");
	}
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
			return Token::Invalid;
		}
		return Token::End;
	}
};

template<>
class Tokenizer<double>
{
public:

	double parse(const char* text)
	{	
		const char* tmp = text;
		long double value = atof(tmp);
		if (value <= NumericTraits<double>::max && value >= NumericTraits<double>::min)
		{
			return value;
		}
		else error("Wrong double");
	}
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
				if (c1 == '.')
				{
					c1 = *(++tmp);
					while( c1 >= '0' && c1 <= '9')
					{				
						c1 = *(++tmp);
					}
				}
				else if (c1 == 'e')
				{
					c1 = *(++tmp);
					if ( c1 != '-' && c1 != '+')
					{
						return Token::Invalid;
					}
					c1 = *(++tmp);
					if (c1 < '0' || c1 > '9')
					{
						return Token::Invalid;
					}
					while( c1 >= '0' && c1 <= '9')
					{				
						c1 = *(++tmp);
					}
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
				if (c1 == '.')
				{
					c1 = *(++text);
					while( c1 >= '0' && c1 <= '9')
					{				
						c1 = *(++text);
					}
				}
				else if (c1 == 'e')
				{
					c1 = *(++text);
					if ( c1 != '-' && c1 != '+')
					{
						return Token::Invalid;
					}
					c1 = *(++text);
					if (c1 < '0' || c1 > '9')
					{
						return Token::Invalid;
					}
					while( c1 >= '0' && c1 <= '9')
					{				
						c1 = *(++text);
					}
				}
			}	
			return Token::Invalid;
		}
		return Token::End;
	}
};


template<typename T>
class Calculator
{	
public:
	/**
      Вычислить целое значение выражения expression.
	 */
	T calculate(const char*& expression)
	{	
		text = expression;
		result = expr();
		if (Tokenizer<T>::nextToken(text) != Token::End) return error("Invalid brackets");
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
	T expr()
	{
		T value = term();
		for(;;)
		{
			switch (Tokenizer<T>::nextToken(text))
			{
				case Token::Plus : 
				{	
					Tokenizer<T>::passToken(text);
					value += term();
					break;
				}
				case Token::Minus :
				{	
					Tokenizer<T>::passToken(text);
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
	T term()
	{	
		T value = prim();
		for(;;)
		{
			switch (Tokenizer<T>::nextToken(text))
			{
				case Token::Mul : 
				{	
					Tokenizer<T>::passToken(text);
					value *= prim();
					break;
				}
				case Token::Div :
				{	
					Tokenizer<T>::passToken(text);
					T d = prim();
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
	T prim()
	{   
		T value = 0;
		bool is_minus = false;

		if (Tokenizer<T>::nextToken(text) == Token::Minus)
		{
			is_minus = true;
			Tokenizer<T>::passToken(text);
		}

		switch (Tokenizer<T>::nextToken(text))
		{	
			case Token::Left_Bracket:
			{
				Tokenizer<T>::passToken(text);
				value = expr();
				if (Tokenizer<T>::nextToken(text) != Token::Right_Bracket)
				{
					return error("Invalid brackets");
				}
				Tokenizer<T>::passToken(text);
				break;
			}
			case Token::Number :
			{	
				value = number();
				Tokenizer<T>::passToken(text);
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
	T number()
	{	
		return tokenizer.parse(text);
	}


//--------------------------------------//
	Tokenizer<T> tokenizer;
	const char* text = "2 + 2";
	T result = 0;
};