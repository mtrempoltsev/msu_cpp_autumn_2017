#include "calculator.h"

std::unordered_map<std::string, double> constants = {
    { "Pi", 3.14 },
    { "e", 2.7 }};

Calculator::Calculator(): value(0), level(0), text(nullptr)
{}

Token Calculator::getToken() // if Token has type - Number, then value replaces by ridden number
{
    std::string constant_name = "";
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
            case '(': return Token::OpenBracket;
            case ')': return Token::ClosBracket;
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
        if (c >= 'A' && c <= 'z')
        {
            constant_name += c;
            for (auto c = *text; c >= 'A' && c <= 'z'; )
            {
                constant_name += c;
                ++text;
                c = *text; // skipping digits
            }
            if (constants.count(constant_name) > 0)
            {
                value = constants[constant_name];
                return Token::Const;
            }
        }
        return Token::Invalid;
    }
    text--;
    return Token::End;
}

/*
Token Calculator::getToken()
{
    auto token = _getToken();
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

int Calculator::prim()
{
    int answer = 1;
    //int value = 0;
    const char* text_ptr = text;
    auto token = getToken();

    if (token == Token::Minus)
    {
        answer = -1;
        token = getToken();
    }

    if (token == Token::Number || token == Token::Const){
        answer *= value;
    }
    else if (token == Token::OpenBracket)
    {
        level++;
        //text++;
        //text_ptr = text;
        value = this->token_sequence(text);
        answer *= value;
    }
    else
    {
        text = text_ptr;
        throw "Unsupported query";
    }
     return answer;
}



int Calculator::_prim()
{
    int answer = 0;
    //int value = 0;
    const char* text_ptr = text;
    auto token = getToken();

    if (token == Token::Number || token == Token::Const){
        answer = value;
    }
    else if (token == Token::Minus){
        token = getToken();
        if (token == Token::Number || token == Token::Const)
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

int Calculator::term()
{
    int answer = prim();
    //int value = 0;
    const char* text_ptr = text;
    auto token = getToken();
    int divisor = 0;

    while (token != Token::End)
    {
        switch (token) {
        case Token::Div:
            divisor = prim();
            if (divisor == 0)
                throw "Division by zero.";
            answer /= divisor;
            text_ptr = text;
            break;
        case Token::Mul:
            answer *= prim();
            text_ptr = text;
            break;
        default:
            text = text_ptr;
            return answer;
        }
        token = getToken();
    }
    return answer;
}

int Calculator::token_sequence(const char*& text)
{
    this->text=text;
    //this->value=0;
    //this->level=0;
    //this->unshifted_text=text;
    //this->result=0;


    int answer = term();
    //int value = 0;
    auto token = getToken();

    while (token != Token::End)
    {
        switch (token) {
        case Token::ClosBracket:
            if (level>0)
            {
                level--;
                value = answer;
                return answer;
            }
            else
                throw "Unbalansed parentheses.";
        case Token::Minus:
            answer -= term();
            break;
        case Token::Plus:
            answer += term();
            break;
        default:
            throw "Unsupported operation.";
        }
        token = getToken();
     }
    if (level != 0)
        throw "Unbalansed parentheses.";
    return answer;
}


/*
 * ======================================================================================
 * ======================================================================================
 * ======================================================================================
 */

void check(const char* text, int value, bool invalid=false)
{
    Calculator calc;
    const char* text_ptr = text;
    try
    {
        auto result = calc.token_sequence(text);
        if (result == value && !invalid)
            std::cout << "Passed: " << text_ptr << " = " << value << std::endl;
        else
            std::cout << "Failed: " << text_ptr << " = " << result << " (" << value << " expected)" << std::endl;
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
    check("Pi", 3);
    check("Pi + e", 5);
    check("-Pi + 11", 8);

    check("(2)", 2);
    check("(-2)", -2);
    check("(e)", 2);
    check("(e)", 2);

    check("(e*2)+2", 6);
    check("(e+2)+2", 6);
    check("e+(2)+2", 6);
    check("e+(2+2)", 6);
    check("e/(2)", 1);
    check("(2+e)/2", 2);



    check("2-+2", 0, true);
    check("2++2", 0, true);
    check("2 c 2", 0, true);
    check("2 2", 0, true);
    check("((2+2", 0, true);
    check("(2)+2)", 0, true);
    check("(2)+2/(2-2)", 0, true);

    check("1.5 + 1.5", 0, true);
    check("2*+ 2", 0, true);
    check("2+* 2", 0, true);
}
