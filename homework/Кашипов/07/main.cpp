#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <limits>

using namespace std;

//Реализована стратегия parse для различных шаблонов
//Валидация +
template<typename T>
class GetNumber {
};

template<>
class GetNumber<double> {
public:
    bool validate(char c) {
        if ((c >= '0' && c <= '9') || (c == '.')) {
            return true;
        } else {
            return false;
        }
    }

    double parse(stringstream &input) {
        long double result;
        input >> result;
        if ((result > numeric_limits<double>::max()) || (result < numeric_limits<double>::min())) {
            cout << "Your double number out of range";
        }
        return double(result);
    }

};

template<>
class GetNumber<long> {
public:
    bool validate(char c) {
        if ((c >= '0' && c <= '9') || (c == '.')) {
            return true;
        } else {
            return false;
        }
    }

    long parse(stringstream &input) {
        long long result;
        if ((result > numeric_limits<long>::max()) || (result < numeric_limits<long>::min())) {
            cout << "Your long number out of range";
        }
        input >> result;
        return result;
    }


};

template<>
class GetNumber<int> {
public:
    bool validate(char c) {
        if (c >= '0' && c <= '9') {
            return true;
        } else {
            return false;
        }
    }

    int parse(stringstream &input) {
        long long result;
        input >> result;
        if ((result > numeric_limits<int>::max()) || (result < numeric_limits<int>::min())) {
            cout << "Your int number out of range";
        }

        return int(result);
    }

};


enum class Token {
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
                {"Pi", 3.14},
                {"e",  2.7}
        };

template<typename T>
class calc {
public:

    calc(string &str) {
        if (validator(str) == true) {
            stringstream input;
            input << str;
            getToken(input);
            cout << expr(input, false) << endl;
            
            //exit (0);
        } else {
            cout << "Input is not validate" << endl;
            //exit(1);
        }

    };
private:
    //Текущее состояние
    T number;
    Token current;
    string string_constant;
    GetNumber<T> get;

    //Получение токенов
    Token getToken(stringstream &input) {
        char c;
        do {
            input.get(c);
        } while (isspace(c));

        switch (c) {
            case 0:
                return current = Token::End;
            case '-':
                return current = Token::Minus;
            case '+':
                return current = Token::Plus;
            case '*':
                return current = Token::Mul;
            case '/':
                return current = Token::Div;
            case '(':
                return current = Token::Left_bracket;
            case ')':
                return current = Token::Right_bracket;
            default: {
                if (get.validate(c)) {
                    input.putback(c);
                    number = get.parse(input);
                    current = Token::Number;
                    return current;
                } else if (isalpha(c)) {
                    string_constant = c;
                    while (input.get(c) && isalnum(c)) {
                        string_constant.push_back(c);
                    }
                    input.putback(c);
                    return current = Token::Constant;
                } else {
                    return current = Token::Invalid;
                }
            }
        }

        return current = Token::End;
    };

    //Обработка первичных значений
    T prim(stringstream &input, bool get) {

        if (get) {
            getToken(input);
        }
        switch (current) {
            case Token::Number: {
                T v = number;
                getToken(input);
                return v;
            }
            case Token::Constant: {
                double &result = contants[string_constant];
                getToken(input);
                return result;
            }
            case Token::Minus:
                return -prim(input, true);
            case Token::Left_bracket: {
                T result = expr(input, true);
                if (current != Token::Right_bracket) {
					throw runtime_error("No right bracket are available");
                    //cout << "No right bracket are available";
                    //exit(1);
                }
                getToken(input);
                return result;
            };
            case Token::End: {
                cout << number;
            }
            default:
				throw runtime_error("There is some mistake in input");
                //cout << "There is some mistake in input" << endl;
                //exit(1);

        }
    };

    //Умножение
    T term(stringstream &input, bool get) {
        T left = prim(input, get);
        while (true) {
            switch (current) {
                case Token::Mul:
                    left *= prim(input, true);
                    break;
                case Token::Div:
                    if (T d = prim(input, true)) {
                        left /= d;
                        break;
                    } else {
						throw runtime_error("Divide by 0");
                        cout << "Divide by 0" << endl;
                        exit(1);
                    }
                default:
                    return left;
            }
        }
    };

    //Сложение
    T expr(stringstream &input, bool get) {
        T left = term(input, get);
        while (true) {
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
    bool validator(string str) {
        int counter_of_brackets = 0;
        for (unsigned int i = 0; i < str.length(); i++) {
            if (!((str[i] >= '0' && str[i] <= '9') || (str[i] == ' ') || str[i] == '+' || str[i] == '-' ||
                  str[i] == '*' || str[i] == '/' || str[i] == '(' || str[i] == ')' || str[i] == 'P' || str[i] == 'e' ||
                  str[i] == '.')) {
				throw runtime_error("Some unvalid symbols in input");
                return false;
            }
            if (str[i] == '(') counter_of_brackets++;
            if (str[i] == ')') counter_of_brackets--;
            if (counter_of_brackets < 0) {
				throw runtime_error("Some invalid brackets in input");
				return false;
			}
            if (str[i] == 'P' && i < (str.length() - 1)) {
                if (!(str[i + 1] == 'i')) {
					throw runtime_error("Some invalid constants in input");
					return false;
				}
                else {
                    i++;
                    continue;
                }

            } else if (str[i] == 'P' && i == (str.length() - 1)) {
				throw runtime_error("Some invalid constants in input");
                return false;
            } else {}
        }
        if (counter_of_brackets != 0) {
            throw runtime_error("Error number of brackets");
			//cout << "Error number of brackets";
            //exit(1);
            return false;
        }
        return true;
    };
};
//Тесты
bool tests() {
    string str = "25+3.2*(Pi+3)";
    cout << str << "=  ";
    try { calc<double> cal(str); }
    catch (const runtime_error &e) {
        cout << "Invalid" << endl;
        return false;
    }
    str = "1+2*(3+5)";
    cout << str << "=  ";
    try { calc<int> cal(str); }
    catch (const runtime_error &e) {
        cout << "Invalid" << endl;
        return false;
    }
    str = "1314241124141+134123412321";
    cout << str << "=  ";
    try { calc<long> cal(str); }
    catch (const runtime_error &e) {
        cout << "Invalid" << endl;
        return false;
    }
    return true;

}

int main(int argc, char *argv[]) {
    //Тесты
    try{
		tests();
	}
	catch(...){
		cout<<"Something error"<<endl;
		return 1;
	}
	return 0;
}



