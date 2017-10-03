#include <iostream>
#include <sstream>
#include <string>
using namespace std;
//Перечисление возможных значений
enum class Token{
                Invalid,
                Minus,
                Plus,
                Mul,
                Div,
                Number,
                End
};
//Число и текущее состояние токена
int number;
Token current;
//Получение токенов
Token getToken(stringstream& input){
        char c;
        do{
                input.get(c);
        } while (isspace(c));

        switch (c){
                case 0:	return current = Token::End;
                case '-':return current=Token::Minus;
                case '+':return current = Token::Plus;
                case '*':return current = Token::Mul;
                case '/':return current = Token::Div;
                default:
                {
                        if (c >= '0' && c <= '9'){
                                input.putback(c);
                                input >> number;
                                return current = Token::Number;
                        }
                        else
                        {
                                return current = Token::Invalid;
                        }
                }
        }

        return current = Token::End;
}
//Обработка первичных значений
double prim(stringstream& input, bool get) {

        if (get) {
                getToken(input);
        }

        switch (current) {
        case Token::Number: {
                int v = number;
                getToken(input);
                return v;
        }

        case Token::Minus:
                return -prim(input, true);

        }
}
//Сложение
double term(stringstream& input, bool get) {
        double left = prim(input, get);

        while(true) {
                switch (current) {
                case Token::Mul:
                        left *= prim(input, true);
                        break;
                case Token::Div:
                        if (double d = prim(input, true)) {
                                left /= d;
                                break;
                        }
                default:
                        return left;
                }
        }
}
//Умножение
double expr(stringstream& input, bool get) {
        double left = term(input, get);

        while(true) {
                switch (current) {
                case Token::Plus:
                        left += term(input, true);
                        break;
                case Token::Minus:
                        left -= term(input, true);
                        break;
                default:
                        return left;
                }
        }
}
int main(int argc, char* argv[]){
        //Получить строку
        string str= argv[1];
        stringstream input;
        input<<str;
        getToken(input);
        cout << expr(input, false) << endl;

        return 0;
}


