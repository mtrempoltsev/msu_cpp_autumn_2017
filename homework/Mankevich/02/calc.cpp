#include <iostream>
#include <string>
#include <stdexcept>

//Вычисление численного значания выражения методом рекурсивного спуска

//Перечесление возможных токенов
enum class Token{
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
};

//Определение очередного токена
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
double prim(const char*& text, Token& current_token){
    //Создаем копию указателя на строку, чтобы потом
    //можно было легко получить число
    auto old_text = text;
    current_token = getToken(text);
    switch (current_token){
        case Token::Number:{
            //Вынимаем число из строки 
            double num = std::stoi(std::string (old_text, text)); 
            //После инициализации числа определяем следующий токен
            //для определения последующей операции
            current_token = getToken(text);
            return num;
        }
        case Token::Minus:{
            //Предыдущий токен - операция, это токен - минус
            //Вывод: имеем унарный минус
            return -prim(text, current_token);
        }
        case Token::End:{
            //В конце строки стоит операция, а не число - ошибка
            throw std::invalid_argument("Invalid syntax: operation at end of file");
        }
        default:
            //Неправильный синстаксис строки
            //Например два '+' подряд
            throw std::invalid_argument("Invalid syntax");
    }
}

//Выполняются операции деления и умножения
double term(const char*& text, Token& current_token){
    double left = prim(text, current_token);
    while (1){
        switch (current_token){
            case Token::Mul:{
                left *= prim(text, current_token);
                break;
            }
            case Token::Div:{
                //Операция деления и обработка ошибки - деление на 0
                double right = prim(text, current_token);
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
    
//Старт обработки строки/сложение и вычетание
double expr(const char*& text, Token& current_token){
    double left = term(text, current_token);
    while (1){
        switch (current_token){
            case Token::Plus:{
                left += term(text, current_token);
                break;
            }
            case Token::Minus:{
                left -= term(text, current_token);
                break;
            }
            case Token::End:{
                return left;
            }
            default:
                throw std::invalid_argument("Wrong simbols");
        }
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        std::cout << "Wrong input! Try again. Example: \n" << 
            argv[0] << " \"3 * 4 * 7 - -6\"" << std::endl;
        return -1;
    }
    const char* text = argv[1];
    Token curr_token;
    try{
        //Рекурсия операций expr() -> term() -> prim()
        std::cout << expr(text, curr_token) <<std::endl;
    }
    catch (const std::invalid_argument& ia){
        //std::cout << ia.what() << std::endl;
        return -1;
    }
    return 0;
}