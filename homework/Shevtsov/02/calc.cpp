#include <iostream>
#include <stdio.h>
#include <string>
#include <cctype>

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


int global_num = 0;
int error = 0;
// считывает токен, меняет позицию прочитанного текста и записывает число в глобальную переменную
Token getToken(const char*& text)
{
  while (const auto c = *text++)
  {
    switch (c)
    {
      case ' ': continue;
      case '-': return Token::Minus;
      case '+': return Token::Plus;
      case '*': return Token::Mul;
      case '/': return Token::Div;
    }
    if (c >= '0' && c < '9')
    {
      --text;
      auto f = *text;
      int num = 0;
      while (f >= '0' && f <= '9') // преобразование многозначного чила в целый тип
      {
        num = num * 10 + f - '0';
	++text;
	f = *text;
      }
      global_num = num;
      return Token::Number;
    }
    return Token::Invalid;
  }
  return Token::End;
}
//        логика вычислений:
// <выражение> = <слагаемое> {+ <слагаемое>}  ||
// <слагаемое> = <множитель> {+ <множитель>}  ||
// <множитель> = <число> {+ <выражение>}      ||


int term (Token& token, const char*& text);
int primary (Token& token, const char*& text);

int expression (Token& token, const char*& text) { // выражение
  int left = term(token, text);
    //cout << "expression error" << error << endl;
    if (error == 1)
    {
      return left;
    }
    while (token != Token::End) {
      switch(token)
      {
        case Token::Plus:{
          left += term(token, text);
	  if (error == 1)
	  {
	    return left;
	  }
        break;
      }
      case Token::Minus:{
        left -= term(token, text);
        if (error == 1)
	{
	  return left;
	}
        break;
      }
      case Token::End:{
        return left;
      }
      default:
	//cout << "Invalid symbole" << endl;
	error = 1;
	return left;
      }
    }
    return left;
}

int term (Token& token, const char*& text) { // слагаемое
  int left_term = primary(token, text);
	//cout << "term error:" << error << endl;
	if (error == 1)
	{
	  //cout << "if-cycle" << endl;
          return left_term;
	}
  while (token != Token::End){
    switch(token){
      case Token::Mul:{
        left_term *= primary(token, text);
        break;
      }
      case Token::Div:{
	int denominator = primary(token, text);
	if (denominator == 0) {  // Обработка случая деления на ноль
	  cout << "Error! Can't devide by zero" << endl;
	  error = 1;
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
      default:
        cout << "Invalid symbol" << endl;
	error = 1;
	return left_term;
     }
  } 
  return left_term;
}

int primary (Token& token, const char*& text) { // множитель
  token = getToken(text);
	//cout << int(token) << endl;
  switch(token){
    case Token::Number: {
      int v = global_num;
      token = getToken(text);
    return v;
    }
    case Token::Minus:{ // унарный минус
      return -primary(token, text);
    }
    /*
    case Token::End:{
      cout << "End";
      int v = global_num;
      return v;
    }
    */
    default:
      cout << "Invalid symbol" << endl;
      error = 1;
      int v = global_num;
      return v;
    }
}


// переменнная text - идентификатор позиции
// token - показывает что находится на этой позиции
// number - сюда записывается число

int main(int argc, char* argv[])
{
  //const char* text = "1 * 6 + 3 / 2 - 2 * 2";
  const char* text = argv[1];
  //cout << text << endl;
  Token token; // преобразовали текст в токены
  int result = expression(token, text); // вычислелние выражения
  if (error == 1)
  {
    return 1;
  }
  cout << result << endl;
  return 0;
}
