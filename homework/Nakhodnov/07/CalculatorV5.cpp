#include <iostream>
#include <unordered_map>
#include <string>
#include <limits>
#include <cmath>

using namespace std;


template <class T>
class NumericParser {};

template <>
class NumericParser<int> {
private:
    static constexpr int min = numeric_limits<int>::min();
    static constexpr int max = numeric_limits<int>::max();
public:
    NumericParser() {};
    int get_number(char* &S) {
        long long int ans = 0;
        while (*S && isdigit(*S)) {
            ans *= 10;
            ans += (*S++ - '0');
        }
        if (min <= ans && ans <= max) {
            return (int)ans;
        }
        throw(std::invalid_argument("Number in the expression cant`t be represented as int"));
    }
};

template <>
class NumericParser<long> {
private:
    static constexpr long min = numeric_limits<long>::min();
    static constexpr long max = numeric_limits<long>::max();
public:
    NumericParser() {};
    long get_number(char* &S) {
        long long int ans = 0;
        while (*S && isdigit(*S)) {
            ans *= 10;
            ans += (*S++ - '0');
        }
        if (min <= ans && ans <= max) {
            return (long)ans;
        }
        throw(std::invalid_argument("Number in the expression cant`t be represented as long"));
    }
};

template <>
class NumericParser<double> {
private:
    static constexpr double min = numeric_limits<double>::lowest();
    static constexpr double max = numeric_limits<double>::max();
public:
    NumericParser() {};
    double get_number(char* &S) {
        long double before_dot = 0, after_dot = 0, ans;
        int order = 0;
        while (*S && *S != '.' && isdigit(*S)) {
            before_dot *= 10;
            before_dot += (*S++ - '0');
        }
        if (*S == '.') ++S;
        while (*S && isdigit(*S)) {
            ++order;
            after_dot *= 10;
            after_dot += (*S++ - '0');
        }
        ans = before_dot + after_dot / pow(10, order);
        if (min <= ans && ans <= max) {
            return ans;
        }
        throw(std::invalid_argument("Number in the expression cant`t be represented as double"));
    }
};



// Класс для хранения лексем разбираемой строки
template <class T>
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
    T value;
    Token(TokenTypes tp = Token<T>::END, T val = 0) : type(tp), value(val) {}
    Token(const Token& token) {
        if (this != &token) {
            this->type = token.type;
            this->value = token.value;
        }
    }
    Token& operator=(const Token& token) {
        if (this != &token) {
            this->type = token.type;
            this->value = token.value;
        }
        return *this;
    }
};


// Класс, разбивабщий строку на лексемы
template <class T>
class Tokenizer {
public:
    Tokenizer(char *s, unordered_map<string, T> mp) : S(s), constants(mp) {}
    // Получаем первый токен из строки S
    Token<T> getToken() {
        while (*S && isspace(*S)) {
            ++S;
        }
        if (!*S) {
            return Token<T>(Token<T>::END);
        }
        switch (*S) {
        case '+':
            ++S;
            return Token<T>(Token<T>::PLUS);
        case '-':
            ++S;
            return Token<T>(Token<T>::MINUS);
        case '/':
            ++S;
            return Token<T>(Token<T>::DIV);
        case '*':
            ++S;
            return Token<T>(Token<T>::MUL);
        case '(':
            ++balance;
            ++S;
            return Token<T>(Token<T>::OP_BREAK);
        case ')':
            --balance;
            if (balance < 0 || (balance && !*(S + 1)))
                throw(std::invalid_argument("The expression contains an incorrect sequence of brackets"));
            ++S;
            return Token<T>(Token<T>::CL_BREAK);
        default:
            char *S_temp = S;
            Token<T> token = getNumber();
            if (S_temp == S)
                throw(std::invalid_argument(string("The expression contains an incorrect symbol: \'") + *S + string("\'")));
            if (balance && !*S)
                throw(std::invalid_argument("The expression contains an incorrect sequence of brackets"));
            return token;
        }
    }
    void pushOpBack() {
        --S;
        if (*S == '(') --balance;
        if (*S == ')') ++balance;
    }
private:
    char *S;
    unordered_map<string, T> constants;
    NumericParser<T> parser;
    int balance = 0;
    /*
    Выделяем из строки число <number>:
    <number> ::= <digit>|<number><digit>|<const>
    <digit> ::= 0|1|2|3|4|5|6|7|8|9
    <const> ::= Pi|e
    */
    Token<T> getNumber() {
        Token<T> token(Token<T>::NUMBER, 0);
        string buff;
        int iter = 0;
        if (!isalpha(*S) && !isdigit(*S)) return token;

        for (; *(S + iter) && isalpha(*(S + iter)); ++iter) {
            buff += *(S + iter);
        }
        try {
            token.value = constants.at(buff);
            S += iter;
            return token;
        }
        catch (const std::out_of_range&) {
            if (buff.length()) {
                return token;
            }
            token.value = parser.get_number(S);
            return token;
        }
    }
};


