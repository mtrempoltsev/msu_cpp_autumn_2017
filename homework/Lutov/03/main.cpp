#include <algorithm>
#include <cinttypes>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <unordered_map>

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

class Fixed {
private:
  int64_t value;

  static auto
  from_value(int64_t value)
  {
    auto result = Fixed();
    result.value = value;
    return result;
  }

public:
  static const int64_t ONE = static_cast<int64_t>(1) << 32;
  static const int64_t MINTMAX = static_cast<int64_t>(1) << 63;

  Fixed(int32_t integer=0, int32_t fraction=0) :
    value(integer * ONE + fraction)
  {
  }

  operator int() const {
    return value / ONE;
  }

  Fixed &
  operator+=(const Fixed &other) {
    this->value += other.value;
    return *this;
  }

  Fixed &
  operator-=(const Fixed &other) {
    this->value -= other.value;
    return *this;
  }

  Fixed &
  operator*=(const Fixed &other) {
    auto remainder = this->value % Fixed::ONE;
    this->value /= Fixed::ONE;
    this->value *= other.value;
    this->value += (remainder * (other.value / Fixed::ONE));
    this->value += (remainder * (other.value % Fixed::ONE) / Fixed::ONE);
    return *this;
  }

  Fixed &
  operator/=(const Fixed &other) {
    if (other.value == 0) {
      throw std::runtime_error("Zero division");
    } else {
      *this *= Fixed::from_value(-(Fixed::MINTMAX / other.value * 2));
      return *this;
    }
  }

  Fixed
  operator-() const {
    return Fixed::from_value(-this->value);
  }
};

std::unordered_map<std::string, Fixed> constants =
{
   {"Pi", Fixed(3, 14 * Fixed::ONE / 100)},
   {"e", Fixed(2, 7 * Fixed::ONE / 10)}
};

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

  Fixed
  prim()
  {
    if (next->first == Token::Number) {
      auto number = Fixed(std::stoi(next->second));
      ++ next;
      return number;
    } else if (next->first == Token::Const) {
      auto constant = constants[next->second];
      ++ next;
      return constant;
    } else if (next->first == Token::Minus) {
      ++ next;
      return -this->prim();
    } else if (next->first == Token::LeftBracket) {
      ++ next;
      const auto expr = this->expr();
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

  Fixed
  term()
  {
    // prim ([*/] prim)*
    auto term = this->prim();
    while (next->first == Token::Multiply || next->first == Token::Divide) {
      if (next->first == Token::Multiply) {
        ++ next;
        auto prim = this->prim();
        term *= prim;
      } else {
        ++ next;
        auto prim = this->prim();
        term /= prim;
      }
    }
    return term;
  }

  Fixed
  expr()
  {
    // term ([+-] term)*
    auto expr = this->term();
    while (next->first == Token::Plus || next->first == Token::Minus) {
      if (next->first == Token::Plus) {
        ++ next;
        auto term = this->term();
        expr += term;
      } else {
        ++ next;
        auto term = this->term();
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
  Fixed result;

  Parser(Lexems::const_iterator &&_next) :
    next(_next),
    result(Fixed())
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
      std::cout << int(Parser(Lexer(argv[1]).lexems.cbegin()).result) << std::endl;
    } catch (const std::runtime_error &error) {
      std::cerr << "INVALID" << std::endl;
      return 1;
    }
    return 0;
  }
}
