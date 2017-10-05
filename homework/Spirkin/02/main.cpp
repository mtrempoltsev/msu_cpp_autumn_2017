#include <iostream>
#include <string>


enum class Token{
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
};

//определение токена на месте указателя
Token getToken(const char*& text){
    while (const auto c = *text++){
        switch (c){
            case ' ': continue;
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case '*': return Token::Mul;
            case '/': return Token::Div;
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

//Вынимаетм из строки токены и обрабатываем самые приоритетные функции
//В нашем случае - только унарный минус
int prim(const char*& str, Token& state){
    //Создаем копию указателя на строку, чтобы потом
    //можно было легко получить число
    auto old_str = str;
    state = getToken(str);
    switch (state){
        case Token::Number:{
            //Вынимаем число из строки
            double num = std::stoi(std::string (old_str, str));
            //После инициализации числа определяем следующий токен
            //для определения последующей операции
            state = getToken(str);
            return num;
        }
        case Token::Minus:{
            //Предыдущий токен - операция, это токен - минус
            //Вывод: имеем унарный минус
            return -prim(str,state);
        }
        case Token::End:{
            exit(-1);
        }
        default:
           exit(-1);
    }
}

int term(const char*& str, Token& state){
    double prefix = prim(str, state);
    while (true){
        switch (state){
            case Token::Mul:{
                prefix *= prim(str, state);
                break;
            }
            case Token::Div:{
                //Операция деления и обработка ошибки - деление на 0
                double suffix = prim(str, state);
                if (suffix < 1e-6 && suffix > -1e-6) exit(-1);
                prefix /= suffix;
                break;
            }
            default:
                return prefix;
        }
    }
}

int expr(const char*& str,Token& state){
    int prefix=term(str,state);
    while(true){
        switch (state){
            case Token::Plus:{
                prefix += term(str,state);
                break;
            }
            case Token::Minus:{
                prefix -= term(str,state);
                break;
            }
            case Token::End:{
                return prefix;
            }
            default:
                exit(-1);
        }
    }
}



int main(int argc, char* argv[]){
    if (argc != 2){
        return -1;
    }
    const char* str = argv[1];
    Token state;
        try{
            /*Вызов expr(),которая в свою очередь вызовет функцию вычисляющую терм,
             а та в свою очередь вызовет функцию обрабатывающую числа*/
            std::cout << expr(str, state) <<std::endl;
            }
            catch (const std::invalid_argument& ia){
                //std::cout << ia.what() << std::endl;
                return -1;
            }
    return 0;
}

