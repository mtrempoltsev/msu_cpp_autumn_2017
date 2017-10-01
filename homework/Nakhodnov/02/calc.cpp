#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <map>
#include <functional>
#include <exception>
using namespace std;

//объекты данного класса содержит в себе 1 распознаную лексему 
class Token {
public:
    enum Token_Types {
        END,
        PLUS,
        MINUS,
        MULT,
        DIV,
        NUM,
        NONE
    };
    Token_Types type;
    long long int value;
    Token(Token_Types t = Token_Types::NONE, long long int v = 0) :type(t), value(v) {}
    Token(const Token &T) {
        type = T.type;
        value = T.value;
    }
    Token& operator=(const Token &T) {
        if (&T != this) {
            type = T.type;
            value = T.value;
        }
        return *this;
    }
};

//объект данного класса содержит в себе множество операций
class Field {
    using BinaryFunction = function<long long int(long long int, long long int)>;
    map<Token::Token_Types, BinaryFunction> Operations;
public:
    Field() {
        //добавляем простейшие действия - сложение, вычитание, деление, умножение
        Operations[Token::PLUS] = [](long long int a, long long int b) {return a + b;};
        Operations[Token::MINUS] = [](long long int a, long long int b) {return a - b;};
        Operations[Token::MULT] = [](long long int a, long long int b) {return a * b;};
        Operations[Token::DIV] = [](long long int a, long long int b) {
                            if (!b) throw string("Dividion by zero");
                            return a / b;
                        };
    };
    BinaryFunction find_operation(Token::Token_Types T) {
        return Operations.at(T);
    }
};

//данный класс позволяет производить разбиение на лексемы-токены
class Tokenizer{
    const char *S = NULL; //указатель на токенизируемую строку
    int iter = 0; //индекс ещё не обработанного символа в строке S
    int prev_iter = -1; //индекс начала предыдущего токена
    Token prev_token; //в данном объекте хранится токен начинающийся с индекса prev_iter

public:
    Tokenizer(const char * str) : S(str) {}

    Token next_token() {
        if (prev_iter > iter) {
            iter = prev_iter;
            return prev_token;
        }
        prev_iter = iter;
        if (iter > 0 && S[iter - 1] == '\0') return Token(Token::END);
        while (S[iter] == ' ' && S[iter] != '\0') {
            ++iter;
        }
        char *b_iter;
        long long int b_val;
        switch (S[iter++]) {
        case '\0': return Token(Token::END);
        case '+': return Token(Token::PLUS);
        case '-':
            //дополнительно проверяем на унарный минус
            if(S[iter] == ' ') return Token(Token::MINUS); 
            else if (!isdigit(S[iter])) {
                throw string("Undefined lexem: ") + S[iter] + string(" in position: ") + to_string(iter);
            }
            b_val = strtol(S + iter, &b_iter, 10);
            iter = b_iter - S;
            return Token(Token::NUM, -b_val);
        case '*': return Token(Token::MULT);
        case '/': return Token(Token::DIV);
        default:
            --iter;
            if (!isdigit(S[iter])) {
                throw string("Undefined lexem: ") + S[iter] + string(" in position: ") + to_string(iter);
            }
            b_val = strtoll(S + iter, &b_iter, 10);
            iter = b_iter - S;
            return Token(Token::NUM, b_val);
        }
    }

    void push_token(Token &T) {
        iter = prev_iter;
        prev_token = T;
    }
};


//обрабатываем операции с наибольшим приоритетом
long long int high_priority(Tokenizer &Tkz, Field &F) {
    long long int left = 0;
    Token buff = Tkz.next_token();
    left = buff.value;
    while ((buff = Tkz.next_token()).type != Token::NONE &&
        (buff.type == Token::MULT || buff.type == Token::DIV)) {
        left = F.find_operation(buff.type)(left, Tkz.next_token().value);
    }
    if (buff.type == Token::PLUS || buff.type == Token::MINUS) Tkz.push_token(buff);
    return left;
}

//обрабатываем операции с наименьшим приоритетом
long long int low_priority(Tokenizer &Tkz, Field &F) {
    long long int left = 0;
    Token buff;
    left = high_priority(Tkz, F);
    while ((buff = Tkz.next_token()).type != Token::NONE &&
        (buff.type == Token::PLUS || buff.type == Token::MINUS)) {
        left = F.find_operation(buff.type)(left, high_priority(Tkz, F));
    }
    return left;
}



int main(int argc, char *argv[])
{
    if (argc > 2) {
        cout << "Too much arguments" << endl;
        return 0;
    }
    else if (argc < 2) {
        cout << "Too few arguments" << endl;
        return 0;
    }
    if (!strcmp(argv[1], "--help")) {
        cout << "To get computation use expression like that:\n./calc \"1 + 2 * 7\"" << endl;
        return 0;
    }
    Field F({});
    Tokenizer Tkz(argv[1]);
    long long int answer;
    try {
        answer = low_priority(Tkz, F);
        cout << answer << endl;
    }
    catch (string& exc) {
        cout << exc << endl;
    }
    catch (exception& exc) {
        cout << exc.what() << endl;
    }
    return 0;
}

