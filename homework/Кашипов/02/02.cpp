#include <iostream>
#include <string>
#include <stdexcept>

//Возможные токены
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

//Извлекаем число с нужным знаком
int prim(const char*& text, Token& current_token){
    //Создаем копию указателя на строку, чтобы потом
    //можно было легко получить число
    auto old_text = text;
    current_token = getToken(text);
    switch (current_token){
        case Token::Number:{
            //Вынимаем число из строки 
            int number = std::stoi (std::string (old_text, text)); 
            current_token = getToken(text);
            return number;
        }
        case Token::Minus:{
            //Предыдущий токен - операция, это токен - минус
            //Вывод: имеем унарный минус
            return -prim(text, current_token);
        }
        case Token::End:{
            //В конце строки стоит операция, а не число - ошибка
            throw std::invalid_argument("Operation at the end of file");
        }
        default:
            throw std::invalid_argument("Invalid syntax");
    }
}

//Умножение и перемножение структур поменьше, которые состоят из числа, либо числа со знаком минус
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
                if (right < 1e-10 && right > -1e-10) 
                    throw std::invalid_argument("Division by 0");
                left /= right;
                break;
            }
            default:
                return left;
        }
    }
}
    
//Старт обработки строки... Сложение и вычитаение самых крупных структур, состоящих из перемноженных или деленных друг на друга чисел 
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
            default:{
                throw std::invalid_argument("Don't have this simbols");
		
	    }
        }
    }
}

int main(int argc, char* argv[]){
    switch(argc){
        case 1:{
            std::cout << "No arguments. For instance: \n" << 
                argv[0] << "      \"5+6-7*9 --1\"" << std::endl;
            return -1;
        }
        case 2:{
            const char* text = argv[1];
            Token curr_token;
            try{
               //expr() -> term() -> prim(), на чем основан собственно рекурсивный спуск
               std::cout << expr(text, curr_token) <<std::endl;
            }
            catch (const std::invalid_argument& answer){
                std::cout << answer.what() << std::endl;
                return -1;
            }
            break;
        }
        default:
            std::cout << "So many aruments!" << std::endl;
    }
    return 0;
}
