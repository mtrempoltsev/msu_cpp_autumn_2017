#include <algorithm>
#include <functional>
#include <cinttypes>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>
#include <unordered_map>

// Lexer

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

std::unordered_map<std::string, double> constants =
{
   {"Pi", 3.14},
   {"e", 2.7}
};

class Lexer {
private:
  bool
  is_number()
  {
    return all_of(this->literal.begin(), literal.end(),
                  [](char c){ return ('0' <= c && c <= '9') || c == '.' || c == 'e' || c == 'E'; }
                 );
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

        default: if (('0' <= c && c <= '9')
                     || ('a' <= c && c <= 'z')
                     || ('A' <= c && c <= 'Z')
                     || (c == '.')) {
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

auto
unexpencted_lexem(const std::string &str)
{
  return std::runtime_error("Unexpected lexem '" + str + "'");
}

template <typename source_type, typename target_type>
target_type
convert_type(source_type src)
{
  if (std::numeric_limits<target_type>::min() <= src &&
      src <= std::numeric_limits<target_type>::max()) {
    return src;
  } else {
    std::stringstream buffer;
    buffer << src;
    throw unexpencted_lexem(buffer.str());
  }
}

template <typename value_type>
auto
parse_value(const std::string &str)
{
  value_type result;
  std::istringstream buffer(str);
  buffer >> result;

  const size_t max_length = std::numeric_limits<value_type>::digits10 +
                            std::numeric_limits<value_type>::min_exponent10;

  if (buffer.peek() != EOF || str.size() > max_length) {
    throw unexpencted_lexem(str);
  } else {
    return result;
  }
}

template <>
auto
parse_value<int32_t>(const std::string &str)
{
  auto result = parse_value<int64_t>(str);
  return convert_type<int64_t, int32_t>(result);
}

template <>
auto
parse_value<double>(const std::string &str)
{
  auto result = parse_value<long double>(str);
  return convert_type<long double, double>(result);
}

template <typename value_type>
class Parser {
private:

  value_type
  prim()
  {
    if (next->first == Token::Number) {
      auto number = parse_value<value_type>(next->second);
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
        throw unexpencted_lexem(next->second);
      }
    } else {
      throw unexpencted_lexem(next->second);
    }
  }

  value_type
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

        if (std::fabs(prim) <= FLT_EPSILON) {
          throw std::runtime_error("Zero division");
        }

        term /= prim;
      }
    }
    return term;
  }

  value_type
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
      throw unexpencted_lexem(next->second);
    }
  }

  Lexems::const_iterator next;

public:
  value_type result;

  Parser(Lexems::const_iterator &&_next) :
    next(_next),
    result(value_type())
  {
    this->result = this->expr();
    this->eof(); // eof should be last
  }
};

// Calculator

template<typename value_type>
value_type
calc(const std::string &str)
{
  return Parser<value_type>(Lexer(str).lexems.cbegin()).result;
}

// Tests

void check(bool value)
{
  if (!value) {
    std::cerr << "error" << std::endl;
    exit(EXIT_FAILURE);
  } else {
    std::cerr << ".";
  }
}

using Block = std::function<void ()>;

void
raises(const Block &block)
{
  bool raises = false;
  try {
    block();
  } catch(const std::runtime_error &) {
    raises = true;
  }
  check(raises);
}

void
test_parser() {
  std::cerr << "test_parser";

  check(parse_value<int>("123") == 123);
  check(std::fabs(parse_value<double>("123.456") - 123.456) <= FLT_EPSILON);
  check(std::fabs(parse_value<double>("123.456") - 123.456) <= FLT_EPSILON);
  check(std::fabs(parse_value<double>("1e100") - 1e100) <= FLT_EPSILON);
  raises([]{ parse_value<double>("1e500"); });
  check(std::fabs(parse_value<long double>("1e500") - 1e500L) <= FLT_EPSILON);

  std::cerr << "OK" << std::endl;
}

void
test_calc() {
  std::cerr << "test_calc";

  check(calc<int>("12 + 2") == 14);
  check(calc<int>("12 * 2") == 24);
  check(calc<int>("12 - 2") == 10);
  check(calc<int>("12 / 2") == 6);
  check(calc<int>("2 + 2 * 2") == 6);

  check(std::fabs(calc<double>("12 + 20") - 32) <= FLT_EPSILON);
  check(std::fabs(calc<double>("12 * 20") - 240) <= FLT_EPSILON);
  check(std::fabs(calc<double>("12 - 20") - -8) <= FLT_EPSILON);
  check(std::fabs(calc<double>("12 / 20") - 0.6) <= FLT_EPSILON);

  raises([]{ calc<int>("1 / 0"); });
  raises([]{ calc<double>("1 / 0"); });
  raises([]{ calc<long double>("1 / 0"); });

  raises([]{ calc<int>("1e500"); });
  raises([]{ calc<double>("1e500"); });
  check(std::fabs(calc<long double>("1e500") - 1e500L) <= FLT_EPSILON);

  std::cerr << "OK" << std::endl;
}

void
run_tests() {
  test_parser();
  test_calc();
}

int
main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " expression" << std::endl;
    std::cerr << "    or " << argv[0] << " test" << std::endl;
    return 1;
  } else if (argv[1] == std::string("test")) {
    run_tests();
    return 0;
  } else {
    try {
      // Get lexems and parse it!
      std::cout << calc<double>(argv[1]) << std::endl;
    } catch (const std::runtime_error &error) {
      std::cerr << "INVALID" << std::endl;
      return 1;
    }
    return 0;
  }
}
