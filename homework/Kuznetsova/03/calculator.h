#include <stdio.h>
#include <cctype>
#include <iostream>
#include <string>  // std::string
#include <unordered_map>

using namespace std;

enum class Token {
    Invalid,
    Minus,
    Plus,
    Mul,
    Div,
    LBracket,
    RBracket,
    Const,
    Number,
    End
};

extern const char* message;
//отвечает за техническую работу по извлечению токенов из строки, считыванию
//чисел и констант посимвольно
class Tokenizer {
   public:
    Tokenizer(char* input, unordered_map<string, double> constants)
        : input_(input), constants_(constants) {}

    Token get_token();
    void token_back();
    int read_number();
    int read_constant();
    void check_pointer();
    void check_balance();

   private:
    char* input_;
    unordered_map<string, double> constants_;
    int brackets_balance_ = 0;
};

//разбор выражений с вычислением
class Parser {
   public:
    Parser(char* input, unordered_map<string, double> constants)
        : tokenizer_(input, constants) {}
    int calculate();

   private:
    Tokenizer tokenizer_;
    int reached_end_ = 0;

    int parse_primary();
    int parse_term();
    int parse_expression();
};
