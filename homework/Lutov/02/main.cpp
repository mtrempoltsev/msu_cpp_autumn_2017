#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <utility>

enum class Token {
  Number,
  Plus,
  Minus,
  Multiply,
  Divide,
  Eof,
};

using Lexem = std::pair<Token, std::string>;
using Lexems = std::vector<Lexem>;

// Lexer

void
lexer_append_lexem(Lexems &lexems, Token token, const std::string &str)
{
  lexems.push_back(std::make_pair(token, str));
}

void
lexer_append_number_if_it_is_exist(Lexems &lexems, std::string &number)
{
  if (!number.empty()) {
    lexer_append_lexem(lexems, Token::Number, number);
    number = "";
  }
}

auto
lexer(const std::string &text)
{
  Lexems lexems;
  std::string number;

  for (auto c : text) {

    switch (c) {
      case ' ': lexer_append_number_if_it_is_exist(lexems, number);
                continue;

      case '+': lexer_append_number_if_it_is_exist(lexems, number);
                lexer_append_lexem(lexems, Token::Plus, "+");
                continue;

      case '-': lexer_append_number_if_it_is_exist(lexems, number);
                lexer_append_lexem(lexems, Token::Minus, "-");
                continue;

      case '*': lexer_append_number_if_it_is_exist(lexems, number);
                lexer_append_lexem(lexems, Token::Multiply, "*");
                continue;

      case '/': lexer_append_number_if_it_is_exist(lexems, number);
                lexer_append_lexem(lexems, Token::Divide, "/");
                continue;

      default: if ('0' <= c && c <= '9') {
                 number += c;
                 continue;
               }
    }

    throw std::runtime_error(std::string("Unexpected char ") + std::string(1, c));
  }

  lexer_append_number_if_it_is_exist(lexems, number);
  lexer_append_lexem(lexems, Token::Eof, "EOF");

  return lexems;
}

// Parser

auto
unexpencted_lexem(Lexems::const_iterator &next)
{
  return std::runtime_error("Unexpected lexem " + next->second);
}

intmax_t
parse_number(Lexems::const_iterator &next)
{
  if (next->first == Token::Number) {
    intmax_t number = std::stoll(next->second);
    ++ next;
    return number;
  } else {
    throw unexpencted_lexem(next);
  }
}

intmax_t
parse_prim(Lexems::const_iterator &next)
{
  // number | -number
  if (next->first == Token::Number) {
    return parse_number(next);
  } else if (next->first == Token::Minus) {
    ++ next;
    return -parse_number(next);
  } else {
    throw unexpencted_lexem(next);
  }
}

intmax_t
parse_term_tail(Lexems::const_iterator &next, intmax_t prev)
{
  // * prim term_tail | / prim term_tail
  if (next->first == Token::Multiply) {
    ++ next;
    intmax_t prim = parse_prim(next);
    return parse_term_tail(next, prev * prim);
  } else if (next->first == Token::Divide) {
    ++ next;
    intmax_t prim = parse_prim(next);
    if (prim == 0) {
      throw std::runtime_error("Zero division");
    }
    return parse_term_tail(next, prev / prim);
  } else {
    return prev;
  }
}

intmax_t
parse_term(Lexems::const_iterator &next)
{
  // prim term_tail
  if (next->first == Token::Number || next->first == Token::Minus) {
    intmax_t prim = parse_prim(next);
    return parse_term_tail(next, prim);
  } else {
    throw unexpencted_lexem(next);
  }
}

intmax_t
parse_expr_tail(Lexems::const_iterator &next, intmax_t prev)
{
  // + term expr_tail | - term expr_tail
  if (next->first == Token::Plus) {
    ++ next;
    intmax_t term = parse_term(next);
    return parse_expr_tail(next, prev + term);
  } else if (next->first == Token::Minus) {
    ++ next;
    intmax_t term = parse_term(next);
    return parse_expr_tail(next, prev - term);
  } else {
    return prev;
  }
}

intmax_t
parse_expr(Lexems::const_iterator &next)
{
  // term expr_tail
  if (next->first == Token::Number || next->first == Token::Minus) {
    intmax_t term = parse_term(next);
    return parse_expr_tail(next, term);
  } else {
    throw unexpencted_lexem(next);
  }
}

void
parse_eof(Lexems::const_iterator &next)
{
  if (next->first == Token::Eof) {
    ++ next;
  } else {
    throw unexpencted_lexem(next);
  }
}

intmax_t
parser(Lexems::const_iterator &&next)
{
  intmax_t result = parse_expr(next);
  parse_eof(next); // eof should be last
  return result;
}

int
main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " expression" << std::endl;
    return 1;
  } else {
    try {
      // Get lexems and parse it!
      std::cout << parser(lexer(argv[1]).cbegin()) << std::endl;
    } catch (const std::runtime_error &error) {
      std::cerr << "INVALID" << std::endl;
      return 1;
    }
    return 0;
  }
}
