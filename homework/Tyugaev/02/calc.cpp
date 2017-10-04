#include <iostream>

/*
Грамматика калькулятора

	expr = term
   		| expr + term
		| expr - term
	term = prim
	    | term * prim
    	| term / prim
	prim = number
	    | -number
	number = [0-9]+
*/

using namespace std;

enum class Token {
	Invalid,
	Minus,
	Plus,
	Mul,
	Div,
	Number,
	End
};

Token getToken(const char*& text) {
/*
	Cчитывает токен, на местоположение которого указывает &text.
	После выполнения  &text указывает на местоположение считанного токена.
*/
	while (const auto c = *text)
	{
		switch (c)
		{
			case ' ':
			{
				//игнорируем пробелы
				text++;
				continue;
			}			
			case '-': return Token::Minus;
			case '+': return Token::Plus;
			case '*': return Token::Mul;
			case '/': return Token::Div;
		}
		if (c >= '0' && c <= '9') return Token::Number;
		else return Token::Invalid;
	}
	return Token::End;
}

int prim(const char*& text) {
/*
	Возвращает число, над которым дальше будут выполняться арифметические операции.
*/
	int num_value = 0;
	switch (getToken(text))
	{
		case Token::Number:
		{
			do			//цикл для преобразования последовательности токенов Number в число
			{
				num_value = num_value * 10 + ((int)*text - '0');
				text++;
			} while (getToken(text) == Token::Number);
			return num_value;
		}
		case Token::Minus:
		{
			getToken(++text);
			return -prim(text);
		}
		case Token::Invalid:
		{
			cerr << "Ошибка! Некорректный символ" << endl;
			exit(1);
		}
		default:
		{
			cerr << "Ошибка! Неверный синтаксис" << endl;
			exit(1);
		}
	}
}

double term(const char*& text) {
/*
	Возвращает результат выполнения операций умножения и деления.
*/
	double left = prim(text);
	for(;;)
	{
		switch (getToken(text))
		{
			case Token::Mul:
			{
				left *= prim(++text);
				break;
			}
			case Token::Div:
			{
				int d = prim(++text);
				if(d != 0) left /= d;
				else
				{
					cerr << "Ошибка! Деление на ноль" << endl;
					exit(1);
				}
				break;
			}
			case Token::Invalid:
			{
				cerr << "Ошибка! Некорректный символ" << endl;
				exit(1);
			}
			default:
			{
				return left;
			}
		}
	}	
}

double expr(const char*& text) {
/*
	Возвращает результат выполнения операций сложения и вычитания.
*/
	double left = term(text);
	for(;;)
	{
		switch (getToken(text))
		{
			case Token::Plus:
			{
				left += term(++text);
				break;
			}
			case Token::Minus:
			{
				left -= term(++text);
				break;
			}
			case Token::Invalid:
			{
				cerr << "Ошибка! Некорректный символ" << endl;
				exit(1);
			}
			default:
			{
				return left;
			}
		}
	}
}

int main(int argc, char* argv[]) {
	if(argc != 2) {
		cout << "Ошибка! Неверно заданы входные параметры" << endl;
		return 1;
	}

	const char* text = argv[1];

	cout << expr(text) << endl;

	return 0;
}
