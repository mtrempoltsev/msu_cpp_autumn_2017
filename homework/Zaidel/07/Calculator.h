//
// Created by peter on 05.10.17.
//

#ifndef EXPRCALCCLASS_CALCULATOR_H
#define EXPRCALCCLASS_CALCULATOR_H

#include <iostream>
#include <stack>
#include <unordered_map>
#include <cmath>

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

template <class T, class Parser>
class Calculator {

public:

    Calculator()
    {}


    T calculate_s(std::string str)
    {
        const char* txt = str.c_str();
        return calculate(txt);
    }


    T calculate(const char*& text)
    {
        this->text = text;

        if(getToken(false, false) == Token::End)
        {
            throw std::runtime_error("Empty input");
        }

        T res =  expr();

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

    T getConstant()
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
            return static_cast<T>(constants[const_str]);
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


        T num_value = 0;
        if(Parser::parse(text,num_value,isShiftedAfterNumberOrConstant ))
        {
            if (!isShiftedAfterNumberOrConstant)
                text = prev_text;
            return Token::Number;
        }

        while (const auto c = *text++) {
            switch (c) {
//                case ' ':
//                    continue;
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


//            if (c >= '0' && c <= '9') {
//                for (auto c = *(text); c >= '0' && c <= '9';) {
//                    //skip digits
//                    ++text;
//                    c = *text;
//                }
//
//                if (!isShiftedAfterNumberOrConstant)
//                    text = prev_text;
//
//                return Token::Number;
//            }

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
    T prim() {

        bool isNegative = isUnarMinus();

        T res = 0;
        bool isNumber = false;

        Token tk = getToken(false, false);
        if (tk == Token::Const) {
            res = static_cast<T>(getConstant());
            return res;
        }


//        for(;(*text >= '0' && *text <= '9') || *text == ' ' ; ++text)
//        {
//            if(*text == ' ')
//                continue;
//
//            res = res * 10 + (*text - '0');
//            isNumber = true;
//        }

        skipSpaces();

//
//        for (; (*text >= '0' && *text <= '9'); ++text) {
//            res = res * 10 + (*text - '0');
//            isNumber = true;
//        }

        isNumber = Parser::parse(text, res, true);

        if(Parser::check_value(res) == false)
        {
            throw std::runtime_error("Value out of limits!");
        }

        if (!isNumber)
            throw std::runtime_error("Error in number input!");

        if (isNegative)
            return -res;
        else
            return res;
    }

    T bracer()
    {

        bool isNegative = isUnarMinus();



        Token tk = getToken(false, false);
        T res = 0;
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


        if(Parser::check_value(res) == false)
        {
            throw std::runtime_error("Value out of limits!");
        }

        return  res;
    }


    //  вычисление терма в выражении
    T term()
    {

        T res = bracer();

        Token tk = getToken(text);
        while (tk  == Token::Mul || tk == Token::Div)
        {
            if(tk == Token::Mul)
            {
                T pr = bracer();

                T prev_res = res;

                res *=  pr;

                // check overflow
                if (pr != 0 && res / pr != prev_res) {
                    throw std::runtime_error("Result out of limits!");
                }
            }

            if(tk == Token::Div)
            {
                T pr = bracer();
                if(pr == 0)
                {
                    throw std::runtime_error("Division by zero!");
                }

                res /=  pr;

                // check overflow
                if (std::isfinite(res) == false) {
                    throw std::runtime_error("Result out of limits!");
                }
            }

            tk = getToken();
        }
        --text;

        if(Parser::check_value(res) == false)
        {
            throw std::runtime_error("Value out of limits!");
        }

        return  res;
    }


    // сложение и вычитание термов
    T expr()
    {
        T res = term();

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

        if(Parser::check_value(res) == false)
        {
            throw std::runtime_error("Value out of limits!");
        }

        return  res;
    }


};

#endif //EXPRCALCCLASS_CALCULATOR_H
