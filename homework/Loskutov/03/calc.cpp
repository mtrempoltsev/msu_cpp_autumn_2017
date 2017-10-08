#include <iostream>
#include <stdexcept>

using namespace std;

//Класс enum, который описывает возможные токены,
//которые мы можем встретить когда будем идти по выражению
enum class Token {
    Invalid,  //Неверное выражение
    Minus,    //Знак минус
    Plus,     //Знак плюс
    Mul,      //Знак умножение
    Div,      //Знак деления
    Number,   //Число
    End,      //Конец выражения
    Null,     //Пустой токен
    BktLeft,
    BktRight,
    Pi,       //Число Pi
    e         //Число e
};

class Calculator {
public:
    Token *token;
    char* text;
    int res;
    int pos;
    bool bkt;
    
    Calculator() {
        token = (Token*)malloc(sizeof(Token*));
        *token = Token::Null;
        text = nullptr;
        res = 0;
        pos = 0;
    }
    
    Calculator(const char* text_) {
        token = (Token*)malloc(sizeof(Token*));
        *token = Token::Null;
        text = (char*)malloc((strlen(text_)+1)*sizeof(char));
        int count = 0;
        for (int i = 0; i < strlen(text_); i++) {
            text[i] = text_[i];
            if (text[i] == '(') {
                count++;
            }
            if (text[i] == ')') {
                count--;
            }
        }
        text[strlen(text_)] = '\0';
        if (count != 0) {
            throw invalid_argument("Bad expression!");
        }
        res = 0;
        pos = 0;
        bkt = false;
    }
    
    ~Calculator() {
        free(text);
    }
    
    void getToken() {
        while (const auto c = text[pos]) {
            switch (c) {
                case ' ':
                    pos++;
                    continue;
                case '-':
                    pos++;
                    *token = Token::Minus;
                    return;
                case '+':
                    pos++;
                    *token = Token::Plus;
                    return;
                case '*':
                    pos++;
                    *token = Token::Mul;
                    return;
                case '/':
                    pos++;
                    *token = Token::Div;
                    return;
                case '(':
                    pos++;
                    *token = Token::BktLeft;
                    return;
                case ')':
                    pos++;
                    *token = Token::BktRight;
                    return;
            }
            if ((c >= '0') && (c < '9')) {
                *token = Token::Number;
                return;
            }
            if (c == 'P') {
                pos++;
                if (text[pos] == 'i') {
                    pos++;
                    *token = Token::Pi;
                    return;
                }
            }
            if (c == 'e') {
                pos++;
                *token = Token::e;
                return;
            }
            throw invalid_argument("Bad expression!");
        }
        *token = Token::End;
    }
    
    //Функция реализует часть грамматики:
    //prim = number
    //    | -number
    //number = [0-9]+
    int prim() {
        if (*token == Token::End) {
            throw invalid_argument("Bad expression!");
        }
        if (*token == Token::Minus) {
            getToken();
            if (*token == Token::Pi) {
                *token = Token::Null;
                return -3;
            }
            if (*token == Token::e) {
                *token = Token::Null;
                return -2;
            }
            if (*token != Token::Number) {
                throw invalid_argument("Bad expression!");
            }
            char *buf;
            buf = (char*)calloc(20, sizeof(char));
            int i = 0;
            for (; (text[pos] >= '0') && (text[pos] <= '9'); ++pos) {
                buf[i] = text[pos];
                i++;
            }
            buf[i] = '\0';
            int num = atoi(buf);
            free(buf);
            *token = Token::Null;
            return -num;
        }
        if (*token == Token::Pi) {
            *token = Token::Null;
            return 3;
        }
        if (*token == Token::e) {
            *token = Token::Null;
            return 2;
        }
        if (*token != Token::Number) {
            throw invalid_argument("Bad expression!");;
        }
        char *buf;
        buf = (char*)calloc(20, sizeof(char));
        int i = 0;
        buf[0] = text[pos];
        for (; (text[pos] >= '0') && (text[pos] <= '9'); ++pos) {
            buf[i] = text[pos];
            i++;
        }
        buf[i] = '\0';
        int num = atoi(buf);
        free(buf);
        *token = Token::Null;
        return num;
    }
    
    
    //Функция реализует часть грамматики:
    //bkts = ( expr)
    //    | number
    int bkts() {
        getToken();
        if (*token == Token::BktLeft) {
            *token = Token::Null;
            bkt = true;
            expr();
        } else if (*token == Token::BktRight) {
            *token = Token::Null;
        } else {
            return prim();
        }
        *token = Token::Null;
        return res;
    }
    
    //Функция реализует часть грамматики:
    //term = bkts
    //    | term * bkts
    //    | term / bkts
    void term() {
        int left = bkts();
        if (*token == Token::Null) {
            getToken();
        }
        while ((*token == Token::Mul) || (*token == Token::Div)) {
            if (*token == Token::Mul) {
                *token = Token::Null;
                int right = bkts();
                left *= right;
            } else if (*token == Token::Div) {
                *token = Token::Null;
                int right = bkts();
                if (right == 0) {
                    throw invalid_argument("Bad expression!");
                }
                left /= right;
            }
            getToken();
        }
        res = left;
    }
    
    //Функция реализует часть грамматики:
    //expr = term
    //    | expr + term
    //    | expr - term
    void expr() {
        term();
        if (*token == Token::Null) {
            getToken();
        }
        if (*token == Token::Plus) {
            *token = Token::Null;
            int num = res;
            expr();
            res += num;
        } else if (*token == Token::Minus) {
            *token = Token::Null;
            int num = res;
            expr();
            res -= num;
        }
    }
    
    int getResult() {
        return res;
    }
};

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        cout << "No expression!" << endl;
        return 1;
    }
    if (argc > 2) {
        cout << "Too many arguments!" << endl;
        return 1;
    }
    const char* text = argv[1];
    int result = 0;
    try {
        Calculator calc(text);
        calc.expr();
        result = calc.getResult();
    } catch(invalid_argument& e) {
        cout << e.what() << endl;
        return 1;
    }
    cout << result << endl;
    return 0;
}
