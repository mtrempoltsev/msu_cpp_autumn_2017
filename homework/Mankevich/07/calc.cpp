#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <limits>
#include <cstring>


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
    Calc(char*& str): text(str), is_sub_text(0) {};
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
    std::string str = "20 + 3 - 700*-9";
    const char *txt = &str[0];
    Calc<int, Parser<int>> text(txt);
    check (text.calculate() == 6323);
}

void check_double(){
    std::string str = "2.5 + 3.5 - 7.5 * -9";
    const char *txt = &str[0];
    Calc<double, Parser<double>> text(txt); 
    check (text.calculate() == 73.5);
}

void check_long(){
    std::string str = "2000000000000 + 35 - 705*-9";
    const char *txt = &str[0];
    Calc<long, Parser<long>> text(txt); 
    check (text.calculate() == 2000000006380);
}

int main(int argc, char* argv[]){
    try{
        std::cout << "Check int values: " << std::endl;
        check_int();
        std::cout << "Check double values: " << std::endl;
        check_double();
        std::cout << "Check long values: " << std::endl;
        check_long();
    }
    catch (const std::invalid_argument& ia){
        std::cout << ia.what() << std::endl;
        return -1;
    }
    return 0;
}