#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

using lli = long long int;

// В случае возникновения ошибки выводим сообщение msg и завершаем работу с кодом 1
void printError(string msg) {
    cerr << msg << endl;
    exit(1);
}


// Класс для хранения лексем разбираемой строки
class Token {
public:
    enum TokenTypes {
        PLUS,
        MINUS,
        MUL,
        DIV,
        NUMBER,
        END,
        OP_BREAK,
        CL_BREAK
    };
    TokenTypes type;
    lli value;
    Token(TokenTypes tp = Token::END, lli val = 0) : type(tp), value(val) {}
    Token(const Token& T) {
        if (this != &T) {
            this->type = T.type;
            this->value = T.value;
        }
    }
    Token& operator=(const Token& T) {
        if (this != &T) {
            this->type = T.type;
            this->value = T.value;
        }
        return *this;
    }
};


// Класс, разбивабщий строку на лексемы
class Tokenizer {
public:
    Tokenizer(char *s, unordered_map<string, double> mp) : S(s), constants(mp) {}
    // Получаем первый токен из строки S
    Token getToken() {
        while (*S && isspace(*S)) {
            ++S;
        }
        if (!*S) {
            return Token(Token::END);
        }
        switch (*S) {
        case '+':
            ++S;
            return Token(Token::PLUS);
        case '-':
            ++S;
            return Token(Token::MINUS);
        case '/':
            ++S;
            return Token(Token::DIV);
        case '*':
            ++S;
            return Token(Token::MUL);
        case '(':
            ++balance;
            ++S;
            return Token(Token::OP_BREAK);
        case ')':
            if (!balance) printError(string("Incorrect sequence of breaks"));
            ++S;
            return Token(Token::CL_BREAK);
        default:
            char *S_temp = S;
            Token T = getNumber();
            if (S_temp == S) printError(string("Incorrect symbol: \'") + *S + string("\'"));
            return T;
        }
    }
    void pushOpBack() {
        --S;
    }
private:
    char *S;
    unordered_map<string, double> constants;
    int balance = 0;
    /*
    Выделяем из строки число <number>:
    <number> ::= <digit>|<number><digit>|<const>
    <digit> ::= 0|1|2|3|4|5|6|7|8|9
    <const> ::= Pi|e
    */
    Token getNumber() {
        Token T(Token::NUMBER, 0);
        string buff;
        int iter = 0;
        for (; *(S + iter) && isalpha(*(S + iter)); ++iter) {
            buff += *(S + iter);
        }
        try {
            T.value = constants.at(buff);
            S += iter;
            return T;
        }
        catch (const std::exception&) {
        }
        while (*S && isdigit(*S)) {
            T.value *= 10;
            T.value += (*S++ - '0');
        }
        return T;
    }
};



class Calculator {
public:
    Calculator(char *s, unordered_map<string, double> mp) : Tkz(s, mp){}
    lli getValue() {
        return getExpr();
    }
private:
    Tokenizer Tkz;

    /*
    Вычисляем значение лексической единицы <prim>:
    <prim> ::= <number>|-<number>
    */
    lli getPrim() {
        Token T = Tkz.getToken();
        if (T.type == Token::OP_BREAK) {
            return getExpr();
        }
        if (T.type == Token::MINUS) {
            T = Tkz.getToken();
            if (T.type != Token::NUMBER) printError(string("Invalid sequence of tokens"));
            return T.value * -1;
        }
        else if (T.type != Token::NUMBER) printError(string("Invalid sequence of tokens"));
        return T.value;
    }

    /*
    Вычисляем значение лексической единицы <term>:
    <term> ::= <prim>|<term> * <prim>|<term> / <prim>
    Т.е. выполняем обработку операций деления и вычитания
    */
    lli getTerm() {
        lli left, tmp;
        Token T;
        left = getPrim();
        while (1) {
            T = Tkz.getToken();
            switch (T.type) {
            case Token::MUL:
                left *= getPrim();
                break;
            case Token::DIV:
                tmp = getPrim();
                if (!tmp) printError(string("Dividion by zero"));
                left /= tmp;
                break;
            case Token::NUMBER:
                printError(string("Invalid sequence of tokens"));
            case Token::END:
                return left;
            default:
                Tkz.pushOpBack();
                return left;
            }
        }
        return left;
    }

    /*
    Вычисляем значение лексической единицы <expr>:
    <expr> ::= <term>|<expr> + <term>|<expr> - <term>|'('<expr>')'
    Т.е. выполняем обработку операций сложения и вычинания
    */
    lli getExpr() {
        Token T;
        lli left = getTerm();
        while (1) {
            T = Tkz.getToken();
            switch (T.type) {
            case Token::PLUS:
                left += getTerm();
                break;
            case Token::MINUS:
                left -= getTerm();
                break;
            case Token::NUMBER:
                printError(string("Invalid sequence of tokens"));
            case Token::END:
            case Token::CL_BREAK:
                return left;
            default:
                Tkz.pushOpBack();
                return left;
            }
        }
        return left;
    }



};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Invalid number of arguments" << endl;
        return 1;
    }
    unordered_map<string, double> mp = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
    Calculator calc(argv[1], mp);
    cout << calc.getValue() << endl;
    return 0;
}

