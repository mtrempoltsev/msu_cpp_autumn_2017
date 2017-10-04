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

//Получение токенов
Token getToken(stringstream& input, int& number, Token& current){
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
double prim(stringstream& input, bool get, int& number, Token& current) {

        if (get) {
                getToken(input,number,current);
        }

        switch (current) {
        case Token::Number: {
                int v = number;
                getToken(input,number,current);
                return v;
        }

        case Token::Minus:
                return -prim(input, true,number,current);
        default:
               cout<<"There is some mistake in input"<<endl;
               exit(1);
        }
}
//Умножение
double term(stringstream& input, bool get, int& number, Token& current) {
        double left = prim(input, get,number,current);

        while(true) {
                switch (current) {
                case Token::Mul:
                        left *= prim(input, true,number,current);
                        break;
                case Token::Div:
                        if (double d = prim(input, true,number,current)) {
                                left /= d;
                                break;
                        }
                default:
                        return left;
                }
        }
}
//Сложение
double expr(stringstream& input, bool get, int& number, Token& current) {
        double left = term(input, get,number,current);

        while(true) {
                switch (current) {
                case Token::Plus:
                        left += term(input, true,number,current);
                        break;
                case Token::Minus:
                        left -= term(input, true, number,current);
                        break;
                default:
                        return left;
                }
        }
}
//Первичная проверка выражения
bool validator(string str){
    for(char& c : str) {
        if (!((c>= '0' && c <= '9')||(c==' ')||c=='+'||c=='-'||c=='*'||c=='/')){
            return false;
        }
    }
    return true;

}
int main(int argc, char* argv[]){
        //Получить строку
        string str= argv[1];
        if (validator(str)==true){
            stringstream input;
            input<<str;

            //Число и текущее состояние токена
            int number;
            Token current;
            getToken(input,number,current);
            cout << expr(input, false,number,current) << endl;
            return 0;
        }
        else{
             cout<<"Input is not validate"<<endl;
             return 1;
        }

}


