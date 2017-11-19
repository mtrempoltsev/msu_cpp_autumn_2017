#ifndef CALC_CPP
#define CALC_CPP

#include "../include/calc.hpp"


template <class T>
std::unordered_map<std::string, T> Calculator<T>::constants;

template <>
int Calculator<int>::get_prim(char*& expr) {
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

		long double prim = get_expr(expr);

		if (*expr != ')') {
			throw RuntimeError("mismached brackets - an extra \"(\"");
		}

		expr++;
		opened_brackets_cnt--;

		return is_negative ? (-prim) : (prim);
	}

	long double prim = 0;

	if (is_digit(*expr)) {
		do {
			prim = 10 * prim + (*expr - '0');

			if (prim < NumericTraits<int>::min || prim > NumericTraits<int>::max) {
				throw RangeError("invalid range for 'int' type");
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
			throw RuntimeError("constant \"" + s + "\" is not found");
		}
	}

	return is_negative ? (-prim) : (prim);
}

template <>
long Calculator<long>::get_prim(char*& expr) {
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

		long double prim = get_expr(expr);

		if (*expr != ')') {
			throw RuntimeError("mismached brackets - an extra \"(\"");
		}

		expr++;
		opened_brackets_cnt--;

		return is_negative ? (-prim) : (prim);
	}

	long double prim = 0;

	if (is_digit(*expr)) {
		do {
			prim = 10 * prim + (*expr - '0');

			if (prim < NumericTraits<long>::min || prim > NumericTraits<long>::max) {
				throw RangeError("invalid range for 'long' type");
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
			throw RuntimeError("constant \"" + s + "\" is not found");
		}
	}

	return is_negative ? (-prim) : (prim);
}

template <>
double Calculator<double>::get_prim(char*& expr) {
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

		long double prim = get_expr(expr);

		if (*expr != ')') {
			throw RuntimeError("mismached brackets - an extra \"(\"");
		}

		expr++;
		opened_brackets_cnt--;

		return is_negative ? (-prim) : (prim);
	}

	// integral part of prim
	long double floor = 0;

	// fractional part of prim
	long double frac = 0;

	long double prim = 0;

	// true if floor part of double exists
	bool floor_part = false;

	// true if fractional part of double exists
	bool frac_part = false;

	double pow10 = 1.0;

	// comma flag for double
	bool comma = false;

	if (is_digit(*expr) || *expr == '.') {
		do {
			if (*expr == '.') {
				if (comma) {
					throw RuntimeError("invalid character \".\"");
				}

				expr++;
				comma = true;

				continue;
			}

			if (comma) {
				frac = frac * 10 + (*expr - '0');
				pow10 /= 10;
				frac_part = true;
			} else {
				floor = 10 * floor + (*expr - '0');
				floor_part = true;
			}

			expr++;
		} while (is_digit(*expr) || *expr == '.');

		prim = floor + frac * pow10;

		if (!frac_part && !floor_part) {
			throw RangeError("invalid notation for 'double' type");
		}
	} else if (is_letter(*expr)) {
		string s;

		do {
			s += *expr;
			expr++;
		} while (is_letter(*expr));

		if (constants.find(s) != constants.end()) {
			prim = constants[s];
		} else {
			throw RuntimeError("constant \"" + s + "\" is not found");
		}
	}

	if (prim < -NumericTraits<double>::min || prim > NumericTraits<double>::max) {
		throw RangeError("invalid range for 'double' type");
	}

	return is_negative ? -(prim) : (prim);
}

template <class T>
T Calculator<T>::get_term(char*& expr) {
	T term_1 = get_prim(expr);

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

			T term_2 = get_prim(expr);

			if (term_2 == 0) {
				throw LogicError("division by zero in \"" + std::to_string(term_1) + " / " + std::to_string(term_2) + "\"");
			}

			term_1 /= term_2;

			break;
		}
		default:
			return term_1;
		}
	}
}

template <class T>
T Calculator<T>::get_expr(char*& expr) {
	T term_1 = get_term(expr);

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

template <class T>
T Calculator<T>::eval(char* expr) {
	if (*expr == '\0') {
		throw ArgumentError("input expression is empty");
	}

	opened_brackets_cnt = 0;

	T result = get_expr(expr);

	if (opened_brackets_cnt != 0 || *expr == ')') {
		throw RuntimeError("mismached brackets - an extra \")\"");
	}

	if (*expr != '\0') {
		throw RuntimeError("invalid character \"" + std::to_string(*expr) + "\"");
	}

	return result;
}

#endif
