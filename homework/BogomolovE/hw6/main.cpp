#include <iostream>
#include <unordered_map>
#include <limits>

std::unordered_map<std::string, double> constants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

using namespace std;

enum class Token // enum class cannot be cast to type int
{
    Invalid, // 0
    Minus, // 1
    Plus, // 2
    Mul, // 3
    Div, // 4
    Number, // 5
    End, // 6
    Constant, //7
    LBracket,
    RBracket
};

template <class T>
struct NumericTraits
{};

template <>
struct NumericTraits<int>
{
    constexpr static int max = std::numeric_limits<int>::max();
    constexpr static int min = std::numeric_limits<int>::min();
};

template <>
struct NumericTraits<long>
{
    constexpr static long max = std::numeric_limits<long>::max();
    constexpr static long min = std::numeric_limits<long>::min();
};

template <>
struct NumericTraits<double>
{
    constexpr static double max = std::numeric_limits<double>::max();
    constexpr static double min = std::numeric_limits<double>::min();
};

template <class T>
struct Parser
{};

template <>
struct Parser<int>
{
  static bool parse(const char *&text, int &value)
  {
    long tmp = atol(text);
    if ((tmp < NumericTraits<int>::min) || (tmp > NumericTraits<int>::max)){
      return false;
    }
    value = tmp;
    return true;
  }
};

template <>
struct Parser<long>
{
  static bool parse(const char *&text, long &value)
  {
    double tmp = strtold(text, NULL);
    std::cout << tmp <<std::endl;
    std::cout << NumericTraits<long>::min <<std::endl;
    if ((tmp < NumericTraits<long>::min) || (tmp > NumericTraits<long>::max)){
      return false;
    }
    value = tmp;
    return true;
  }
};

template <>
struct Parser<double>
{
  static bool parse(const char *&text, double &value)
  {
    long double tmp = strtold(text, NULL);
    if ((tmp < NumericTraits<double>::min)||(tmp > NumericTraits<double>::max)){
      return false;
    }
    value = tmp;
    return true;
  }
};

template <class T, class ParserT>
class Calculator
{
public:
    Token token; // is for token
    const char *prev; // is for pointing the current
    //cannot change pointed memory but  can change the pointer with effect outside of the function
    //this function gets token from string passing the spaces between tokens
    int opened_brackets = 0;
    Calculator(const char *&text)
    {

      prev = text;
      getToken(text); // initialize token


    }


    // Returns if token is end of line
    int isEnd(void)
    {
       return (token == Token::End);
    }
    // Returns if token is Invalid
    int isInvalid(void)
    {
       return (token == Token::Invalid);
    }


    int isConstant(void)
    {
        return(token == Token::Constant);
    }

    void getToken(const char *&text)
    {
        while (const auto c = *text++){
          // memorize the start of the token and missing spaces
            prev = text-1;
            switch (c){
                case ' ': continue;
                case '-': token = Token::Minus; return;
                case '+': token = Token::Plus; return;
                case '*': token = Token::Mul; return;
                case '/': token = Token::Div; return;
                case '(': token = Token::LBracket; return;
                case ')': token = Token::RBracket; return;
            }
            if (c >= '0' && c <= '9'){
                for (auto c = *text; c >= '0' && c <= '9';){ //skip digits
                    text++;
                    c = *text;
                }

                token = Token::Number;
                return;
            }

            if (isalpha(c)){
                for (auto c = *text; isalpha(c);){ //skip letters
                    text++;
                    c = *text;
                }
                token = Token::Constant;
                return;
            }
            token = Token::Invalid;
            return;
        }
        token =  Token::End;
        return;
    }


    T getNumber(const char *&text)
    {
      T value;
      if (!ParserT::parse(text,value)){
        std::cout << "Out of range of the type" << std::endl;
        throw 0;
      }
      return value;
    }

    //this function returns primary expression
    T prim(const char *&text)
    {

        getToken(text);// read token
        switch (token){ // if number then take it from position prev
            case Token::Number:{
                T number = getNumber(prev);
                getToken(text);
                if (isInvalid() || isConstant()) throw 0; // if invalid token throw an exception

                return number;
            }
            case Token::Minus:{
                T number = prim(text);
                return -number;
            }
            case Token::Constant:{
                //read constant name
                auto name = std::string(prev, text - prev);
                auto iter = constants.find(name);

                // if there's no such constant throwing an exception
                if (iter == constants.end()){
                    throw 0;
                }

                int number = constants[name];

                getToken(text);
                if (isInvalid()) throw 0;

                return number;
            }
            case Token::LBracket: {

                //calculating an expression inside the brackets
                opened_brackets++;
                int result = expr(text);
    						if (token != Token::RBracket) {
    							cout<<"Unbalanced brackets"<<endl;
    							throw 0;
    						}
                opened_brackets--;
    						getToken(text);
    						return result;
            }
            default: throw 0;
        }
    }

    T term(const char *&text)
    {
        T left = prim(text); // get recursively part result of the part of expression
        while(1){
            switch (token){
                case Token::Mul:{
                    left *= prim(text);
                    break;
                }
                case Token::Div:{
                    int divisor = prim(text);
                    if (divisor == 0) throw 0;
                    left /= divisor;
                    break;
                }
                case Token::RBracket: {
                    if (!opened_brackets){
                          throw 0;
                    }
                }
                default: return left;
            }
        }
    }

    T expr(const char *&text)
    {
        T left = term(text); // get recursively part result of the part of expression
        while(1){
            switch (token){
                case Token::Plus:{
                    left += term(text);
                    break;
                }
                case Token::Minus:{
                    left -= term(text);
                    break;
                }
                default: return left;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    const char *text = "1 + 2";

    if (argc == 1) { // of there are no arguments print message
      std::cout << "Empty expression"  << std::endl;
      return 2;
    }
    text = argv[1];
    auto prev = text;

    Calculator<double, Parser<double> > calc  = Calculator<double, Parser<double> >(text);

    if (calc.isEnd()){ // the same if there is an empty string argument
        std::cout << "Empty expression"  << std::endl;
        return 2;
    }
    if (!calc.isInvalid()){// if token is valid then calculate an expression
        text = prev; // point main text pointer to the start of string
        calc.prev = prev;
        try
        {
            std::cout << calc.expr(text) << std::endl;
        }
        catch (int e)
        {
            std::cout << "Invalid input"  << std::endl;
            return 1;
        }
    } else {
        std::cout << "Invalid input"  << std::endl;
        return 1;
    }
    return 0;
}
