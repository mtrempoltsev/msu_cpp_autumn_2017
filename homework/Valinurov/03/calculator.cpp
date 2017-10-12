#include <iostream>
#include <ctype.h>
#include <unordered_map>

enum class Token
{
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    Br_Open,// открывающаяся скобка
    Br_Close,// закрывающаяся скобка
    End
};

// класс выделяет токены, попутно получая число
class Tokenizer
{
public:
    Tokenizer(const char*& in): text(in)
    {
    }

    Token getToken()
    {
        while(auto c = *text++)
        {
            switch(c)
            {
                case '-': return Token::Minus;
                case '+': return Token::Plus;
                case '*': return Token::Mul;
                case '/': return Token::Div;
                case '(': return Token::Br_Open;
                case ')': return Token::Br_Close;
                case 'e':
                    number = constants["e"];
                    return Token::Number;
            }

            if (c == 'P')
            {
                if (*text++ == 'i')
                {
                    number = constants["Pi"];
                    return Token::Number;
                } else
                    throw "Invalid Token\n";
            }

            if (c>='0'&&c<='9')
            {
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

    int GetNumber()
    {
        return number;
    }

private:
    int number = 0;

    std::unordered_map<std::string, double> constants =
        {
            { "Pi", 3.14 },
            { "e", 2.7 }
        };

    const char* text;
};

class Calculator
{
public:

    Calculator(const char*& in)
    {
        tokenizer = new Tokenizer(in);
    }

    //Вычисляет +-
    int Expr()
    {
        int result = Term();

        while (last_token != Token::End)
        {
            if (last_token == Token::Plus)
                result += Term();
            else if (last_token == Token::Minus)
                result -= Term();
            else if (last_token == Token::Br_Close)
            {
                if (brace_balance == 0)
                    throw "Unpaired braces\n";
                break;
            } else
                throw "Invalid Expression\n";
        }

        return result;
    }

private:
    //Вычисляет числа и раскрывает скобки
    int Prim()
    {
        Token new_token = tokenizer->getToken();
        if (new_token == Token::Number)
            return tokenizer->GetNumber();
        else if (new_token == Token::Minus)
            return -Prim();
        else if (new_token == Token::Br_Open)
        {
            brace_balance++;
            int result = Expr();
            if (last_token != Token::Br_Close)
                throw "Unpaired braces\n";
            brace_balance--;
            return result;
        } else
            throw "Invalid Number\n";
    }

    //Вычисляет */
    int Term()
    {
        int result = Prim();
        last_token = tokenizer->getToken();

        while (last_token == Token::Mul || last_token == Token::Div || last_token == Token::Number)
        {
            if (last_token == Token::Mul)
                result *= Prim();
            else if (last_token == Token::Div)
            {
                int divisor = Prim();
                if (divisor == 0)
                    throw "Division by 0\n";
                result /= divisor;
            } else
                throw "Invalid Term\n";
            last_token = tokenizer->getToken();
        }

        return result;
    }

    Token last_token;// last_token - нужно когда Term встретил +- или Expr встретил )

    Tokenizer* tokenizer;

    int brace_balance = 0;// текущий баланс скобок
};

int main(int argc, char* argv[])
{
    if (argc < 2){
        std::cout << "format is ./calc string" << std::endl;
        return 1;
    }

    const char* text = argv[1];
    Calculator calc(text);

    try
    {
        int result = calc.Expr();
        std::cout << result << std::endl;
    }
    catch (const char* ms){
        std::cout << ms << std::endl;
        return 1;
    }

    return 0;
}
