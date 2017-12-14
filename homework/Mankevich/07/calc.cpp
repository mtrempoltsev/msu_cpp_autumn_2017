#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <limits>
#include <cstring>
#include <math.h>


enum class Token{
    Right, // ')' 
    Left,  // '('
    Pi,
    E,
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
};

std::unordered_map<std::string, double> constants =
        {
                {"Pi", 3.14},
                {"e",  2.7}
        };

template <class T>
struct NumericTraits{

};

template <>
struct NumericTraits<int>{
    static constexpr int min = std::numeric_limits<int>::min();
    static constexpr int max = std::numeric_limits<int>::max();
};

template <>
struct NumericTraits<double>{
    static constexpr double min = std::numeric_limits<double>::min();
    static constexpr double max = std::numeric_limits<double>::max();
};

template <>
struct NumericTraits<long>{
    static constexpr long min = std::numeric_limits<long>::min();
    static constexpr long max = std::numeric_limits<long>::max();
};

template <class T>
struct Parser{

};

template <>
struct Parser<int>{
    bool parse(const std::string& text, int& value){
        long double p = stod(text);
        if (p > NumericTraits<int>::max || p < NumericTraits<int>::min)
            return false;
        value = (int) p;
        return true;
    }
};

template <>
struct Parser<double>{
    bool parse(const std::string& text, double& value){
        long double p = stod(text);
        if (p > NumericTraits<double>::max || p < NumericTraits<double>::min)
            return false;
        value = (double) p;
        return true;
    }
};

template <>
struct Parser<long>{
    bool parse(const std::string& text, long& value){
        long double p = stod(text);
        if (p > NumericTraits<long>::max || p < NumericTraits<long>::min)
            return false;
        value = (long) p;
        return true;
    }
};

template <class T, class Parser>
class Calc{
public:
    Calc(const char*& str): text(str), is_sub_text(0) {};
    Calc(const char*& str, bool check): text(str), is_sub_text(1) {};
    ~Calc() {};
    T calculate();
private:
    T expr();
    T term();
    T prim();
    Token getToken();
    
    const char*& text;
    Token current_token;
    bool is_sub_text; };

template <class T, class Parser>
Token Calc<T, Parser>::getToken(){
    while (const auto c = *text++){
        switch (c){
            case ' ': continue;
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case '*': return Token::Mul;
            case '/': return Token::Div;
            case '(': return Token::Left;
            case ')': return Token::Right;
            case 'e': return Token::E;
            case 'P':{
                if (*text++ == 'i') return Token::Pi;
                else return Token::Invalid; 
            }
        }
        if (c >= '0' && c <= '9'){
            for (auto c = *text; c >= '0' && c <= '9'; c = *(++text))
                ;
            if (*text == '.'){  
                if (*(text + 1) >= '0' && *(text + 1) <= '9')
                    for (auto c = *(++text); c >= '0' && c <= '9'; c = *(++text))
                        ;
                else
                    return Token::Invalid;
            }
            return Token::Number;
        }
        return Token::Invalid;
    }
    return Token::End;
}

template <class T, class Parser>
T Calc<T, Parser>::prim(){
    auto old_text = text;
    current_token = getToken();
    
    switch (current_token){
        case Token::Left:{
            Calc sub_text(text, 1);
            T num = sub_text.calculate();
            current_token = getToken();
            return num;
        }
        case Token::Pi:{
            current_token = getToken();
            return constants["Pi"];
        }
        case Token::E:{
            current_token = getToken();
            return constants["e"];
        }
        case Token::Number:{
            T num = T();
            if (!Parser().parse(std::string (old_text, text), num)){
                throw std::invalid_argument("Wrong type of values");
            } 
            current_token = getToken();
            return num;
        }   
        case Token::Minus:{
            return -prim();
        }
        case Token::End:{
            throw std::invalid_argument("Invalid syntax: operation at end of file");
        }
        default:
            throw std::invalid_argument("Invalid syntax");
    }
}

template <class T, class Parser>
T Calc<T, Parser>::term(){
    T left = prim();
    while (1){
        switch (current_token){
            case Token::Mul:{
                left *= prim();
                break;
            }
            case Token::Div:{
                T right = prim();
                if (right < 1e-6 && right > -1e-6) 
                    throw std::invalid_argument("Division by 0");
                left /= right;
                break;
            }
            default:
                return left;
        }
    }
}

template <class T, class Parser>
T Calc<T, Parser>::expr(){
    T left = term();
    while (1){
        switch (current_token){
            case Token::Plus:{
                left += term();
                break;
            }
            case Token::Minus:{
                left -= term();
                break;
            }
            case Token::Right:{
                if (is_sub_text) return left;
                else throw std::invalid_argument("Wrong with right simbol");
            }
            case Token::End:{
                if (is_sub_text) throw std::invalid_argument("Wrong with right simbol"); 
                else return left;
            }
            default:
                throw std::invalid_argument("Wrong simbols 1");
        }
    }
}

template <class T, class Parser>
T Calc<T, Parser>::calculate(){
    return expr();
}

void check(bool value){
    if (!value)
        std::cerr << "Error " << std::endl;;
}

void check_int(){
    const char *test1 = "20 + 3 - 5";
    const char *test2 = "20 * 3 / 10";
    const char *test3 = "10 - (-7 + 5) * (-1)";
    const char *test4 = "2 * Pi + (Pi - 7 * 11) * -2";
    Calc<int, Parser<int>> text1(test1);
    Calc<int, Parser<int>> text2(test2);
    Calc<int, Parser<int>> text3(test3);
    Calc<int, Parser<int>> text4(test4);
    
    check (text1.calculate() == 18);
    check (text2.calculate() == 6);
    check (text3.calculate() == 8);
    check (text4.calculate() == 154);
}

void check_double(){
    const char *test1 = "20.7 + 3.12 - 5.77";
    const char *test2 = "20.6 * 3.2 / 10";
    const char *test3 = "10.22 - (-7 + 5) * (-1)";
    const char *test4 = "2 * Pi + (Pi - 7 * 11) * -2 * e";
    Calc<double, Parser<double>> text1(test1);
    Calc<double, Parser<double>> text2(test2);
    Calc<double, Parser<double>> text3(test3);
    Calc<double, Parser<double>> text4(test4);
    
    check (fabs(text1.calculate() - 18.05) < 1e-6);    
    check (fabs(text2.calculate() - 6.592) < 1e-6);
    check (fabs(text3.calculate() - 8.22) < 1e-6);
    check (fabs(text4.calculate() - 405.124) < 1e-6);
}

void check_long(){
    const char *test1 = "3000000000 + 7 - 5";
    const char *test2 = "20 * 3 / 10";
    const char *test3 = "10 - (-7 + 5) * (-1)";
    const char *test4 = "2 * Pi + (Pi - 7 * 11) * -2";
    Calc<long, Parser<long>> text1(test1);
    Calc<long, Parser<long>> text2(test2);
    Calc<long, Parser<long>> text3(test3);
    Calc<long, Parser<long>> text4(test4);
    
    check (text1.calculate() == 3000000002);
    check (text2.calculate() == 6);
    check (text3.calculate() == 8);
    check (text4.calculate() == 154);
}

int main(int argc, char* argv[]){
    const char* txt = argv[1];
    Calc<double, Parser<double>> calc(txt);
    try{
        std::cout << calc.calculate() << std::endl;
    }
    catch (const std::invalid_argument& ia){
        std::cout << ia.what() << std::endl;
        return -1;
    }
    return 0;
}