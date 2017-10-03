#include "iostream"

enum class Token
{
    Invalid,
    Minus, //1
    Plus, //2
    Mul, //3
    Div, //4
    Number, //5
    End //6
};
Token token; //variable that holds current token
Token getToken(const char*& text) //parsing token from string
{
    while (const auto c = *text++)
    {
        switch (c)
        {
            case ' ': continue;
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case '*': return Token::Mul;
            case '/': return Token::Div;
        }
        if (c >= '0' && c <= '9')
        {
            return Token::Number;
        }
        else return Token::Invalid;
    }
    return Token::End;
}
//parsing number
int prim(const char*& text)
{
    int result = 0;
    token = getToken(text);
    --text;
    if (token == Token::Number)
    {
        while(*text >= '0' && *text <= '9')
        {
            result = result*10 + *text - '0';
            ++text;
        }
        return result;
    }
    if (token == Token::Minus)
    {
        ++text;
        return (-1)*prim(text);
    }
    else
    {
        throw "Unexpected symbol";
    }
}
//parsing multiplication/division
int term(const char*& text)
{
    int leftOperand = prim(text);
    token = getToken(text);
    --text;
    while(token != Token::End && (token == Token::Mul || token == Token::Div))
    {
        if(token == Token::Mul)
        {
            ++text;
            leftOperand *= prim(text);
            token = getToken(text);
            --text;
        }
        if(token == Token::Div)
        {
            ++text;
            leftOperand /= prim(text);
            token = getToken(text);
            --text;
        }
    }
    return leftOperand;
}
//parsing sum/difference
int expr(const char*& text)
{
    int leftOperand = term(text);
    while(token != Token::End && (token == Token::Plus || token == Token::Minus))
    {
        if(token == Token::Plus)
        {
            ++text;
            leftOperand += term(text);
        }
        if(token == Token::Minus)
        {
            ++text;
            leftOperand -= term(text);
        }
    }
    return leftOperand;
}

int main(int argc, char * argv[])
{
    const char* text = argv[1];
    if (argc < 2)
    {
        std::cout << "no expression" << std::endl;
        return 1;
    }
    try
    {
        std::cout <<expr(text);
    }
    catch(const char* text)
    {
        std::cout << text;
    }
    return 0;
}
