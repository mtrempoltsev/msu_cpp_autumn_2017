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
//Token token; //variable that holds current token
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
        else throw "Unexpected symbol";;
    }
    return Token::End;
}
//parsing number
int prim(const char*& text, Token* ptr_token)
{
    int result = 0;
    *ptr_token = getToken(text);
    --text;
    if (*ptr_token == Token::Number)
    {
        while(*text >= '0' && *text <= '9')
        {
            result = result*10 + *text - '0';
            ++text;
        }
        return result;
    }
    if (*ptr_token == Token::Minus)
    {
        ++text;
        return (-1)*prim(text, ptr_token);
    }
    else
    {
        throw "Unexpected symbol";
    }
}
//parsing multiplication/division
int term(const char*& text, Token* ptr_token)
{
    int leftOperand = prim(text, ptr_token);
    *ptr_token = getToken(text);
    --text;
    while(*ptr_token != Token::End && (*ptr_token == Token::Mul || *ptr_token == Token::Div))
    {
        if(*ptr_token == Token::Mul)
        {
            ++text;
            leftOperand *= prim(text, ptr_token);
            *ptr_token = getToken(text);
            --text;
        }
        if(*ptr_token == Token::Div)
        {
            ++text;
            int tmp = prim(text, ptr_token);
            if (tmp == 0)
            {
                throw "Zero division";
            }
            leftOperand /= tmp;
            *ptr_token = getToken(text);
            --text;
        }
    }
    return leftOperand;
}
//parsing sum/difference
int expr(const char*& text, Token* ptr_token)
{
    int leftOperand = term(text, ptr_token);
    while(*ptr_token != Token::End && (*ptr_token == Token::Plus || *ptr_token == Token::Minus))
    {
        if(*ptr_token == Token::Plus)
        {
            ++text;
            leftOperand += term(text, ptr_token);
        }
        if(*ptr_token == Token::Minus)
        {
            ++text;
            leftOperand -= term(text, ptr_token);
        }
    }
    return leftOperand;
}

int main(int argc, char * argv[])
{
    const char* text = argv[1];
    Token* ptr_token = nullptr;
    Token token;
    if (argc < 2)
    {
        std::cout << "no expression" << std::endl;
        return 1;
    }
    try
    {
        token = getToken(text);
        ptr_token = &token;
        --text;
        std::cout <<expr(text, ptr_token);
    }
    catch(const char* text)
    {
        std::cout << text;
    }
    return 0;
}
