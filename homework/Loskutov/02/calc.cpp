#include <iostream>

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
    Null      //Пустой токен
};

//Функция возвращает следующий токен в нашем выражении
Token getToken(const char*& text) {
    while (const auto c = *text) {
        switch (c) {
            case ' ':
                text++;
                continue;
            case '-':
                text++;
                return Token::Minus;
            case '+':
                text++;
                return Token::Plus;
            case '*':
                text++;
                return Token::Mul;
            case '/':
                text++;
                return Token::Div;
        }
        if ((c >= '0') && (c < '9')) {
            return Token::Number;
        }
        return Token::Invalid;
    }
    return Token::End;
}

//Функция реализует часть грамматики:
//prim = number
//    | -number
//number = [0-9]+
int prim(const char*& text, Token *token) {
    *token = getToken(text);
    if ((*token == Token::End) || (*token == Token::Invalid)) {
        *token = Token::Invalid;
        return 0;
    }
    if (*token == Token::Minus) {
        *token = getToken(text);
        if (*token != Token::Number) {
            *token = Token::Invalid;
            return 0;
        }
        char buf[20];
        int i = 0;
        for (;(*text >= '0') && (*text <= '9'); ++text) {
            buf[i] = *text;
            i++;
        }
        *token = Token::Null;
        return -atoi(buf);
    }
    if (*token != Token::Number) {
        *token = Token::Invalid;
        return 0;
    }
    char buf[20];
    int i = 0;
    buf[0] = *text;
    for (;(*text >= '0') && (*text <= '9'); ++text) {
        buf[i] = *text;
        i++;
    }
    *token = Token::Null;
    return atoi(buf);
}

//Функция реализует часть грамматики:
//term = prim
//    | term * prim
//    | term / prim
int term(const char*& text, Token* token) {
    int res = prim(text, token);
    if (*token == Token::Null) {
        *token = getToken(text);
        if (*token == Token::Invalid) {
            return res;
        }
    }
    if (*token == Token::Mul) {
        *token = Token::Null;
        int num = term(text, token);
        if (*token == Token::Invalid) {
            return res;
        }
        res *= num;
    } else if (*token == Token::Div) {
        *token = Token::Null;
        int num = term(text, token);
        if (*token == Token::Invalid) {
            return res;
        }
        res /= num;
    }
    return res;
}

//Функция реализует часть грамматики:
//expr = term
//    | expr + term
//    | expr - term
int expr(const char*& text, Token* token) {
    int res = term(text, token);
    if (*token == Token::Invalid) {
        return res;
    }
    if (*token == Token::Null) {
        *token = getToken(text);
        if (*token == Token::Invalid) {
            return res;
        }
    }
    if (*token == Token::Plus) {
        *token = Token::Null;
        int num = expr(text, token);
        if (*token == Token::Invalid) {
            return res;
        }
        res += num;
    } else if (*token == Token::Minus) {
        *token = Token::Null;
        int num = expr(text, token);
        if (*token == Token::Invalid) {
            return res;
        }
        res -= num;
    }
    return res;
}

int main(int argc, const char * argv[]) {
    if (argc < 2) {
        cout << "No expression!" << endl;
        return 0;
    }
    const char* text = argv[1];
    Token *token = (Token*)malloc(sizeof(Token*));
    *token = Token::Null;
    int res = expr(text, token);
    if (*token == Token::Invalid) {
        cout << "Bad expression!" << endl;
    } else {
        cout << res << endl;
    }
    free(token);
    return 0;
}
