//
//  main.cpp
//  calculator
//
//  Created by Павел Адаменко on 10/26/17.
//  Copyright © 2017 Павел Адаменко. All rights reserved.
//
// Algorithm from Бьерн Страуструп. Язык программирования С++
// ГЛАВА 3. ВЫРАЖЕНИЯ И ОПЕРАТОРЫ, page 70
//[http://8361.ru/6sem/books/Straustrup-Yazyk_programmirovaniya_c.pdf]
//

#include <iostream>
#include <unordered_map>


std :: unordered_map<std :: string, double> contants= {
    { "PI", 3.141592 },
    { "e",  2.718281 }
};


enum class Token
{
    NaN,
    MIN,
    SUM,
    MUL,
    DIV,
    NUM,
    END,
    LP,
    RP,
    EXP,
    PI,
    Null
};


template<class T>
struct Parser{};


template<>
struct Parser<int>
{
    static int get_number(const char * &text) {
        --text;
        std :: string res_substr = text;
        auto f = *text;
        int num = 0;
        int ind = 0;
        while (f >= '0' && f <= '9') {
            ++text;
            f = *text;
            ind ++;
        }
        if (f=='.') throw( "'.' String to int type error" );
        try
        {
            num = std :: stoi(res_substr.substr(0, ind));

        }
        catch(...)
        {
            throw( "String to int error" );
        }
        return num;
    }
};


template<>
struct Parser<double>
{
    static double get_number(const char * &text) {
        --text;
        std :: string res_substr = text;
        auto f = *text;
        int ind = 0;
        
        double num = 0;
        while ((f >= '0' && f <= '9') ||
               f == '.'  || f == 'E' || f == 'e') {
            ++text;
            f = *text;
            ind ++;
        }
        try
        {
            num = std :: stof( res_substr.substr(0, ind) );
        }
        catch(...)
        {
            throw( "String to double error" );
        }
        return num;
    }
};


template<>
struct Parser<long>
{
    static long get_number(const char * &text) {
        --text;
        std :: string res_substr = text;
        auto f = *text;
        int ind = 0;
        
        long num = 0;
        while (f >= '0' && f <= '9') {
            ++text;
            f = *text;
            ind ++;
        }
        if (f=='.') throw( "'.' String to long type error" );
        try
        {
            num = std :: stol( res_substr.substr(0, ind) );
        }
        catch(...)
        {
            throw( "String to long error" );
        }
        return num;
    }
};


template <typename  valueType> class Calculator
{
private:
    Token   curr_tok;        // curr_tok s[i] (token)
    const char* text;        // text     s[i] (reff)
    int count_braket;        // count_braket of braket
    
    
    Token getToken(){
        while (auto c = *text++) {
            switch (c) {
                case ' ': continue;
                case '-': return Token::MIN;
                case '+': return Token::SUM;
                case '*': return Token::MUL;
                case '/': return Token::DIV;
                case '(': return Token::LP;
                case ')': return Token::RP;
            }
            if (c >= '0' && c <= '9') return Token::NUM;
            if (c == 'e') return Token::EXP;
            if (c == 'P') {
                c = *text++;
                if (c == 'i'){
                    return Token::PI;
                }
                else
                    return Token::NaN;
            }
            return Token::NaN;
        }
        return Token::END;
    }
    
    
    valueType primary() {
        curr_tok = getToken();
        switch (curr_tok) {
            case Token::NUM: {
                valueType num;
                num = Parser<valueType> :: get_number(text);
                curr_tok = getToken();
                return num;
            }
            case Token::EXP: {
                double num = 0;
                num = contants["e"];
                curr_tok = getToken();
                return num;
            }
            case Token::PI: {
                double num = 0;
                num = contants["PI"];
                curr_tok = getToken();
                return num;
            }
            case Token::LP: {
                count_braket++;
                valueType num = expression();
                if (curr_tok != Token::RP) throw( "Bracket position error" );
                curr_tok = getToken();
                return num;
            }
            case Token::Null: {
                int num = 0;
                curr_tok = getToken();
                return num;
            }
            case Token::MIN: {
                return -primary();
            }
            default: throw( "NaN symbol error" );
        }
    }
    
    
    valueType term() {
        valueType left_term = primary();
        while ( curr_tok != Token::END ){
            switch( curr_tok ) {
                case Token::MUL: {
                    left_term *= primary();
                    break;
                }
                case Token::DIV: {
                    valueType denominator = primary();
                    if (denominator == 0){ throw( "Zero division error" ); }
                    else {
                        left_term /= denominator;
                        break;
                    }
                }
                case Token::SUM: {
                    return left_term;
                }
                case Token::MIN: {
                    return left_term;
                }
                case Token::END: {
                    return left_term;
                }
                case Token::RP: {
                    count_braket--;
                    return left_term;
                }
                default: throw( "NaN symbol error" );
            }
        }
        return left_term;
    }
    
    
public:
    Calculator( const char*& txt ) {
        curr_tok = Token::Null;
        text = txt;
        count_braket = 0;
    }
    
    
    valueType expression() {
        valueType left = term();
        while (curr_tok != Token::END) {
            switch( curr_tok ) {
                case Token::SUM: {
                    left += term();
                    break;
                }
                case Token::MIN: {
                    left -= term();
                    break;
                }
                case Token::END: {
                    return left;
                }
                default:
                    return left;
            }
        }
        if (count_braket !=0) throw( "Incorrect braket error\n" );
        return left;
    }
};

int main(int argc, char* argv[])
{
    try
    {
        if (argc <= 1) throw( "Need an argument" );
        //argv[1] = "10 - (Pi*Pi)/2+8*8/4";   // Debug input
        const char* text = argv[1];
        Calculator<double> calc(text);
        double result = calc.expression();

        std :: cout << result << "\n";
        return 0;
    }
    catch (const char* str)
    {
        std :: cout << str << "\n";
        return 1;
    }
}

