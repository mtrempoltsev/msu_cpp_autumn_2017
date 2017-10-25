#include <iostream>

using namespace std;

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

/*====================================================
*  Функция разбивает данную строку на токены
*  Вход -- строка
*  Вывод -- токены строки
====================================================*/


Token getToken(const char *&text)
{
    while (const auto c = *text++)
    {
        switch (c)
        {
            case '*': return Token::Mul;
            case '/': return Token::Div;
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case ' ': continue;
        }

        if ((c >= '0') && (c <= '9'))
        {
            for (auto c = *text; c >= '0' && c <= '9';)
            {
                text++;
                c = *text;
            }

            return Token::Number;
        }

        return Token::Invalid;
    }
    return Token::End;
}

/*====================================================
*  Функция выделяет числа
*  Вход -- токен, число1, число2
*  Вывод -- числа в строке или код ошибки
====================================================*/

int prim(Token &token, const char *&text, const char *&prev)
{
    token = getToken(text);
    switch (token)
    {
        case Token::Number:
        {
            int number = atoi(prev);
            token = getToken(text);
            prev = text;

            if (token == Token::Invalid)
            {
                cout << "Error input" << endl;
                exit(-1);
            }

            return number;
        }

        case Token::Minus:
        {
            int number = prim(token, text, prev);
            return number;
        }

        default:
        {
            cout << "Error input" << endl;
            exit(-1);
        }

    }
}

/*====================================================
* Реализация умножения/деления
* Вход: токен, множитель1, множитель2
* Вывод: результат умножения/деления или код ошибки:
*                                        -1 -- /0
====================================================*/

int term(Token &token, const char *&text, const char *&prev)
{
    int left = prim(token, text, prev);
    while(1)
    {
        switch (token)
        {
            case Token::Mul:
            {
                left *= prim(token, text, prev);
                break;
            }

            case Token::Div:
            {
                int divisor = prim(token, text, prev);
                if (divisor == 0)
                {
                    cout << "Div 0" << endl;
                    exit(-1);
                }
                left /= divisor;
                break;
            }

            default: return left;
        }
    }
}

/*====================================================
* Реализация сложения/вычитания
* Вход: токен, слагаемое1, слагаемое2
* Вывод: результат сложения/разности
====================================================*/

int expr(Token &token, const char *&text, const char *&prev)
{
    int left = term(token, text, prev);
    while(1)
    {
        switch (token)
        {
            case Token::Plus:
            {
                left += term(token, text, prev);
                break;
            }
            case Token::Minus:
            {
                left -= term(token, text, prev);
                break;
            }

            default: return left;
        }
    }
}

int main(int argc, char *argv[])
{
    const char *text = "2*2";

    if (argc == 1)
    {
        cout << "Empty expression"  << endl;
        return -1;
    }

    text = argv[1];

    auto prev = text;

    auto token = getToken(text);

    if (token == Token::End)
    {
        cout << "Empty expression"  << endl;
        return -1;
    }

    if (token != Token::Invalid)
    {
        text = prev;
        cout << expr(token, text, prev) << endl;
    }
    else
    {
        cout << "Error input"  << endl;
        return -1;
    }
return 0;
}
