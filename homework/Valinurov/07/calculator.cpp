#include <iostream>
#include <ctype.h>
#include <unordered_map>
#include <limits>
#include <cmath>
#include <sstream>
#include <string>

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
    static constexpr double min = std::numeric_limits<double>::lowest();
    static constexpr double max = std::numeric_limits<double>::max();
    static constexpr int max_length10 = std::numeric_limits<double>::max_exponent10 - std::numeric_limits<double>::min_exponent10 + 2; // максимальное количество цифр в числе, учитывая .
};

template<>
struct NumericTraits<int>
{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
    static constexpr int max_length10 = std::numeric_limits<int>::digits10 + 1; // максимальное количество цифр в числе
};

template <>
struct NumericTraits<long>
{
    static constexpr long min = std::numeric_limits<long>::min();
    static constexpr long max = std::numeric_limits<long>::max();
    static constexpr int max_length10 = std::numeric_limits<long>::digits10 + 1;
};

template<class T>
struct Parser{
    static bool Number_Token(const char c)
    {
        throw std::invalid_argument("don't work with this type\n");
    }

    static long Get_Number(const char*& in)
    {
        throw std::invalid_argument("don't work with this type\n");
    }
};

template<>
struct Parser<long>
{
    static bool Number_Token(const char c)
    {
        return c >= '0' && c <= '9';
    }

    static long Get_Number(const char*& in)
    {
        int64_t res;
        std::string number_string;// максимальное количество цифр в числе

        for (; *in >= '0' && *in <= '9'; in++)
            number_string += *in;

        std::istringstream buffer(number_string);
        buffer >> res;

        if ((number_string.length() > NumericTraits<long>::max_length10) || (res > NumericTraits<long>::max) || (res < NumericTraits<long>::min))
            throw std::invalid_argument("long overflow detected\n");

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
        int64_t res;
        std::string number_string;

        for (; *in >= '0' && *in <= '9'; in++)
            number_string += *in;

        std::istringstream buffer(number_string);
        buffer >> res;

        if ((number_string.length() > NumericTraits<int>::max_length10) || (res > NumericTraits<int>::max) || (res < NumericTraits<int>::min))
            throw std::invalid_argument("int overflow detected\n");

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
        long double res;
        std::string number_string;

        for (; *in >= '0' && *in <= '9'; in++)
            number_string += *in;

        if (*in == '.')
        {
            number_string += '.';
            in++;
            for (; *in >= '0' && *in <= '9'; in++)
                number_string += *in;
        }

        std::istringstream buffer(number_string);
        buffer >> res;

        if ((number_string.length() > NumericTraits<double>::max_length10) || (res > NumericTraits<double>::max) || (res < NumericTraits<double>::min))
            throw std::invalid_argument("double overflow detected\n");

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
                    throw std::invalid_argument("Invalid Token\n");
            }

            if (Parser<T>::Number_Token(c))
            {
                number = Parser<T>::Get_Number(--text);
                return Token::Number;
            }

            if (!isspace(c)) // если символ не среди разрешённых и не пробельный бросаем исключение
                throw std::invalid_argument("Invalid Token\n");
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
                    throw std::invalid_argument("Unpaired braces\n");
                break;
            } else
                throw std::invalid_argument("Invalid Expression\n");
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
                throw std::invalid_argument("Unpaired braces\n");
            brace_balance--;
            return result;
        } else
            throw std::invalid_argument("Invalid Number\n");
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
                    throw std::invalid_argument("Division by 0\n");
                result /= divisor;
            } else
                throw std::invalid_argument("Invalid Term\n");
            last_token = tokenizer->getToken();
        }

        return result;
    }

    Token last_token;// last_token - нужно когда Term встретил +- или Expr встретил )

    Tokenizer<T>* tokenizer;

    int brace_balance = 0;// текущий баланс скобок
};
