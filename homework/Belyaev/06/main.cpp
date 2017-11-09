#include <iostream>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <cmath> 

class Tokenizer {
public:
    void updateToken(
            const char *&text) //Указатель будет сдвигаться. Текст - это ссылка на указатель константной char. Не смогу менять то, что внутри, но указатель смогу.
    {
        while (const auto c = *text++) {//Когда встретит 0 - остановится. Приоритет выше у инкремента - прибавим сначала, но разыменуем предыдущий указатель
            switch (c) {
                case ' ':
                    continue;
                case '-':
                    thisToken = Token::Minus;
                    return;
                case '+':
                    thisToken = Token::Plus;
                    return;
                case '*':
                    thisToken = Token::Mul;
                    return;
                case '/':
                    thisToken = Token::Div;
                    return;
                case '(':
                    thisToken = Token::LBrace;
                    return;
                case ')':
                    thisToken = Token::RBrace;
                    return;
            }
            if (c >= '0' && c <= '9') {
                thisToken = Token::Number;
                return;
            }
            if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
                thisToken = Token::Const;
                return;
            }
            throw std::runtime_error("Invalid Symbol"); // Вместо return Token::Invalid;
        }
        thisToken = Token::End;
        return;
    }

    enum class Token {
        Minus,
        Plus,
        Mul,
        Div,
        Number,
        End,
        Const,
        LBrace,
        RBrace
    };

    Token thisToken;
};

template <class T, class Parser>
class calculator {
public:
    calculator(const char *&text){
        expression = text;
    }

    void calculate(){
        std::cout << expr(expression) << std::endl;
    }

private:
    T prim(const char *&text) {
        bool isPositive = true;
        thisToken.updateToken(text);
        --text;
        if (thisToken.thisToken == Tokenizer::Token::Minus) { //Checking if number is positive/negative
            isPositive = false;
            thisToken.updateToken(++text); //Checking what goes after subtraction symbol
            --text;
        }
        if(thisToken.thisToken == Tokenizer::Token::LBrace){//If there are braces - create loop to calculate expr in braces.
            ++text;
            T c = expr(text, true);
            return c * (2 * isPositive - 1);
        }
        if (thisToken.thisToken == Tokenizer::Token::End) {
            return 0;
        }
        if (thisToken.thisToken == Tokenizer::Token::Const){
            int length = 1;
            ++text ;
            while ((*text >= 'A' && *text <= 'Z') || (*text >= 'a' && *text <= 'z')) {
                length += 1;
                ++text;
            }
            auto* var = new std::string();
            var->assign(text-length, length);
            return constants.at(*var) * (2 * isPositive - 1);
        }
        if (thisToken.thisToken != Tokenizer::Token::Number) {
            throw std::runtime_error("Syntax error");
        }
        T c;
        //decltype(Parser::parse())
        /*
        T c = T(*text - '0');
        while (*(++text) >= '0' && *text <= '9') {
            c = c * 10 + T(*text - '0');
        }*/
        if(!Parser::parse(text, c))
    		throw std::runtime_error ("Syntax error: number can not be read");


        return c * (2 * isPositive - 1);


    }

    T term(const char *&text) {
        T c = prim(text);
        thisToken.updateToken(text);
        while (thisToken.thisToken == Tokenizer::Token::Mul || thisToken.thisToken == Tokenizer::Token::Div) {
            if (thisToken.thisToken == Tokenizer::Token::Mul) {
                c = c * prim(text);
                thisToken.updateToken(text);
            } else {
                T divider = prim(text);
                if (divider) {
                    c = c / divider;
                    thisToken.updateToken(text);
                } else throw std::runtime_error("Division by zero");
            }
        }
        --text;
        return c;
    }


    T expr(const char *&text, bool fromPrim = false) {
        T c = term(text);
        thisToken.updateToken(text);
        while (thisToken.thisToken != Tokenizer::Token::End && thisToken.thisToken != Tokenizer::Token::RBrace && thisToken.thisToken != Tokenizer::Token::LBrace) {
            if (thisToken.thisToken == Tokenizer::Token::Plus) {
                c += term(text);
                thisToken.updateToken(text);
            } else if (thisToken.thisToken == Tokenizer::Token::Minus) {
                c -= term(text);
                thisToken.updateToken(text);
            } else
                throw std::runtime_error("Syntax error");
        }
        if (thisToken.thisToken == Tokenizer::Token::LBrace){
            throw std::runtime_error("Brace syntax error");
        }
        if (thisToken.thisToken != Tokenizer::Token::RBrace || fromPrim){
            return c;
        }
        throw std::runtime_error("Brace syntax error");
    }
    const char* expression;
    std::unordered_map<std::string, double> constants =
            {
                    { "Pi", 3.14 },
                    { "e", 2.7 }
            };
    Tokenizer thisToken;

};
template <class T>
struct Parser
{
};
template <class T>
struct NumericTraits
{
};

template<> struct NumericTraits<double>{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();
};

template <>
struct NumericTraits<int>{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
};

template <>
struct NumericTraits<long>{
    static constexpr long min = std::numeric_limits<long>::min();
    static constexpr long max = std::numeric_limits<long>::max();
};

template<>
struct Parser<int>
{
  static bool parse(const char*& text, int& value)
  {
  	long tmp = long(*text - '0');
        while (*(++text) >= '0' && *text <= '9') {
            tmp = tmp * 10 + long(*text - '0');
        }
  if(tmp < NumericTraits<int>::min || tmp > NumericTraits<int>::max)
  	return false;
  value = tmp;
  return true;
  }
};

template<>
struct Parser<long>
{
  static bool parse(const char*& text, long& value)
  {
  	long long tmp = (long long)(*text - '0');
        while (*(++text) >= '0' && *text <= '9') {
            tmp = tmp * 10 + (long long)(*text - '0');
        }
  if(tmp < NumericTraits<long>::min || tmp > NumericTraits<long>::max)
  	return false;
  value = tmp;
  return true;
  }
};

template<>
struct Parser<double>
{
  static bool parse(const char*& text, double& value)
  {
  	long double tmp = (long double)(*text - '0');
        while (*(++text) >= '0' && *text <= '9') {
            tmp = tmp * 10 + (long double)(*text - '0');
        }
        if((*text == '.') && (*(++text) >= '0' || *(text) <= '9')){
        	tmp += (long double)(*text - '0') / 10;
        	int power = -1;
        	while (*(++text) >= '0' && *text <= '9') {
        		--power; 
            	tmp +=  (long double)(*text - '0') * pow(10.0, power);
        	}
    	}
  if(!std::isfinite(tmp)){//Требуется, потому что в случае проверки NumericTraits 0.0 не пройдет проверку.
  	return false;
  }
  value = tmp;
  return true;
  }
};




int main(int argc, char* argv[]) {

    if(argc<2){
        throw std::runtime_error("No input expression");
    }
    const char* expression = argv[1];
    //calculator<double, Parser<double>>* myCalc = new calculator<double,Parser<double>>(expression);

    calculator<int, Parser<int>>* myCalc = new calculator<int,Parser<int>>(expression);
    myCalc->calculate();
    return 0;
}