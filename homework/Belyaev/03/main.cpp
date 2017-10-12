#include <iostream>
#include <unordered_map>
#include <cstring>

enum class Token
{
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End,
    Const,
    LBrace,
    RBrace
};

Token getToken(const char*& text) //Указатель будет сдвигаться. Текст - это ссылка на указатель константной char. Не смогу менять то, что внутри, но указатель смогу.
{
    while(const auto c = *text++) {//Когда встретит 0 - остановится. Приоритет выше у инкремента - прибавим сначала, но разыменуем предыдущий указатель
        switch (c) {
            case ' ':
                continue;
            case '-':
                return Token::Minus;
            case '+':
                return Token::Plus;
            case '*':
                return Token::Mul;
            case '/':
                return Token::Div;
            case '(':
                return Token::LBrace;
            case ')':
                return Token::RBrace;
        }
        if (c >= '0' && c <= '9')
            return Token::Number;
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')){
            return Token::Const;
        }
        throw std::runtime_error("Invalid Symbol"); // Вместо return Token::Invalid;
    }
    return Token::End;
}

class calculator {
public:
    calculator(const char *&text){
        expression = text;
    }

    int calculate(){
        std::cout << expr(expression) << std::endl;
    }


private:
    int prim(const char *&text) {
        bool isPositive = true;
        Token thisToken = getToken(text);
        --text;
        if (thisToken == Token::Minus) { //Checking if number is positive/negative
            isPositive = false;
            thisToken = getToken(++text); //Checking what goes after subtraction symbol
            --text;
        }
        if(thisToken == Token::LBrace){//If there are braces - create loop to calculate expr in braces.
            ++text;
            int c = expr(text, true);
            //++text;
            //thisToken = getToken(text);//Looking for the next token after RBrace
            return c * (2 * isPositive - 1);
        }
        if (thisToken == Token::End) {
            return 0;
        }
        if (thisToken == Token::Const){
            int length = 1;
            ++text ;
            while ((*text >= 'A' && *text <= 'Z') || (*text >= 'a' && *text <= 'z')) {
                length += 1;
                ++text;
            }
            std::string* var = new std::string();
            var->assign(text-length, length);
            return constants.at(*var) * (2 * isPositive - 1);
        }
        if (thisToken != Token::Number) {
            throw std::runtime_error("Syntax error");
        }
        int c = int(*text - '0');
        while (*(++text) >= '0' && *text <= '9') {
            c = c * 10 + int(*text - '0');
        }


        return c * (2 * isPositive - 1);


    }

    int term(const char *&text) {
        int c = prim(text);
        Token thisToken = getToken(text);
        while (thisToken == Token::Mul || thisToken == Token::Div) {
            if (thisToken == Token::Mul) {
                c = c * prim(text);
                thisToken = getToken(text);
            } else {
                int divider = prim(text);
                if (divider) {
                    c = c / divider;
                    thisToken = getToken(text);
                } else throw std::runtime_error("Division by zero");
            }
        }
        --text;
        return c;
    }


    int expr(const char *&text, bool fromPrim = false) {
        int c = term(text);
        Token thisToken = getToken(text);
        while (thisToken != Token::End && thisToken != Token::RBrace && thisToken != Token::LBrace) {
            if (thisToken == Token::Plus) {
                c += term(text);
                thisToken = getToken(text);
            } else if (thisToken == Token::Minus) {
                c -= term(text);
                thisToken = getToken(text);
            } else
                throw std::runtime_error("Syntax error");
        }
        if (thisToken == Token::LBrace){
            throw std::runtime_error("Brace syntax error");
        }
        if (thisToken != Token::RBrace || fromPrim){
            return c;
        }
        throw std::runtime_error("Brace syntax error");
    }
    const char* expression;
    std::unordered_map<std::string, double> constants =
            {
                    { "Pi", 3.14 },
                    { "e", 2.7 }
            };

};


int main(int argc, char* argv[]) {

    if(argc<2){
        throw std::runtime_error("No input expression");
    }
    const char* expression = argv[1];
    calculator* myCalc = new calculator(expression);
    myCalc->calculate();

    /*const char* test_exp = "2 + 2";
    calculator* myCalc = new calculator(test_exp);
    myCalc->calculate();*/


    return 0;
}