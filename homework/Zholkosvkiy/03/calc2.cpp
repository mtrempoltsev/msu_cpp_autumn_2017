#include <iostream>
#include <stdexcept>
#include <unordered_map>
using namespace std;

enum class Token
{
	Plus,
	Minus,
	Mult,
	Div,
	Num,
	OpenBracket,
	CloseBracket,
	Word,
	End,
	Invalid,
};

//получаем токен
class Tokenizer
{
public:

	void set(const char* str)
  {
		this->str = str;
		value = 0;
		currentToken = Token::Invalid;
	}

	int getToken()
  {
		while (auto c = *str++)
    {
			switch (c)
      {
				case ' ': continue;
				case '+':
					currentToken = Token::Plus;
					return 0;
				case '-':
					currentToken = Token::Minus;
					return 0;
				case '*':
					currentToken = Token::Mult;
					return 0;
				case '/':
					currentToken = Token::Div;
					return 0;
				case '(':
					fold++;
					currentToken = Token::OpenBracket;
					return 0;
				case ')':
          //на уровень выше
					fold--;
					if (fold < 0)
          {
            //лишняя скобка
						throw runtime_error("Error");
					}
					currentToken = Token::CloseBracket;
					return 0;
			}

      //получаем число
			if ((c >= '0') && (c <= '9'))
      {
				value = c - '0';
				while ((*str >= '0') && (*str <= '9'))
        {
					value = value * 10 + (*str++) - '0';
				}
				currentToken = Token::Num;
				return value;
			}
      //если текст
			if (isalpha(c))
      {
				int i = 0;
				Word[i] = c;
				while (isalpha(*str))
				{
					Word[++i] = *str++;
				}
				Word[++i] = 0;
				currentToken = Token::Word;
				return 0;
			}
			throw runtime_error("Error");

		}
		if (fold > 0)
    {
			throw runtime_error("Error");
		}
		currentToken = Token::End;
		return 0;
	}

	std::string tokenToStr(Token token)
  {
		switch (token)
		{
			case Token::Plus: return "Plus";
			case Token::Minus: return "Minus";
			case Token::Mult: return "Mult";
			case Token::Div: return "Div";
			case Token::Num: return "Num";
			case Token::OpenBracket: return "OpenBracket";
			case Token::CloseBracket: return "CloseBracket";
			case Token::Word: return "Word";
			case Token::End: return "End";
			case Token::Invalid: return "Invalid";
		}
		return "Unknown";
	}

	Token getCurrentToken() { return currentToken; }

	int getValue() { return value; }

	char* getWord() {	return Word;}

private:
	const char* str;
	Token currentToken;
	int value;
	char Word[128]; //сюда записываем константы
	int fold = 0;
};

class Calculator
{
public:

	int calculate(const char* str)
  {
		tokenizer.set(str);
		return get_term();
	}
private:
	Tokenizer tokenizer;
  //вычитаем и скадываем
	int get_term()
  {
		int result = get_item();
		if (tokenizer.getCurrentToken() == Token::Word)
		{
			throw runtime_error("Error");
		}
		while ((tokenizer.getCurrentToken() == Token::Plus) || (tokenizer.getCurrentToken() == Token::Minus))
    {
			if (tokenizer.getCurrentToken() == Token::Plus)
      {
				result += get_item();
			}
      else
      {
				result -= get_item();
			}
		}
		return result;
	}

	int get_item()
  {
		int result = getNumber();
    //вычитаем и делим
		while ((tokenizer.getCurrentToken() == Token::Mult) || (tokenizer.getCurrentToken() == Token::Div))
    {
			if (tokenizer.getCurrentToken() == Token::Mult)
      {
				result *= getNumber();
			}
      else
      {
				int value = getNumber();
        //деление на ноль
				if (value == 0)
        {
					throw runtime_error("Error");
				}
				result /= value;
			}
		}
		return result;
	}

	int getNumber()
  {
		int result = tokenizer.getToken();
		int sign = 1;
    //отрицательное число
		if (tokenizer.getCurrentToken() == Token::Minus)
    {
			result = tokenizer.getToken();
			sign = -1;
		}
    //возвращаем число
		if (tokenizer.getCurrentToken() == Token::Num)
    {
			tokenizer.getToken();
			return result * sign;
		}
    //открывается скобка
		if (tokenizer.getCurrentToken() == Token::OpenBracket)
    {
  		result = get_term();

      if (tokenizer.getCurrentToken() == Token::CloseBracket)
      {
        //считываем следующий
        tokenizer.getToken();
  		}
  		return result * sign;
		}
    //если константа
		if (tokenizer.getCurrentToken() == Token::Word)
		{
			auto word = tokenizer.getWord();
			if ((word[0] == 'P' && word[1] == 'i') )
			{
				tokenizer.getToken();
				return 3.14 * sign;

			}
			else if (word[0] == 'e')
			{
				tokenizer.getToken();
				return 2.71 * sign;
			}
			else
			{
				throw runtime_error("Error");
			}
		}
		throw runtime_error("Error");
		return 0;
	}

};


int main(int argc, char const *argv[])
{
	try
  {
		if (argc > 1)
    {
			Calculator calc;
			cout << calc.calculate(argv[1]) << endl;
		}
		else
		{
			return 1;
		}
	}
  catch (const runtime_error& e)
  {
		return 1;
	}
	return 0;
}
