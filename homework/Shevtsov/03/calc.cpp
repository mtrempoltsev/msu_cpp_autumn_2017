#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>
#include <unordered_map>
#include <cstring>

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

class Calculator {
public:
  Calculator(); // Конструктор на случай если текста нет
  Calculator(const char*& text); // Конструктор
  int expression(); // вызов метода для подсчета выражения калькулятора записанного в text
  int count;
private:
  Token getToken();
  int primary();
  int term();
  Token token;
  const char* text;
};

// переменнная text - идентификатор позиции
// token - показывает что находится на этой позиции

Calculator::Calculator() {
  text = nullptr;
  token = Token::Null;
  count = 0;
}

Calculator::Calculator(const char*& txt) {
  token = Token::Null;
  text = txt;
  count = 0;
}

// считывает токен, меняет позицию прочитанного текста и записывает число в
// глобальную переменную
Token Calculator::getToken()
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


int Calculator::expression () { // выражение
  int left = term();
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

int Calculator::term () { // слагаемое
  int left_term = primary();
  while (token != Token::End){
    switch(token){
      case Token::Mul:{
        left_term *= primary();
        break;
      }
      case Token::Div:{
        int denominator = primary();
	if (denominator == 0) {  // Обработка случая деления на ноль
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

int Calculator::primary () { // множитель
  token = getToken();
  switch(token){
    case Token::Number: {
      --text;
      auto f = *text;
      int num = 0;
      while (f >= '0' && f <= '9') // преобразование многозначного чила в целый тип
      {
        num = num * 10 + f - '0';
	      ++text;
	      f = *text;
      }
      token = getToken();
      return num;
      }
      case Token::EXP: { // случай экспоненты
        double num = 0;
        num = contants["e"];
        token = getToken();
        return num;
      }
      case Token::Pi: { // случай константы Пи
        double num = 0;
        num = contants["Pi"];
        token = getToken();
        return num;
      }
      case Token::LP:{ // обработка скобок
        count++;
        int num = expression(); // считается выражение внутри скобок
        if (token != Token::RP) {
          throw "Error!";
      	  break;
        }
        token = getToken();
        return num;
      }
      case Token::Null:{
        int num = 0;
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
  try
  {
    //const char* text = "1 * 6 + 3 / 2 - 2 * 2";
    const char* text = argv[1];
    Calculator calc(text);
    int result = calc.expression();


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
