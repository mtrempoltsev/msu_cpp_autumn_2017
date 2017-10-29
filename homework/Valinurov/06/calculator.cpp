#include <iostream>
#include <ctype.h>
#include <unordered_map>
#include <limits>
#include <cmath>

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

template<class T>
struct NumericTraits{};

template<>
struct NumericTraits<double>
{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();
};

template<>
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

template<class T>
struct Parser{};

template<>
struct Parser<long>
{
    static bool Number_Token(const char c)
    {
        return c >= '0' && c <= '9';
    }

    static long Get_Number(const char*& in)
    {
        int64_t res = 0;

        for (; *in >= '0' && *in <= '9'; in++)
        {
            res = res * 10 + *in - '0';
        }

        if ((res > NumericTraits<long>::max) || (res < NumericTraits<long>::min))
            std::cout << "long overflow detected" << std::endl;

        return res;
    }
};

template<>
struct Parser<int>
{
    static bool Number_Token(const char c)
    {
        return Parser<long>::Number_Token(c);
    }

    static int Get_Number(const char*& in)
    {
        int64_t res = 0;

        for (; *in >= '0' && *in <= '9'; in++)
        {
            res = res * 10 + *in - '0';
        }

        if ((res > NumericTraits<int>::max) || (res < NumericTraits<int>::min))
            std::cout << "int overflow detected" << std::endl;

        return res;
    }
};

template<>
struct Parser<double>
{
    static bool Number_Token(const char c)
    {
        return (c >= '0' && c <= '9') || c == '.';
    }

    static double Get_Number(const char*& in)
    {
        long double res = 0, fraction = 10;
        bool single_point = true; // запретить число .

        for (; *in >= '0' && *in <= '9'; in++)
        {
            res = res * 10 + *in - '0';
            single_point = false;
        }

        if (*in == '.')
        {
            in++;
            for (; *in >= '0' && *in <= '9'; in++)
            {
                res += (*in - '0') / fraction;
                fraction *= 10;
                single_point = false;
            }
        }

        if (single_point)
            throw ". isn't a number\n";

        if ((res > NumericTraits<double>::max) || (res < NumericTraits<double>::min))
            std::cout << "double overflow detected" << std::endl;

        return res;
    }
};

template<class T>
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

            if (Parser<T>::Number_Token(c))
            {
                number = Parser<T>::Get_Number(--text);
                return Token::Number;
            }

            if (!isspace(c)) // если символ не среди разрешённых и не пробельный бросаем исключение
                throw "Invalid Token\n";
        }
        return Token::End;
    }

    T GetNumber()
    {
        return number;
    }

private:
    T number = 0;

    std::unordered_map<std::string, double> constants =
        {
            { "Pi", 3.14 },
            { "e", 2.7 }
        };

    const char* text;
};

template<class T>
class Calculator
{
public:

    Calculator(const char*& in)
    {
        tokenizer = new Tokenizer<T>(in);
    }

    //Вычисляет +-
    T Expr()
    {
        T result = Term();

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
    T Prim()
    {
        Token new_token = tokenizer->getToken();
        if (new_token == Token::Number)
            return tokenizer->GetNumber();
        else if (new_token == Token::Minus)
            return -Prim();
        else if (new_token == Token::Br_Open)
        {
            brace_balance++;
            T result = Expr();
            if (last_token != Token::Br_Close)
                throw "Unpaired braces\n";
            brace_balance--;
            return result;
        } else
            throw "Invalid Number\n";
    }

    //Вычисляет */
    T Term()
    {
        T result = Prim();
        last_token = tokenizer->getToken();

        while (last_token == Token::Mul || last_token == Token::Div || last_token == Token::Number)
        {
            if (last_token == Token::Mul)
                result *= Prim();
            else if (last_token == Token::Div)
            {
                T divisor = Prim();
                if (fabs(divisor) < 1e-12) // проверка на равенство 0 делителя
                    throw "Division by 0\n";
                result /= divisor;
            } else
                throw "Invalid Term\n";
            last_token = tokenizer->getToken();
        }

        return result;
    }

    Token last_token;// last_token - нужно когда Term встретил +- или Expr встретил )

    Tokenizer<T>* tokenizer;

    int brace_balance = 0;// текущий баланс скобок
};
