#ifndef CALC_HPP
#define CALC_HPP

#include <iostream>
#include <sstream>
#include <unordered_map>
#include <limits>

using namespace std;

template <typename T>
struct NumericTraits {};

template <>
struct NumericTraits<double> {
	static constexpr double min = std::numeric_limits<double>::min();
	static constexpr double max = std::numeric_limits<double>::max();
};

template <>
struct NumericTraits<int> {
	static constexpr int min = std::numeric_limits<int>::min();
	static constexpr int max = std::numeric_limits<int>::max();
};

template <>
struct NumericTraits<long> {
	static constexpr long min = std::numeric_limits<long>::min();
	static constexpr long max = std::numeric_limits<long>::max();
};


template <class T>
class Calculator {

public:
	Calculator() {
		init_constants();
	}

	~Calculator() {}

	T eval(char* expr);	// calculate the value of input expression

	static std::unordered_map<std::string, T> constants;

private:

	void init_constants() {
		constants["Pi"] = (T)3.14;
		constants["e"] = (T)2.7;
	}

	bool is_letter(char c) {
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	bool is_digit(char c) {
		return (c >= '0' && c <= '9');
	}

	void skip_spaces(char*& expr) {
		while (*expr == ' ') {
			expr++;
		}
	}

	// [GET_PRIM]: parsing [+-]?(?:Pi|e|\d+)
	T get_prim(char*& expr);
	// int get_prim(char*& expr);
	// double get_prim(char*& expr);

	// [GET_TERM]: parsing 'prim | term * prim | term / prim'
	T get_term(char*& expr);

	// [GET_EXPR]: parsing 'expr = term | expr + term | expr - term'
	T get_expr(char*& expr);

	// IF '(' THEN opened_brackets_cnt += 1
	// ELSE IF ')' THEN opened_brackets_cnt -= 1
	// ENDIF
	int opened_brackets_cnt;
};

#endif
