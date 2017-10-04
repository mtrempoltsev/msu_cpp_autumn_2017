#include <string>
#include <cctype>
#include <cstdlib>

/*
* Exit codes
* 1: incorrect expression notation
* 2: division by zero
*/

using str_it = std::string::const_iterator;

int safe_division(int a, int b) {
	if (b == 0) {
		exit(2);
	}
	return a / b;
}

enum class Operation {
	add,
	sub,
	mul,
	div,
	notOp,
	endOfExpr
};

str_it skipSpaces(str_it it, str_it end) {
	if (it == end) {
		return end;
	}
	while (std::isspace(*it)) {
		it++;
	}
	return it;
}

str_it nextTokenPos(str_it it, str_it end) {
	if (it == end) {
		return end;
	}
	return skipSpaces(++it, end);
}

str_it prevTokenPos(str_it it, str_it end) {
	if (it == end) {
		return end;
	}
	it--;
	while (std::isspace(*it)) {
		it--;
	}
	return it;
}

Operation getOpType(str_it it, str_it end) {
	if (it == end) {
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

int getNumberSign(str_it &it, str_it end) {
	if (it == end) {
		exit(1);
	}
	if (*it == '-') {
		it++;
		return -1;
	}
	return 1;
}

int getNumber(str_it &it, str_it end) {
	if (it == end || !std::isdigit(*it)) {
		exit(1);
	}
	int res = *it - '0';
	while (it + 1 != end && isdigit(*(it + 1))) {
		res = res * 10 + (*++it - '0');
	}
	return res;
}

int getPrim(str_it &it, str_it end) {
	int sign = getNumberSign(it, end);
	return sign * getNumber(it, end);
}

int getTerm(str_it &it, str_it end) {
	int res = getPrim(it, end);
	it = nextTokenPos(it, end);
	while (it != end) {
		Operation op = getOpType(it, end);
		if (op != Operation::mul && op != Operation::div) {
			break;
		}
		it = nextTokenPos(it, end);
		if (op == Operation::mul) {
			res *= getPrim(it, end);
		} else {
			res = safe_division(res, getPrim(it, end));
		}
		it = nextTokenPos(it, end);
	}
	it = prevTokenPos(it, end);
	return res;
}

int calcExpr(const std::string &s) {
	str_it it = s.begin();
	str_it end = s.end();
	if (it == end) {
		exit(1);
	}
	it = skipSpaces(it, end);
	int res = getTerm(it, end);
	it = nextTokenPos(it, end);
	while (it != end) {
		Operation op = getOpType(it, end);
		if (op == Operation::notOp) {
			exit(1);
		}
		if (op == Operation::endOfExpr) {
			break;
		}
		it = nextTokenPos(it, end);
		if (op == Operation::add) {
			res += getTerm(it, end);
		} else if (op == Operation::sub) {
			res -= getTerm(it, end);
		} else {
			exit(1);
		}
		it = nextTokenPos(it, end);
	}
	return res;
}
