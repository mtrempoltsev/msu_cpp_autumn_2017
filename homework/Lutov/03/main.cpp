#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <unordered_map>

std::unordered_map<std::string, double> constants =
{
   {"Pi", 3.14},
   {"e", 2.7}
};

enum class Token {
  Number,
  Plus,
  Minus,
  Multiply,
  Divide,
  LeftBracket,
  RightBracket,
  Const,
  Eof,
};

using Lexem = std::pair<Token, std::string>;
using Lexems = std::vector<Lexem>;

class Lexer {
private:
  bool
  is_number()
  {
    return all_of(this->literal.begin(), literal.end(), [](char c){ return '0' <= c && c <= '9'; });
  }

  bool
  is_const()
  {
    return constants.count(this->literal) > 0;
  }

  void
  append_lexem(Token token, const std::string &str)
  {
    lexems.push_back(std::make_pair(token, str));
  }

  void
  append_literal_if_exist()
  {
    if (!this->literal.empty()) {
      if (this->is_number()) {
        this->append_lexem(Token::Number, this->literal);
      } else if (this->is_const()) {
        this->append_lexem(Token::Const, this->literal);
      } else {
        throw std::runtime_error(std::string("Unexpected literal: ") + this->literal);
      }
      this->literal = "";
    }
  }

  std::string literal;

public:
  Lexems lexems;

  Lexer(const std::string &text) :
    literal(std::string()),
    lexems(Lexems())
  {

    for (auto c : text) {

      switch (c) {
        case ' ': this->append_literal_if_exist();
                  continue;

        case '+': this->append_literal_if_exist();
                  this->append_lexem(Token::Plus, "+");
                  continue;

        case '-': this->append_literal_if_exist();
                  this->append_lexem(Token::Minus, "-");
                  continue;

        case '*': this->append_literal_if_exist();
                  this->append_lexem(Token::Multiply, "*");
                  continue;

        case '/': this->append_literal_if_exist();
                  this->append_lexem(Token::Divide, "/");
                  continue;

        case '(': this->append_literal_if_exist();
                  this->append_lexem(Token::LeftBracket, "(");
                  continue;

        case ')': this->append_literal_if_exist();
                  this->append_lexem(Token::RightBracket, ")");
                  continue;

        default: if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) {
                   this->literal += c;
                   continue;
                 }
      }

      throw std::runtime_error(std::string("Unexpected char ") + std::string(1, c));
    }

    this->append_literal_if_exist();
    this->append_lexem(Token::Eof, "EOF");
  }
};

class Parser {
private:
  auto
  unexpencted_lexem()
  {
    return std::runtime_error("Unexpected lexem " + next->second);
  }

  intmax_t
  prim()
  {
    if (next->first == Token::Number) {
      intmax_t number = std::stoll(next->second);
      ++ next;
      return number;
    } else if (next->first == Token::Const) {
      intmax_t constant = constants[next->second];
      ++ next;
      return constant;
    } else if (next->first == Token::Minus) {
      ++ next;
      return -this->prim();
    } else if (next->first == Token::LeftBracket) {
      ++ next;
      const intmax_t expr = this->expr();
      if (next->first == Token::RightBracket) {
        ++ next;
        return expr;
      } else {
        throw unexpencted_lexem();
      }
    } else {
      throw unexpencted_lexem();
    }
  }

  intmax_t
  term()
  {
    // prim ([*/] prim)*
    intmax_t term = this->prim();
    while (next->first == Token::Multiply || next->first == Token::Divide) {
      if (next->first == Token::Multiply) {
        ++ next;
        intmax_t prim = this->prim();
        term *= prim;
      } else {
        ++ next;
        intmax_t prim = this->prim();
        term /= prim;
      }
    }
    return term;
  }

  intmax_t
  expr()
  {
    // term ([+-] term)*
    intmax_t expr = this->term();
    while (next->first == Token::Plus || next->first == Token::Minus) {
      if (next->first == Token::Plus) {
        ++ next;
        intmax_t term = this->term();
        expr += term;
      } else {
        ++ next;
        intmax_t term = this->term();
        expr -= term;
      }
    }
    return expr;
  }

  void
  eof()
  {
    if (next->first == Token::Eof) {
      ++ next;
    } else {
      throw unexpencted_lexem();
    }
  }

  Lexems::const_iterator next;

public:
  intmax_t result = 0;

  Parser(Lexems::const_iterator &&_next) :
    next(_next)
  {
    this->result = this->expr();
    this->eof(); // eof should be last
  }
};

int
main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " expression" << std::endl;
    return 1;
  } else {
    try {
      // Get lexems and parse it!
      std::cout << Parser(Lexer(argv[1]).lexems.cbegin()).result << std::endl;
    } catch (const std::runtime_error &error) {
      std::cerr << "INVALID" << std::endl;
      return 1;
    }
    return 0;
  }
}
