#include <iostream>
#include <string>
#include <stdexcept>
#include <unordered_map>
#include <sstream> 

using namespace std;
//Возможные токены
enum class Token{
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End,
    Left_bracket,
    Right_bracket,
    Constant
};

//Константы
unordered_map < std::string, double > contants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

class calc{
    public:
    Token current;
    calc(const char*& str){
        if (validator(str)==true){
            std::cout << expr(str, current) << std::endl;
            exit (0);
        }
        else{
            throw std::invalid_argument("Input is not validate");
        }

    };
    private:
    //Текущее состояние
    int number;
    char* string_constant = new char[2];



    //Определение очередного токена
    Token getToken(const char*& text){
        while (const auto c = *text++){
            switch (c){
                case ' ': continue;
                case '-': return Token::Minus;
            	case '+': return Token::Plus;
            	case '*': return Token::Mul;
            	case '/': return Token::Div;
            	case '(': return Token::Left_bracket;
            	case ')': return Token::Right_bracket;
            }
            if (c >= '0' && c <= '9'){
                 for (auto c = *text; c >= '0' && c <= '9'; c = *text++)
                 ;
                 return Token::Number;
            }
            if (isalpha(c)) {
                string_constant[0] = c;
                *text++;
                while (auto c = *text++) {
                    if (isalnum(c))
                    string_constant[1] = c;
                    

                }

                //text.putback(c);
                return current=Token::Constant;
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
            case Token::Left_bracket:{
                 cout << text <<endl;
                 double result = expr(text, current);
	        if (current != Token::Right_bracket){
                    throw std::invalid_argument("No right bracket are available");
                }
                return result;
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
    
    //Старт обработки строки... Сложение и вычитаение самых крупных структур, состоящих из      перемноженных или деленных друг на друга чисел 
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
                case Token::Right_bracket:{
                     return left;
                }
                default:{



                    throw std::invalid_argument("Don't have this symbols");
		
	        }
            }
        }
    }







    bool validator(const char* str){
            int counter_of_brackets=0;
            int i=0;
            /*for(unsigned int i=0; i<str.length(); i++)*/
            char x = str[0];
            while (x){
                if (!((x>= '0' && x <= '9')||(x ==' ')||x =='+'|| x =='-'|| x =='*'|| x =='/'||x =='('|| x ==')'|| x =='P'|| x =='e')){
                    cout<<"No this symbol" << endl;
                    return false;

                }
                else {}
                if ( x =='(') counter_of_brackets++; else {}
                if ( x ==')') counter_of_brackets--; else {}
                if (counter_of_brackets<0) { 
                    cout<<"Error number of brackets #1"<< endl;
                    return false;}
                else {}
                if ( x =='P' && str[i+1]!='i'){
                    cout<<"Error with Pi #1" << endl;
                    return false;
                    }
                else if (x =='P' && str[i+1]=='i'){
                   i++;
                   
                   continue;
                }
                else {
                    if (x == 'P')
                    {
                        cout<<"Error with Pi #2" << endl;
                        return false;
                    }
                }
                i++;
                x = str[i];
            }
            if (counter_of_brackets!=0) {
                cout<<"Error number of brackets #2" << endl;
                exit(1);
                return false;
            }
            return true;

    };
};
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
               calc cal (text);
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
