//
// Created by peter on 05.10.17.
//

#ifndef EXPRCALCCLASS_CALCULATOR_H
#define EXPRCALCCLASS_CALCULATOR_H

#include <iostream>
#include <stack>
#include <unordered_map>

enum class Token
{
    Invalid ,
    Minus ,
    Plus ,
    Mul ,
    Div ,
    Number ,
    BraceIn,
    BraceOut,
    Const,
    End
};


class Calculator {

public:

    Calculator()
    {}

    int calculate(const char*& text)
    {
        this->text = text;

        if(getToken(false, false) == Token::End)
        {
            throw std::runtime_error("Empty input");
        }

        int res =  expr();

        if(brackets.size() > 0)
        {
            throw std::runtime_error("Error in brackets");
        }

        return res;

    }


private:
    const char* text;
    std::stack<Token> brackets;

    std::unordered_map<std::string, double> constants =
            {
                    { "Pi", 3.14 },
                    { "e", 2.7 }
            };

    void skipSpaces()
    {
        // skip spaces
        while (const auto c = *text) {
            if(c != ' ')
            {
                break;
            }
            text++;
        }
    }

    std::string getConstString(bool isShiftedAfterNumberOrConstant = false)
    {
        skipSpaces();
        const char *prev_text = text;

        std::string const_str = "";



        for (auto c = *(text); c >= 'A' && c <= 'z';) {
            const_str+=c;

//            //skip digits
            ++text;
            c = *text;
        }


        if (!isShiftedAfterNumberOrConstant)
            this->text = prev_text;

        return  const_str;


    }

    Token checkConstant( bool isShiftedAfterOperation = true, bool isShiftedAfterNumberOrConstant = false) {
//        const char *prev_text = text;
//
//        std::string const_str = "";
//
//        for (auto c = *(text); (c >= 'A' && c <= 'z') || c == ' ';) {
//
//            if( c == ' ')
//            {
//                continue;
//            }
//
//            const_str+=c;
//
//            //skip digits
//            ++text;
//            c = *text;
//        }

        std::string const_str  = getConstString(isShiftedAfterNumberOrConstant);


        Token tokenConst = Token::Invalid;

        if (constants.count(const_str) > 0) {
            tokenConst = Token::Const;
        }


//        for(size_t i = 0; i< const_str.size(); ++i)
//        {
//            if(constants.count(const_str.substr(0,i)) > 0)
//            {
//                tokenConst =  Token ::Const;
//            }
//        }

//        if (!isShiftedAfterNumberOrConstant)
//            this->text = prev_text;

        return tokenConst;
    }

    double getConstant()
    {
//        std::string const_str = "";
//
//        for (auto c = *(text); c >= 'A' && c <= 'z';) {
//
//            const_str+=c;
//
//            //skip digits
//            ++text;
//            c = *text;
//        }

        std::string const_str = getConstString(true);

        if(constants.count(const_str) > 0)
        {
            return constants[const_str];
        }
        else
        {
            throw std::runtime_error("Error in constants");
        }

    }


    // получение текущего токена
    Token getToken( bool isShiftedAfterOperation = true, bool isShiftedAfterNumberOrConstant = false) {
        skipSpaces();
        const char *prev_text = text;

        if(checkConstant(isShiftedAfterOperation, isShiftedAfterNumberOrConstant) == Token::Const)
        {
            return Token ::Const;
        }




        while (const auto c = *text++) {
            switch (c) {
                case ' ':
                    continue;
                case '-':
                    if (!isShiftedAfterOperation)
                        text = prev_text;
                    return Token::Minus;
                case '+':
                    if (!isShiftedAfterOperation)
                        text = prev_text;
                    return Token::Plus;
                case '/':
                    if (!isShiftedAfterOperation)
                        text = prev_text;
                    return Token::Div;
                case '*':
                    if (!isShiftedAfterOperation)
                        text = prev_text;
                    return Token::Mul;
                case '(':
                    if (!isShiftedAfterOperation)
                        text = prev_text;
                    return Token::BraceIn;
                case ')':
                    if (!isShiftedAfterOperation)
                        text = prev_text;
                    return Token::BraceOut;
            }

            if (c >= '0' && c <= '9') {
                for (auto c = *(text); c >= '0' && c <= '9';) {
                    //skip digits
                    ++text;
                    c = *text;
                }

                if (!isShiftedAfterNumberOrConstant)
                    text = prev_text;

                return Token::Number;
            }

            if (!isShiftedAfterNumberOrConstant)
                text = prev_text;

            return Token::Invalid;
        }
        return Token::End;
    }



    bool isUnarMinus()
    {
        const char* prev_text = text;

        if(getToken() == Token::Minus)
        {
            return true;
        }


        text = prev_text;
        return  false;
    }



// вычисление числа с унарным минусом
    int prim()
    {

        bool isNegative = isUnarMinus();

        int res  = 0;
        bool isNumber = false;

        Token tk = getToken(false, false);
        if(tk == Token::Const)
        {
            res = (int) getConstant();
            return res;
        }

        for(;(*text >= '0' && *text <= '9') || *text == ' ' ; ++text)
        {
            if(*text == ' ')
                continue;

            res = res * 10 + (*text - '0');
            isNumber = true;
        }

        if(!isNumber)
            throw std::runtime_error("Error in number input!");

        if(isNegative)
            return -res;
        else
            return res;
    }

    int bracer()
    {

        bool isNegative = isUnarMinus();



        Token tk = getToken(false, false);
        int res = 0;
        if(tk == Token::BraceIn)
        {
            // если начало скобок, то вычисляем выражение внутри скобок и записываем в результат

            brackets.push(Token::BraceIn);

            text++;
            res = expr();
        }
        else
        {

            // если нет то считываем просто число
            res = prim();


        }

        if(isNegative)
            res*=-1;


        return  res;
    }


    //  вычисление терма в выражении
    int term()
    {

        int res = bracer();

        Token tk = getToken(text);
        while (tk  == Token::Mul || tk == Token::Div)
        {
            if(tk == Token::Mul)
            {
                int pr = bracer();
                res *=  pr;
            }

            if(tk == Token::Div)
            {
                int pr = bracer();
                if(pr == 0)
                {
                    throw std::runtime_error("Division by zero!");
                }

                res /=  pr;
            }

            tk = getToken();
        }
        --text;

        return  res;
    }


    // сложение и вычитание термов
    int expr()
    {
        int res = term();

        Token tk;

        tk = getToken();
        while (tk != Token::End /*&& tk!= Token::BraceOut*/)
        {

            switch(tk)
            {
                case Token::Invalid:
                {
                    throw std::runtime_error("Invalid character!");
                }

                case Token ::Plus:
                {
                    res += term();
                    break;
                }
                case Token ::Minus:
                {
                    res -= term();
                    break;
                }
                case Token::BraceOut:
                {
                    if(brackets.empty()
                       || brackets.top() != Token::BraceIn)
                    {
                        throw std::runtime_error("Error in brackets");
                    }

                    brackets.pop();
                    return res;
                }
                default:
                {
                    throw std::runtime_error("Something go wrong!");
                }
            }

            tk = getToken();
        }

        return  res;
    }




};

#endif //EXPRCALCCLASS_CALCULATOR_H
