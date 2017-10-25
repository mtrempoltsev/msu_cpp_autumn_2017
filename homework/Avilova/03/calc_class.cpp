#include <iostream>
#include <unordered_map>

std::unordered_map<std::string, double> constants =
{
    { "Pi", 3.14 },
    { "e", 2.7 }
};

using namespace std;

enum class Token
{
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End,
    Constant,
    Left_Bracket,
    Right_Bracket
};

/*===========================================
* функции:
* конструктор
* проверка на конец выражения
* проверка на правильность ввода
* проверка на константу
* взятие токена
* выделение чисел
* умножение/деление
* сложение/вычитание
===========================================*/
class Calculator
{
   public:
      Token token;
      const char *prev;
      int brackets = 0;

      Calculator(const char *&text);
      int isEnd(void);
      int isInvalid(void);
      int isConstant(void);
      void getToken(const char *&text);
      int prim(const char *&text);
      int term(const char *&text);
      int expr(const char *&text);
};

Calculator::Calculator(const char *&text)
{
    prev = text;
    getToken(text);
}

int Calculator::isEnd(void)
{
   return (token == Token::End);
}

int Calculator::isInvalid(void)
{
   return (token == Token::Invalid);
}

int Calculator::isConstant(void)
{
    return(token == Token::Constant);
}

void Calculator::getToken(const char *&text)
{
    while (const auto c = *text++)
    {
        prev = text-1;
        switch (c)
        {
            case '(': token = Token::Left_Bracket; return;
            case ')': token = Token::Right_Bracket; return;
            case '*': token = Token::Mul; return;
            case '/': token = Token::Div; return;
            case '-': token = Token::Minus; return;
            case '+': token = Token::Plus; return;
            case ' ': continue;
        }

        if (c >= '0' && c <= '9')
        {
            for (auto c = *text; c >= '0' && c <= '9';)
            {
                text++;
                c = *text;
            }
            token = Token::Number;
            return;
        }

        if (isalpha(c))
        {
            for (auto c = *text; isalpha(c);)
            {
                text++;
                c = *text;
            }
            token = Token::Constant;
            return;
        }

        token = Token::Invalid;
        return;
    }
    token =  Token::End;
    return;
}


int Calculator::prim(const char *&text)
{

    getToken(text);
    switch (token)
    {
        case Token::Number:
        {
            int number = atoi(prev);
            getToken(text);
            if (isInvalid() || isConstant())
            {
                 cout << "Error input" << endl;
                 exit(-1);
            }

            return number;
        }

        case Token::Minus:
        {
            int number = prim(text);
            return -number;
        }

        case Token::Constant:
        {
            auto name = std::string(prev, text - prev);
            auto iter = constants.find(name);

            if (iter == constants.end())
                exit(-1);

            int number = constants[name];

            getToken(text);

            if (isInvalid())
                exit(-1);

            return number;
        }

        case Token::Left_Bracket:
        {
            brackets++;
            int result = expr(text);
                if (token != Token::Right_Bracket)
                {
                    cout << "Error input" << endl;
                    exit(-1);
                }

                brackets--;
                getToken(text);
                return result;
        }
        default:
        {
            cout << "Error input" << endl;
            exit(-1);
        }

    }
}


int Calculator::term(const char *&text)
{
    int left = prim(text);
    while(1)
    {
        switch (token)
        {
            case Token::Mul:
            {
                left *= prim(text);
                break;
            }

            case Token::Div:
            {
                int divisor = prim(text);
                if (divisor == 0)
                {
                    cout << "Div 0" << endl;
                    exit(-1);
                }
                left /= divisor;
                break;
            }

            case Token::Right_Bracket:
            {
                if (!brackets)
                      exit(-1);
            }

            default: return left;
        }
    }
}

int Calculator::expr(const char *&text)
{
    int left = term(text);
    while(1)
    {
        switch (token)
        {
            case Token::Plus:
            {
                left += term(text);
                break;
            }
            case Token::Minus:
            {
                left -= term(text);
                break;
            }
            default: return left;
        }
    }
}

int main(int argc, char *argv[])
{
    const char *text = "2*2";

    if (argc == 1)
    {
      cout << "Empty input" << endl;
      return -1;
    }

    text = argv[1];

    auto prev = text;

    Calculator calc  = Calculator(text);

    if (calc.isEnd())
    {
        cout << "Error input" << endl;
        return -1;
    }
    if (!calc.isInvalid())
    {
        text = prev;
        calc.prev = prev;
        cout << calc.expr(text) << endl;
    }
    else
    {
        cout << "Error input"  << endl;
        return -1;
    }
return 0;
}
