#ifndef CALC_CPP
#define CALC_CPP

#include "../include/calc.hpp"

std::unordered_map<std::string, double> Calculator::constants;


int Calculator::get_prim(char*& expr) {
	skip_spaces(expr);

	bool is_negative = false;

	switch (*expr) {
	case '+': {
		expr++;

		break;
	}
	case '-': {
		is_negative = true;

		expr++;

		break;
	}
	default:
		break;
	}

	if (*expr == '(') {
		expr++;
		opened_brackets_cnt++;

		int prim = get_expr(expr);

		if (*expr != ')') {
			std::stringstream err;
			err << "Mismached brackets: an extra \"(\"" << endl;

			throw std::runtime_error(err.str());
		}

		expr++;
		opened_brackets_cnt--;

		return is_negative ? (-prim) : (prim);
	}

	int prim = 0;

	if (is_digit(*expr)) {
		do {
			prim = 10 * prim + (*expr - '0');

			if (value > NumericTraits<int>::max || value < NumericTraits<int>::min) {
				cout << "error" << endl;
				exit(0);
			}

			expr++;
		} while (is_digit(*expr));
	} else if (is_letter(*expr)) {
		string s;

		do {
			s += *expr;
			expr++;
		} while (is_letter(*expr));

		if (constants.find(s) != constants.end()) {
			prim = constants[s];
		} else {
			std::stringstream err;
			err << "Constant: \"" << s << "\" is not found" << endl;

			throw std::runtime_error(err.str());
		}
	}

	return is_negative ? (-prim) : (prim);
}

int Calculator::get_term(char*& expr) {
	int term_1 = get_prim(expr);

	while (1) {
		skip_spaces(expr);

		char op = *expr;

		switch (op) {
		case '*': {
			expr++;

			term_1 *= get_prim(expr);

			break;
		}
		case '/': {
			expr++;

			int term_2 = get_prim(expr);

			if (term_2 == 0) {
				std::stringstream err;
				err << "Division by zero: \"" << term_1 << " / " << term_2 << "\"" << endl;

				throw std::runtime_error(err.str());
			}

			term_1 /= term_2;

			break;
		}
		default:
			return term_1;
		}
	}
}

int Calculator::get_expr(char*& expr) {
	int term_1 = get_term(expr);

	while (1) {
		skip_spaces(expr);

		char op = *expr;

		switch (op) {
		case '+': {
			expr++;

			term_1 += get_term(expr);

			break;
		}
		case '-': {
			expr++;

			term_1 -= get_term(expr);

			break;
		}
		default:
			return term_1;
		}
	}
}

int Calculator::eval(char* expr) {
	if (*expr == '\0') {
		std::stringstream err;
		err << "Error: input expression is empty" << endl;

		throw std::runtime_error(err.str());
	}

	opened_brackets_cnt = 0;

	int result = get_expr(expr);

	if (opened_brackets_cnt != 0 || *expr == ')') {
		std::stringstream err;
		err << "Mismached brackets: an extra \"" << *expr << "\"" << endl;

		throw std::runtime_error(err.str());
	}

	if (*expr != '\0') {
		std::stringstream err;
		err << "Invalid character: \"" << *expr << "\"" << endl;

		throw std::runtime_error(err.str());
	}

	return result;
};

#endif
