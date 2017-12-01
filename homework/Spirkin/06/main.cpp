#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <unordered_map>
#include <cstring>
#include <limits>

using namespace std;

std::unordered_map<std::string, double> contants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

enum class Token
{
  Invalid,
  Minus,
  Plus,
  Mul,
  Div,
  Number,
  End,
  LP,
  RP,
  EXP,
  Pi,
  Null
};

template<class T> // Шаблоны свойств
struct NumericTraits{};

template<>
struct NumericTraits<int>
{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
};

template<>
struct NumericTraits<long>
{
  static constexpr long min = std::numeric_limits<long>::min();
  static constexpr long max = std::numeric_limits<long>::max();
};

template<>
struct NumericTraits<double>
{
  static constexpr double min = std::numeric_limits<double>::min();
  static constexpr double max = std::numeric_limits<double>::max();
};


template<class T>
struct Parser
{};

template<>
struct Parser<int>
{
  static int Get(const char*& text)
  {
    --text;
    auto f = *text;
    int num = 0;
    while (f >= '0' && f <= '9') // преобразование многозначного числа в целый тип
    {
      num = num * 10 + f - '0';
      ++text;
      f = *text;
    }

    if( num < NumericTraits<int>::min || num > NumericTraits<int>::max )
      cout << "Overflow" << endl;

    return num;
  }
};

template<>
struct Parser<long>
{
  static long Get(const char*& text)
  {
    --text;
    auto f = *text;
    long num = 0;
    while (f >= '0' && f <= '9') // преобразование многозначного числа в целый тип
    {
      num = num * 10 + f - '0';
      ++text;
      f = *text;
    }

    if( num < NumericTraits<long>::min || num > NumericTraits<long>::max )
      cout << "Overflow" << endl;

    return num;
  }
};

template<>
struct Parser<double>
{
  static double Get(const char*& text)
  {
    double fraction = 10;
    --text;
    auto f = *text;
    double num = 0;
    if (f == '.')
      throw "Not a number";

    while (f >= '0' && f <= '9') // преобразование многозначного числа в целый тип
    {
      num = num * 10 + f - '0';
      ++text;
      f = *text;
    }

    if (f == '.')
    {
      ++text;
      f = *text;
      if (f >= '0' && f <= '9')
        while (f >= '0' && f <= '9') // преобразование многозначного числа в целый тип
        {
          num += (f - '0') / fraction;
          fraction *= 10;
          ++text;
          f = *text;
        }
      else
        throw "No numbers after point";
    }

    if ( num < NumericTraits<double>::min || num > NumericTraits<double>::max )
      cout << "Overflow" << endl;
    return num;
  }
};

template<class T>
class Calculator {
public:
  Calculator(); // Конструктор на случай если текста нет
  Calculator(const char*& text); // Конструктор
  T expression(); // вызов метода для подсчета выражения калькулятора записанного в text
  int count;
private:
  Token getToken();
  T primary();
  T term();
  Token token;
  const char* text;
};

// переменнная text - идентификатор позиции
// token - показывает что находится на этой позиции
template<class T>
Calculator<T>::Calculator() {
  text = nullptr;
  token = Token::Null;
  count = 0;
}

template<class T>
Calculator<T>::Calculator(const char*& txt) {
  token = Token::Null;
  text = txt;
  count = 0;
}

// считывает токен, меняет позицию прочитанного текста и записывает число в
// глобальную переменную
template<class T>
Token Calculator<T>::getToken()
{
  while (auto c = *text++)
  {
    switch (c)
    {
      case ' ': continue;
      case '-': return Token::Minus;
      case '+': return Token::Plus;
      case '*': return Token::Mul;
      case '/': return Token::Div;
      case '(': return Token::LP;
      case ')': return Token::RP;
    }
    if (c >= '0' && c <= '9')
    {
      return Token::Number;
    }
    if (c == 'e')
    {
      return Token::EXP;
    }
    if (c == 'P') {
      c = *text++;
      if (c == 'i'){
        return Token::Pi;
      }
      else
        return Token::Invalid;
    }
    return Token::Invalid;
  }
  return Token::End;
}
//        логика вычислений:
// <выражение> = <слагаемое> {+ <слагаемое>}  ||
// <слагаемое> = <множитель> {+ <множитель>}  ||
// <множитель> = <число> {+ <выражение>}      ||

template<class T>
T Calculator<T>::expression () { // выражение
  T left = term();
  while (token != Token::End) {
    switch(token)
    {
      case Token::Plus:{
        left += term();
        break;
      }
      case Token::Minus:{
        left -= term();
        break;
      }
      case Token::End:{
        return left;
      }
      default:
        return left;
    }
  }
  return left;
}

template<class T>
T Calculator<T>::term () { // слагаемое
  T left_term = primary();
  while (token != Token::End){
    switch(token){
      case Token::Mul:{
        left_term *= primary();
        break;
      }
      case Token::Div:{
        T denominator = primary();
        if (denominator == 0) {
          throw "Error! Can't devide by zero";
          break;
        }
        else {
          left_term /= denominator;
          break;
        }
      }
        case Token::Plus:{
          return left_term;
        }
        case Token::Minus:{
          return left_term;
        }
        case Token::End:{
          return left_term;
        }
  case Token::RP:{
    count--;
    return left_term;
  }
        default:
          throw "Invalid symbol";
          return left_term;
    }
  }
  return left_term;
}

template <class T>
T Calculator<T>::primary () { // множитель
  token = getToken();
  switch(token){
    case Token::Number: {
      T num = Parser<T>::Get(text);
      token = getToken();
      return num;
      }
      case Token::EXP: { // случай экспоненты
        T num = 0;
        num = contants["e"];
        token = getToken();
        return num;
      }
      case Token::Pi: { // случай константы Пи
        T num = 0;
        num = contants["Pi"];
        token = getToken();
        return num;
      }
      case Token::LP:{ // обработка скобок
        count++;
        T num = expression(); // считается выражение внутри скобок
        if (token != Token::RP) {
          throw "Error!";
          break;
        }
        token = getToken();
        return num;
      }
      case Token::Null:{
        T num = 0;
        token = getToken();
        return num;
      }
      case Token::Minus:{ // унарный минус
      return -primary();
    }
    default:
      throw "Invalid symbol";
      return 1;
  }
}


int main(int argc, char* argv[])
{
    if (argc==1){
        cout<<"empty expression"<<endl;
        return 0;
    }
  try
  {

    const char* text = argv[1];

    Calculator<double> calc(text);
    double result = calc.expression();


    if (calc.count != 0){
      cout << "Invalid" << endl;
      return 1;
    }
    cout << result << endl;
      return 0;
  }
  catch (const char* str){
    cout << str << endl;
    return 1;
  }
}
