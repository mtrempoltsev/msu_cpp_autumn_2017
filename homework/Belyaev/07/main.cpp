#include <iostream>
#include <unordered_map>
#include <cstring>
#include <limits>
#include <cmath>
#include <cfloat> 
#include <memory>

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
  static long bigType;
  static bool checkType(long &a){
  	if(a > NumericTraits<int>::max || a < - NumericTraits<int>::max){
  		return false;
  	}
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
  if(tmp < -NumericTraits<long>::max || tmp > NumericTraits<long>::max)
  	return false;
  value = tmp;
  return true;
  }
  static long long bigType;
  static bool checkType(long long &a){
  	if(a > NumericTraits<long>::max || a < - NumericTraits<long>::max){
  		return false;
  	}
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
  	if(tmp > NumericTraits<double>::max){
  		return false;
  	}
  	value = tmp;
  	return true;
  }


  static bool checkType(long double &a){
  	if(!std::isfinite((double)a)){//Требуется, потому что в случае проверки NumericTraits 0.0 не пройдет проверку.
  		return false;
  	}
  	if(a > NumericTraits<double>::max || a < - NumericTraits<double>::max){
  		return false;
  	}
  	return true;
  }
  static long double bigType;
};


template <class T, class Parser>
class calculator {
public:
    calculator(char *text){
        expression = text;
    }
    calculator(){

    }

    T calculate(char *text){
    	expression = text;
    	T result = expr(expression);
        return result;
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
            std::string var;
            var.assign(text-length, length);
            return constants.at(var) * (2 * isPositive - 1);
        }
        if (thisToken.thisToken != Tokenizer::Token::Number) {
            throw std::runtime_error("Syntax error");
        }
        T c;
        if(!Parser::parse(text, c))
    		throw std::runtime_error ("Syntax error: number can not be read");


        return c * (2 * isPositive - 1);


    }

    T term(const char *&text) {
        T c = prim(text);
        thisToken.updateToken(text);
        while (thisToken.thisToken == Tokenizer::Token::Mul || thisToken.thisToken == Tokenizer::Token::Div) {

            decltype(Parser::bigType) test = 0.0;
            if (thisToken.thisToken == Tokenizer::Token::Mul) {
 
            	test = (decltype(Parser::bigType))c * (decltype(Parser::bigType))prim(text);
            	if(Parser::checkType(test)){
            		c = T(test);
            	}else throw std::range_error("Result left type limits");

                thisToken.updateToken(text);
            } else {
                T divider = prim(text);
                if (divider) {

                	test = (decltype(Parser::bigType))c / (decltype(Parser::bigType))divider;
            		if(Parser::checkType(test)){
            			c = T(test);
            		}else throw std::range_error("Result left type limits");

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
        	decltype(Parser::bigType) test = 0.0;
            if (thisToken.thisToken == Tokenizer::Token::Plus) {

            	test = (decltype(Parser::bigType))c + (decltype(Parser::bigType))term(text);
            		if(Parser::checkType(test)){
            			c = T(test);
            		}else throw std::range_error("Result left type limits");

                thisToken.updateToken(text);
            } else if (thisToken.thisToken == Tokenizer::Token::Minus) {

            	test = (decltype(Parser::bigType))c - (decltype(Parser::bigType))term(text);
            		if(Parser::checkType(test)){
            			c = T(test);
            		}else throw std::range_error("Result left type limits");

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
                    { "Pi", M_PI },
                    { "e", M_E }
            };
    Tokenizer thisToken;

};


void checkErrors(bool a){
	if(!a)
		std::cout << "error" << std::endl;
	return;
}

bool isEqual(const double &left, const double &right){
	return fabs(left - right) < DBL_EPSILON;
}




int main(int argc, char* argv[]) {

    char Expr1[] = "3+3";
    char Expr2[] = "9/2*2";
    char Expr3[] = "Pi*-e";
    char Expr4[] = "8*Pi";

    //MUST BE FINE

    try{

    //DOUBLE

    checkErrors(isEqual(calculator<double,Parser<double>>().calculate(Expr1),(double)6));
    checkErrors(isEqual(calculator<double,Parser<double>>().calculate(Expr2),(double)9));
    checkErrors(isEqual(calculator<double,Parser<double>>().calculate(Expr3),(double)-M_PI*M_E));
    checkErrors(isEqual(calculator<double,Parser<double>>().calculate(Expr4),(double)M_PI*8));

    //INT

    checkErrors(calculator<int,Parser<int>>().calculate(Expr1)==6);
    checkErrors(calculator<int,Parser<int>>().calculate(Expr2)==8);
    checkErrors(calculator<int,Parser<int>>().calculate(Expr3)==-6);
    checkErrors(calculator<int,Parser<int>>().calculate(Expr4)==24);

    //LONG

    checkErrors(calculator<long,Parser<long>>().calculate(Expr1)==6);
    checkErrors(calculator<long,Parser<long>>().calculate(Expr2)==8);
    checkErrors(calculator<long,Parser<long>>().calculate(Expr3)==-6);
    checkErrors(calculator<long,Parser<long>>().calculate(Expr4)==24);
    

    }catch(const std::range_error& error){
        std::cout << error.what() << std::endl;
    }catch(const std::runtime_error& error){
        std::cout << error.what() << std::endl;
    }
    catch(...){
        std::cout << "SMTH ELSE IS WRONG" << std::endl;
    }

    //ERRORS
    try{
        char errExpr1[] = "2147483647+1";
        calculator<int,Parser<int>>().calculate(errExpr1);
    }catch(const std::range_error& error){
        std::cout << error.what()  << std::endl;
    }catch(const std::runtime_error& error){
        std::cout << error.what()  << std::endl;
    }
    catch(...){
        std::cout << "SMTH ELSE IS WRONG" << std::endl;
    }

    try{
        char errExpr2[] = "2.0";
        calculator<int,Parser<int>>().calculate(errExpr2);
    }catch(const std::range_error& error){
        std::cout << error.what()  << std::endl;
    }catch(const std::runtime_error& error){
        std::cout << error.what()  << std::endl;
    }
    catch(...){
        std::cout << "SMTH ELSE IS WRONG" << std::endl;
    }

    try{
        char errExpr3[] = "9223372036854775807+1";
        calculator<long,Parser<long>>().calculate(errExpr3);
    }catch(const std::range_error& error){
        std::cout << error.what()  << std::endl;
    }catch(const std::runtime_error& error){
        std::cout << error.what()  << std::endl;
    }
    catch(...){
        std::cout << "SMTH ELSE IS WRONG" << std::endl;
    }




    return 0;
}