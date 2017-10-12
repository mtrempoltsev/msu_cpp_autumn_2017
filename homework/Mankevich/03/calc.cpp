#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>

//Перечисление возможнык токенов
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


class Calc{
public:
    Calc(const char*& str): text(str), is_sub_text(0) {};
    Calc(const char*& str, bool check): text(str), is_sub_text(1) {};
    ~Calc() {};
    double calculate();
private:
    double expr();
    double term();
    double prim();
    Token getToken();
    
    const char*& text;
    Token current_token;
    bool is_sub_text; // Является ли строка объекта скобочным выражение(подстрокой): (...)
                      // другого объекта
};

//Взятие очередного токена
Token Calc::getToken(){
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
            for (auto c = *text; c >= '0' && c <= '9'; c = *text++)
                ;
            return Token::Number;
        }
        return Token::Invalid;
    }
    return Token::End;
}

//Вынимаетм из строки токены и обрабатываем самые приоритетные функции:
//унарный минус, скобочные выражения, числовые значения
double Calc::prim(){
    auto old_text = text;
    current_token = getToken();
    
    switch (current_token){
        case Token::Left:{
            Calc sub_text(text, 1);
            double num = sub_text.calculate();
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
            double num = std::stoi(std::string (old_text, text)); 
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

//Операции умножения и деления
double Calc::term(){
    double left = prim();
    while (1){
        switch (current_token){
            case Token::Mul:{
                left *= prim();
                break;
            }
            case Token::Div:{
                double right = prim();
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

//Операции сложения и вычитания, выход из скобочной подстроки
double Calc::expr(){
    double left = term();
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

//Старт вычисления значения 
double Calc::calculate(){
    return expr();
}

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << "Wrong input! Try again. Example: \n" << 
            argv[0] << " \"3 * 4 * 7 - -6\"" << std::endl;
        return -1;
    }
    
    const char* txt = argv[1];
    Calc text(txt);
    try{
        std::cout << text.calculate() <<std::endl;
    }
    catch (const std::invalid_argument& ia){
        //std::cout << ia.what() << std::endl;
        return -1;
    }
    return 0;
}