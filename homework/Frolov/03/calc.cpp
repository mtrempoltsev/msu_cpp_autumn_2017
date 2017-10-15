#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

using namespace std;
//Перечисление возможных значений
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
}; //Возможные константы
unordered_map<std::string, double> contants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
class calc{
    public:

    calc(string& str){
         if (validator(str)==true){
            stringstream input;
            input<<str;
            getToken(input);
            cout << expr(input, false) << endl;
            exit (0);
        }
        else{
             cout<<"Input is not validate"<<endl;
             exit(1);
        }

    };
    private:
            //Текущее состояние
            int number;
            Token current;
            string string_constant;
            //Получение токенов
        Token getToken(stringstream& input){
                char c;
                do{
                        input.get(c);
                } while (isspace(c));

                switch (c){
                        case 0:    return current = Token::End;
                        case '-':return current=Token::Minus;
                        case '+':return current = Token::Plus;
                        case '*':return current = Token::Mul;
                        case '/':return current = Token::Div;
                        case '(':return current = Token::Left_bracket;
                        case ')':return current = Token::Right_bracket;
                        default:
                        {
                                if (c >= '0' && c <= '9'){
                                        input.putback(c);
                                        input >> number;
                                        return current = Token::Number;
                                }
                                else if (isalpha(c)) {
                                            string_constant = c;
                                            while (input.get(c) && isalnum(c)) {
                                              string_constant.push_back(c);
                                            }
                                            input.putback(c);
                                            return current=Token::Constant;
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
                    case Token::Constant: {
                        double& result = contants[string_constant];
                        getToken(input);
                    return result;
                    }
                    case Token::Minus:
                            return -prim(input, true);
                    case Token::Left_bracket: {
                        double result = expr(input, true);
                        if (current != Token::Right_bracket) {
                            cout<<"No right bracket are available";
                            exit(1);
                        }
                        getToken(input);
                        return result;
                };
                    default:
                           cout<<"There is some mistake in input"<<endl;
                           exit(1);

            }
        };
        //Умножение
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
                                else{
                                    cout<<"Divide by 0"<<endl;
                                    exit(1);
                                }
                        default:
                                return left;
                        }
                }
        }
        //Сложение
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
        };
        //Первичная проверка выражения
        bool validator(string str){
            int counter_of_brackets=0;
            for(unsigned int i=0; i<str.length(); i++) {
                if (!((str[i]>= '0' && str[i] <= '9')||(str[i]==' ')||str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='('||str[i]==')'||str[i]=='P'||str[i]=='e')){

                    return false;
                }
                if (str[i]=='(') counter_of_brackets++;
                if (str[i]==')') counter_of_brackets--;
                if (counter_of_brackets<0) return false;
                if (str[i]=='P'&&i<(str.length()-1)){
                        if (!(str[i+1]=='i')) return false;
                        else{
                                i++;
                                continue;
                            }

                }else if(str[i]=='P'&&i==(str.length()-1)){
                        return false;
                    }
                else{}
            }
            if (counter_of_brackets!=0) {
                    cout<<"Error number of brackets";
                    exit(1);
                    return false;
                }
            return true;

        };

};
int main(int argc, char* argv[]){
        //Получить строку
        string str= argv[1];
    calc cal(str);
}



