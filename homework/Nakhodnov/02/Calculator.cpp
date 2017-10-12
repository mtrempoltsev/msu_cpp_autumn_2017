#include <iostream>
#include <string>

using namespace std;

enum Token
{
    PLUS,
    MINUS,
    MUL,
    DIV,
    NUMBER,
    END
};

using lli = long long int;

// В случае возникновения ошибки выводим сообщение msg и завершаем работу с кодом 1
void printError(string msg) {
    cerr << msg << endl;
    exit(1);
}


/*
    Выделяем из строки число <number>:
        <number> ::= <digit>|<number><digit>
        <digit> ::= 0|1|2|3|4|5|6|7|8|9
*/
char *getNumber(char *S, lli &value) {
    value = 0;
    while (*S && isdigit(*S)) {
        value *= 10;
        value += (*S++ - '0');
    }
    return S;
}

// Получаем первый токен из строки S
char *getToken(char *S, Token &T, lli &value) {
    while (*S && isspace(*S)) {
        ++S;
    }
    if (!*S) {
        T = Token::END;
        return S;
    }
    switch (*S) {
    case '+':
        T = Token::PLUS;
        return ++S;
    case '-':
        T = Token::MINUS;
        return ++S;
        break;
    case '/':
        T = Token::DIV;
        return ++S;
    case '*':
        T = Token::MUL;
        return ++S;
    default:
        char *S_temp = getNumber(S, value);
        if (S_temp == S) printError(string("Incorrect symbol: \'") + *S + string("\'"));
        T = Token::NUMBER;
        return S_temp;
    }

}

/*
    Вычисляем значение лексической единицы <prim>:
        <prim> ::= <number>|-<number>
*/
char * getPrim(char *S, lli &value) {
    Token T;
    S = getToken(S, T, value);
    if (T == Token::MINUS) {
        S = getToken(S, T, value);
        if (T != Token::NUMBER) printError(string("Invalid sequence of tokens"));
        value *= -1;
        return S;
    }
    else if (T != Token::NUMBER) printError(string("Invalid sequence of tokens"));
    return S;
}


/*
    Вычисляем значение лексической единицы <term>:
        <term> ::= <prim>|<term> * <prim>|<term> / <prim>
    Т.е. выполняем обработку операций деления и вычитания
*/
char * getTerm(char *S, lli &value) {
    lli left;
    Token T;
    S = getPrim(S, value);
    while ((S = getToken(S, T, left))) {
        switch (T) {
        case Token::MUL:
            S = getPrim(S, left);
            value *= left;
            break;
        case Token::DIV:
            S = getPrim(S, left);
            if (!left) printError(string("Dividion by zero"));
            value /= left;
            break;
        case Token::NUMBER:
            printError(string("Invalid sequence of tokens"));
        case Token::END:
            return S;
        default:
            return --S;
        }
    }
    return nullptr;
}

/*
    Вычисляем значение лексической единицы <expr>:
        <expr> ::= <term>|<expr> + <term>|<expr> - <term>
    Т.е. выполняем обработку операций сложения и вычинания
*/
char * getExpr(char *S, lli &value) {
    lli left;
    Token T;
    S = getTerm(S, value);
    while ((S = getToken(S, T, left))) {
        switch (T) {
        case Token::PLUS:
            S = getTerm(S, left);
            value += left;
            break;
        case Token::MINUS:
            S = getTerm(S, left);
            value -= left;
            break;
        case Token::NUMBER:
            printError(string("Invalid sequence of tokens"));
        case Token::END:
            return S;
        default:
            return --S;
        }
    }
    return nullptr;
}



int main(int argc, char *argv[])
{
    /*if(argc != 2) printError(string("Incorrect amount of arguments"));
    lli value;
    getExpr(argv[1], value);*/
    string b;
    cin.getline(b);
    getExpr(b.c_str());
    cout << value << endl;
    return 0;
}