template <class T>
class Calculator {
public:
    Calculator(char *s, unordered_map<string, T> mp) : Tkz(s, mp) {}
    T getValue() {
        return getExpr();
    }
private:
    Tokenizer<T> Tkz;

    /*
    Вычисляем значение лексической единицы <prim>:
    <prim> ::= <number>|-<number>
    */
    T getPrim() {
        Token<T> token = Tkz.getToken();
        if (token.type == Token<T>::OP_BREAK) {
            return getExpr();
        }
        if (token.type == Token<T>::MINUS) {
            token = Tkz.getToken();
            if (token.type != Token<T>::NUMBER)
                throw(std::invalid_argument("The expression contains an incorrect sequence of tokens"));
            return token.value * -1;
        }
        else if (token.type != Token<T>::NUMBER)
            throw(std::invalid_argument("The expression contains an incorrect sequence of tokens"));
        return token.value;
    }

    /*
    Вычисляем значение лексической единицы <term>:
    <term> ::= <prim>|<term> * <prim>|<term> / <prim>
    Т.е. выполняем обработку операций деления и вычитания
    */
    T getTerm() {
        T left, tmp;
        Token<T> token;
        left = getPrim();
        while (1) {
            token = Tkz.getToken();
            switch (token.type) {
            case Token<T>::MUL:
                left *= getPrim();
                break;
            case Token<T>::DIV:
                tmp = getPrim();
                if (!tmp)
                    throw(std::runtime_error("Division by zero"));
                left /= tmp;
                break;
            case Token<T>::NUMBER:
                throw(std::invalid_argument("The expression contains an incorrect sequence of tokens"));
            case Token<T>::END:
                return left;
            case Token<T>::CL_BREAK:
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
    T getExpr() {
        Token<T> token;
        T left = getTerm();
        while (1) {
            token = Tkz.getToken();
            switch (token.type) {
            case Token<T>::PLUS:
                left += getTerm();
                break;
            case Token<T>::MINUS:
                left -= getTerm();
                break;
            case Token<T>::NUMBER:
                throw(std::invalid_argument("The expression contains an incorrect sequence of tokens"));
            case Token<T>::END:
                return left;
            case Token<T>::CL_BREAK:
                return left;
            default:
                Tkz.pushOpBack();
                return left;
            }
        }
        return left;
    }



};


template <class T>
void prepare_computation(Calculator<T>& calc) {
    try
    {
        cout << calc.getValue() << endl;
    }
    catch (const std::invalid_argument& exp)
    {
        cerr << "invalid_argument exception\n" << exp.what() << endl;
    }
    catch (const std::runtime_error& exp)
    {
        cerr << "runtime_error exception\n" << exp.what() << endl;
    }
    catch (const std::exception& exp)
    {
        cerr << "Unknown exception\n" << exp.what() << endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cerr << "Invalid number of arguments" << endl;
        return 0;
    }

#ifdef INT
    unordered_map<string, int> mp_int = {
        { "Pi", 3 },
        { "e", 2 }
    };
    Calculator<int> calc_int(argv[1], mp_int);
    prepare_computation(calc_int);
    return 0;
#endif

#ifdef LONG
    unordered_map<string, long> mp_long = {
        { "Pi", 3 },
        { "e", 2 }
    };
    Calculator<long> calc_long(argv[1], mp_long);
    prepare_computation(calc_long);
    return 0;
#endif

#ifdef DOUBLE
    unordered_map<string, double> mp_double = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
    Calculator<double> calc_double(argv[1], mp_double);
    cout.precision(15);
    prepare_computation(calc_double);
    return 0;
#endif

    cout << "Incorrect type. Recompile programm with the correct TYPE" << endl;
    return 0;
}

