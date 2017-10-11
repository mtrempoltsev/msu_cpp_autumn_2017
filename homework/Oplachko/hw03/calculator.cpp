#include <string>
#include <cctype>
#include <cstdlib>
#include <unordered_map>
#include "calculator.hpp"

/*
* Exit codes
* 1: incorrect expression notation
*/

std::unordered_map<std::string, double> Calculator::constants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

Calculator::Calculator(const std::string &t): s(t), it(s.begin()) { }

void Calculator::skipSpaces() {
	if (it == s.end()) {
		return;
	}
	while (std::isspace(*it)) {
		it++;
	}
}

void Calculator::backSkipSpaces() {
	if (it == s.end()) {
		return;
	}
	while (std::isspace(*it)) {
		it--;
	}
}

void Calculator::nextTokenPos() {
	if (it != s.end()) {
		it++;
		skipSpaces();
	}
}

void Calculator::prevTokenPos() {
	if (it != s.end()) {
		it--;
		backSkipSpaces();
	}
}

Operation Calculator::getOpType() {
	if (it == s.end()) {
		return Operation::endOfExpr;
	}
	switch (*it) {
	case '+':
		return Operation::add;
	case '-':
		return Operation::sub;
	case '*':
		return Operation::mul;
	case '/':
		return Operation::div;
	default:
		return Operation::notOp;
	}
}

int Calculator::getNumberSign() {
	if (it == s.end()) {
		exit(1);
	}
	if (*it == '-') {
		it++;
		return -1;
	}
	return 1;
}

bool Calculator::isThisConstant(const std::string &cons) {
	auto tmp_it = it;
	for (auto &c : cons) {
		if (tmp_it == s.end() || c != *tmp_it++) {
			return false;
		}
	}
	it = --tmp_it;
	return true;
}

double Calculator::getConstant() {
	for (auto &x : constants) {
		if (isThisConstant(x.first)) {
			return x.second;
		}
	}
	exit(1);
}

double Calculator::getNumber() {
	if (it == s.end()) {
		exit(1);
	}
	if (!std::isdigit(*it)) {
		return getConstant();
	}
	double res = *it - '0';
	while (it + 1 != s.end() && isdigit(*(it + 1))) {
		res = res * 10 + (*++it - '0');
	}
	if (it + 1 != s.end() && *(it + 1) == '.') {
		auto eon_it = it + 2;
		if (eon_it == s.end() || !std::isdigit(*eon_it)) {
			exit(1);
		}
		while (eon_it + 1 != s.end() && std::isdigit(*(eon_it + 1))) {
			eon_it++;
		}
		it = eon_it;
		while (*eon_it == '0') {
			eon_it--;
		}
		double frac_part = 0;
		while (std::isdigit(*eon_it)) {
			frac_part = (frac_part + (*eon_it-- - '0')) / 10;
		}
		res += frac_part;
	}
	return res;
}

double Calculator::getPrim() {
	int sign = getNumberSign();
	return sign * getNumber();
}

double Calculator::getExtPrim() {
	if (it != s.end() && *it == '(') {
		return calcExpr(true);
	}
	return getPrim();
}

double Calculator::getTerm() {
	double res = getExtPrim();
	nextTokenPos();
	while (it != s.end()) {
		Operation op = getOpType();
		if (op != Operation::mul && op != Operation::div) {
			break;
		}
		nextTokenPos();
		if (op == Operation::mul) {
			res *= getExtPrim();
		} else {
			res /= getExtPrim();
		}
		nextTokenPos();
	}
	prevTokenPos();
	return res;
}

double Calculator::calcExpr(bool begin_with_bracket) {
	if (it == s.end()) {
		exit(1);
	}
	skipSpaces();
	if (begin_with_bracket) {
		it++;
	}
	double res = getTerm();
	nextTokenPos();
	while (it != s.end() && (!begin_with_bracket || *it != ')')) {
		Operation op = getOpType();
		if (op == Operation::notOp) {
			exit(1);
		}
		if (op == Operation::endOfExpr) {
			break;
		}
		nextTokenPos();
		if (op == Operation::add) {
			res += getTerm();
		} else if (op == Operation::sub) {
			res -= getTerm();
		} else {
			exit(1);
		}
		nextTokenPos();
	}
	if (begin_with_bracket && it == s.end()) {
		exit(1);
	}
	return res;
}
