#include <iostream>

using namespace std;

enum class Token // enum class cannot be cast to type int
{
    Invalid, // 0
    Minus, // 1
    Plus, // 2
    Mul, // 3
    Div, // 4
    Number, // 5
    End // 6
};

//cannot change pointed memory but  can change the pointer with effect outside of the function
//this function gets token from string passing the spaces between tokens
Token getToken(const char *&text)
{
    while (const auto c = *text++){
        switch (c){
            case ' ': continue;
            case '-': return Token::Minus;
            case '+': return Token::Plus;
            case '*': return Token::Mul;
            case '/': return Token::Div;
        }
        if (c >= '0' && c <= '9'){
            for (auto c = *text; c >= '0' && c <= '9';){ //skip digits
                text++;
                c = *text;
            }

            return Token::Number;
        }
        return Token::Invalid;
    }
    return Token::End;
}

//this function returns primary expression
int prim(Token &token, const char *&text, const char *&prev)
{
    token = getToken(text);// read token
    switch (token){ // if number then take it from position prev
        case Token::Number:{
            int number = atoi(prev);
            token = getToken(text);
            prev = text;

            if (token == Token::Invalid) throw 0; // if invalid token throw an exception

            return number;
        }
        case Token::Minus:{
            int number = prim(token, text, prev);
            return number;
        }
        default: throw 0;
    }
}

int term(Token &token, const char *&text, const char *&prev)
{
    int left = prim(token, text, prev); // get recursively part result of the part of expression
    while(1){
        switch (token){
            case Token::Mul:{
                left *= prim(token, text, prev);
                break;
            }
            case Token::Div:{
                int divisor = prim(token, text, prev);
                if (divisor == 0) throw 0;
                left /= divisor;
                break;
            }
            default: return left;
        }
    }
}

int expr(Token &token, const char *&text, const char *&prev)
{
    int left = term(token, text, prev); // get recursively part result of the part of expression
    while(1){
        switch (token){
            case Token::Plus:{
                left += term(token, text, prev);
                break;
            }
            case Token::Minus:{
                left -= term(token, text, prev);
                break;
            }
            default: return left;
        }
    }
}

int main(int argc, char *argv[])
{
    const char *text = "1 + 2";

    if (argc == 1) { // of there are no arguments print message
      std::cout << "Empty expression"  << std::endl;
      return 2;
    }
    text = argv[1];

    auto prev = text;

    auto token = getToken(text);
    if (token == Token::End){ // the same if there is an empty string argument
        std::cout << "Empty expression"  << std::endl;
        return 2;
    }
    if (token != Token::Invalid){// if toke is valid then calculate an expression
        text = prev; // point main text pointer to the start of string
        try
        {
            std::cout << expr(token, text, prev) << std::endl;
        }
        catch (int e)
        {
            std::cout << "Invalid input"  << std::endl;
            return 1;
        }
    } else {
        std::cout << "Invalid input"  << std::endl;
        return 1;
    }
    return 0;
}
