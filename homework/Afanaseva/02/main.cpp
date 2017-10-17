#include <iostream>
#include <exception>
using namespace std;

enum class Token // : long
{
    End,     //0
    Minus,   //1
    Plus,    //2
    Mul,     //3
    Div,     //4
    Number,  //5
    Invalid  //6
};

Token getToken(const char*& text, int& value) // if Token has type - Number, then value replaces by ridden number
{
    value = 0;
    while (const auto c = *text++) // be going to zero (end of line)
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
            value = (int)(c - '0');
            for (auto c = *text; c >= '0' && c <= '9'; )
            {
                value = value * 10 + (int)(c - '0');
                ++text;
                c = *text; // skipping digits
            }
            return Token::Number;
        }
        return Token::Invalid;
    }
    text--;
    return Token::End;
}
/*
Token getToken(const char*& text, int& value)
{
    auto token = _getToken(text, value);
    //cout << static_cast<int> (token);
    const char* c;
    if (token == Token::Number)
        cout << "Number("<< value << ")" << endl;
    else
    {
        switch (token) {
        case Token::Minus:
            c = "-";
            break;
        case Token::Plus:
            c = "+";
            break;
        case Token::Div:
            c = "/";
            break;
        case Token::Mul:
            c = "*";
            break;
        case Token::End:
            c = "e";
            break;
        default:
            c = "i";
            break;
        }
        cout << c << endl;
    }
    return token;
}
*/
int prim(const char*& text)
{
    int answer = 0;
    int value = 0;
    const char* text_ptr = text;
    auto token = getToken(text, value);

    if (token == Token::Number){
        answer = value;
    }
    else if (token == Token::Minus){
        token = getToken(text, value);
        if (token == Token::Number)
            answer = -value;
        else {
            text = text_ptr;
            throw "Unsupported query";
        }
    }
    else{
        text = text_ptr;
        throw "Unsupported query";
    }
     return answer;
}

int term(const char*& text)
{
    int answer = prim(text);
    int value = 0;
    const char* text_ptr = text;
    auto token = getToken(text, value);

    while (token != Token::End)
    {
        switch (token) {
        case Token::Div:
	    int divisor = prim(text);
	    if (divisor == 0) throw "Division by zero.";
	    answer /= divisor;
            text_ptr = text;
            break;
        case Token::Mul:
            answer *= prim(text);
            text_ptr = text;
            break;
        default:
            text = text_ptr;
            return answer;
        }
        token = getToken(text, value);
    }
    return answer;
}

int token_sequence(const char*& text)
{
    int answer = term(text);
    int value = 0;
    auto token = getToken(text, value);

    while (token != Token::End)
    {
        switch (token) {
        case Token::Minus:
            answer -= term(text);
            break;
        case Token::Plus:
            answer += term(text);
            break;
        default:
            throw "Unsupported operation.";
        }
        token = getToken(text, value);
     }
    return answer;
}

void check(const char* text, int value, bool invalid = false)
{
    const char* text_ptr = text;
    try
    {
        auto result = token_sequence(text);
        if (result == value && !invalid)
	    std::cout << "Passed: " << text_ptr << "  =  " << value << std::endl;
        else
	    std::cout << "Failed: " << text_ptr << "  =  " << result << " (" << value << " expected)" << std::endl;
    }
    catch(char const* msg)
    {
        if (invalid)
            std::cout << "Passed: " << text_ptr << " Exception message: " << msg << std::endl;
        else
            std::cout << "Failed: " << text_ptr << " Exception message: " << msg << " (" << value << " expected)" <<std::endl;
    }
}

void check_calc()
{
    check("1+1", 2);
    check("2+ 2", 4);
    check("2 +2", 4);
    check("2 + 2", 4);
    check("2 +       2", 4);
    check("2", 2);
    check("-2", -2);
    check("-2 - 2", -4);
    check("2- 2", 0);
    check("2- -  2", 4);
    check("100 + 2", 102);
    check("101 + 2", 103);
    check("8 - 6 * 2 / 2", 2);
    check("8 - 6 / 2 * 2", 2);
    check("8 - 6 / 2 * - 2", 14);
    check("2 + 3 * 4 - -2", 16);
    check("2*-2", -4);


    check("2-+2", 0, true);
    check("2++2", 0, true);
    check("2 c 2", 0, true);
    check("2 2", 0, true);

    check("1.5 + 1.5", 0, true);
    check("2*+ 2", 0, true);
    check("2+* 2", 0, true);
}

/*
 * ================================================================================================
 */

int main(int argc, char* argv[])
{
    // argc - количество аргументов
    // argv - сами аргументы, первый всегда - имя программы

    if (argc < 2)
    {
        cout << "Not enough arguments. Try: " << argv[0] << " <expr>." << endl;
        cout << "Inner test begun..." << endl;
        check_calc();
        return 0;
    }

    const char* text = argv[1];

    try
    {
        //cout << "Input text = " << text << endl;
        cout << token_sequence(text) << endl;
    }
    catch(char const* msg)
    {
        std::cout << endl << "Exception message: " << msg << std::endl;
        return -2;
    }
    return 0;
}
