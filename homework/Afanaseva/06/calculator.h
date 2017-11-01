#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <unordered_map>
#include <iostream>
#include <exception>
#include <limits>

using namespace std;


bool almost_equal(double a, double b, double epsilon = 1e-7)
{
    double maximum = max(1., max(abs(a), abs(b)));
    if (abs(a - b) < epsilon * maximum)
        return true;
    return false;
}

// ======================================================================================


enum class Token // : char
{
    End,     //0
    Minus,   //1
    Plus,    //2
    Mul,     //3
    Div,     //4
    Number,  //5
    Invalid, //6
    Const,
    OpenBracket,
    ClosBracket
};
std::unordered_map<std::string, double> constants = {
    { "Pi", 3.14159},
    { "e",  2.71828}};

// Шаблоны свойств для проверки допустимости входных данных
template <typename T>
struct NumericTraits
{
};

template <> // Специализация
struct NumericTraits<double>
{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();
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

// Класс парсера с различными специализациями

template <class T>
class Parser
{};

template <>
class Parser<double>
{
public:
    double getNumber(const char* text)
    {
        long double value = std::strtold(text, nullptr);
        if (value < NumericTraits<double>::min
            || value > NumericTraits<double>::max)
        {
            throw "getNumber error: invalid number range.";
        }
        value = (double)value;
        return value;
    }
};

template <>
class Parser<int>
{
public:
    int getNumber(const char* text)
    {
        long value = std::atol(text);
        if (value < NumericTraits<int>::min
            || value > NumericTraits<int>::max)
        {
            throw "getNumber error: invalid number range.";
        }
        value = (int)value;
        return value;
    }
};

template <>
class Parser<long>
{
public:
    long getNumber(const char* text)
    {
        long long value = std::atoll(text);
        if (value < NumericTraits<long>::min
            || value > NumericTraits<long>::max)
        {
            throw "getNumber error: invalid number range.";
        }
        value = (long)value;
        return value;
    }
};
// Класс калькулятор

template <class T, class Device>
class Calculator
{
private:
    T result;
    T value;
    size_t level;
    const char* unshifted_text;
    const char* text;
    Device parser_;

    Token getToken();

    T _prim();
    T prim();
    T term();


public:
    Calculator()
        : result(0), value(0), level(0), unshifted_text(nullptr), text(nullptr)
        {}

    T token_sequence(const char*& text);
};

template <typename T, typename Device>
Token Calculator<T, Device>::getToken() // if Token has type - Number, then value replaces by ridden number
{
    std::string constant_name = "";
    value = 0;
    while (const auto c = *text++) // be going to zero (end of line)
    {
        switch (c)
        {
            case ' ': continue;
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case '*': return Token::Mul;
            case '/': return Token::Div;
            case '(': return Token::OpenBracket;
            case ')': return Token::ClosBracket;
        }
        if (c >= '0' && c <= '9')
        {
            auto tmp_ptr = --text;

            value = parser_.getNumber(tmp_ptr);

            for (auto c = *text; (c >= '0' && c <= '9')
                                  || c == '.'
                                  || c == ','; )
            {
                ++text;
                c = *text; // skipping digits
            }

            return Token::Number;
        }
        if (c >= 'A' && c <= 'z')
        {
            constant_name += c;
            for (auto c = *text; c >= 'A' && c <= 'z'; )
            {
                constant_name += c;
                ++text;
                c = *text; // skipping digits
            }
            if (constants.count(constant_name) > 0)
            {
                value = (T)constants[constant_name];
                return Token::Const;
            }
        }
        return Token::Invalid;
    }
    text--;
    return Token::End;
}

template <typename T, typename Device>
T Calculator<T, Device>::prim()
{
    T answer = 1.;
    const char* text_ptr = text;
    Token token = getToken();

    if (token == Token::Minus)
    {
        answer = -1.;
        token = getToken();
    }

    if (token == Token::Number || token == Token::Const){
        answer *= value;
    }
    else if (token == Token::OpenBracket)
    {
        level++;
        value = this->token_sequence(text);
        answer *= value;
    }
    else
    {
        text = text_ptr;
        throw "Input error: unsupported query.";
    }
     return answer;
}


template <typename T, typename Device>
T Calculator<T, Device>::_prim()
{
    T answer = 0.;
    const char* text_ptr = text;
    Token token = getToken();

    if (token == Token::Number || token == Token::Const)
    {
        answer = value;
    }
    else if (token == Token::Minus)
    {
        token = getToken();
        if (token == Token::Number || token == Token::Const)
            answer = -value;
        else
        {
            text = text_ptr;
            throw "Input error: unsupported query.";
        }
    }
    else
    {
        text = text_ptr;
        throw "Input error: unsupported query.";
    }
     return answer;
}

template <typename T, typename Device>
T Calculator<T, Device>::term()
{
    T answer = prim();
    const char* text_ptr = text;
    Token token = getToken();
    T divisor = 0.;

    while (token != Token::End)
    {
        switch (token)
        {
        case Token::Div:
            divisor = prim();
            if (almost_equal(divisor,0))
                throw "Operation error: division by zero.";
            answer /= divisor;
            text_ptr = text;
            break;
        case Token::Mul:
            answer *= prim();
            text_ptr = text;
            break;
        default:
            text = text_ptr;
            return answer;
        }
        token = getToken();
    }
    return answer;
}

template <typename T, typename Device>
T Calculator<T, Device>::token_sequence(const char*& text)
{
    this->text=text;

    T answer = term();
    Token token = getToken();

    while (token != Token::End)
    {
        switch (token)
        {
        case Token::ClosBracket:
            if (level > 0)
            {
                level--;
                value = answer;
                return answer;
            }
            else
                throw "Input error: unbalansed parentheses.";
        case Token::Minus:
            answer -= term();
            break;
        case Token::Plus:
            answer += term();
            break;
        default:
            throw "Input error: unsupported operation.";
        }
        token = getToken();
     }
    if (level != 0)
        throw "Input error: unbalansed parentheses.";
    return answer;
}

#endif // CALCULATOR_H






