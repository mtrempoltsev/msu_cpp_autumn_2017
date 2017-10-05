//В unix можно узнать значение последней запущенной программы echo $?
#include<iostream>
enum class Token
{
    Minus,
    Plus,
    Mul,
    Div,
    Number,
    End
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
        }
        if (c >= '0' && c <= '9')
            return Token::Number;
        throw std::logic_error("Invalid Symbol"); // Вместо return Token::Invalid;
    }
    return Token::End;
}
int prim(const char*& text){

    bool isPositive = true;
    Token thisToken = getToken(text);
    --text;
    if(thisToken == Token::Minus){ //Checking if number is positive/negative
        isPositive = false;
        thisToken = getToken(++text); //Checking what goes after subtraction symbol
        --text;
    }
    if(thisToken == Token::End){
        return 0;
    }
    if(thisToken != Token::Number){
        throw std::logic_error("Syntax error");
    }
    int c = int(*text-'0');
    while(*(++text)>='0' && *text<='9'){
        c = c * 10 + int(*text-'0');
    }


    return c * (2 * isPositive-1);


}
int term(const char*& text) {
    int c = prim(text);
    Token thisToken = getToken(text);
    while (thisToken == Token::Mul || thisToken == Token::Div) {
        if (thisToken == Token::Mul) {
            c = c * prim(text);
            thisToken = getToken(text);
        } else {
            int divider = prim(text);
            if(divider) {
                c = c / divider;
                thisToken = getToken(text);
            }else throw std::logic_error("Division by zero");
        }
    }
    --text;
    return c;
}

int expr(const char*& text) {
    int c = term(text);
    Token thisToken = getToken(text);
    while (thisToken != Token::End) {
        if (thisToken == Token::Plus) {
            c += term(text);
            thisToken = getToken(text);
        } else {
            c -= term(text);
            thisToken = getToken(text);
        }
    }
    return c;
}


int main(int argc, char* argv[]) {
    if(argc<2){
        throw std::length_error("No input expression");
    }
    const char* expression = argv[1];
    std::cout << expr(expression) << std::endl;

    return 0;
}
