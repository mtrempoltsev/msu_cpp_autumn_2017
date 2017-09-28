#include <string>

using std::string;
using str_it = string::const_iterator;

enum class Operation {
	add,
	sub,
	mul,
	div,
	notOp
};

void toNextToken(str_it &it, str_it end) {
	if (it + 1 == end) {
		it = end;
	} else {
		it += 2;
	}
}

void toPreviousToken(str_it &it, str_it end) {
	if (it != end) {
		it -= 2;
	}
}

bool isEndTokenPos(str_it it, str_it end) {
	return it == end || *(it + 1) == ' ';
}

Operation getOpType(str_it it, str_it end) {
	if (!isEndTokenPos(it, end)) {
		return Operation::notOp;
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

int getNumberSign(str_it &it) {
	if (*it == '-') {
		it++;
		return -1;
	}
	return 1;
}

int getNumber(str_it &it, str_it end) {
	int res = *it - '0';
	while (it + 1 != end && isdigit(*(it + 1))) {
		res = res * 10 + (*++it - '0');
	}
	return res;
}

int getPrim(str_it &it, str_it end) {
	int sign = getNumberSign(it);
	return sign * getNumber(it, end);
}

int getTerm(str_it &it, str_it end) {
	int res = getPrim(it, end);
	toNextToken(it, end);
	while (it != end) {
		Operation op = getOpType(it, end);
		if (op != Operation::mul && op != Operation::div) {
			break;
		}
		toNextToken(it, end);
		if (op == Operation::mul) {
			res *= getPrim(it, end);
		} else {
			res /= getPrim(it, end);
		}
		toNextToken(it, end);
	}
	toPreviousToken(it, end);
	return res;
}

int calcExpr(const string &s) {
	str_it it = s.begin();
	str_it end = s.end();
	if (it == end) {
		return 0;
	}
	int res = getTerm(it, end);
	toNextToken(it, end);
	while (it != end) {
		Operation op = getOpType(it, end);
		if (op == Operation::notOp) {
			break;
		}
		toNextToken(it, end);
		if (op == Operation::add) {
			res += getTerm(it, end);
		} else {
			res -= getTerm(it, end);
		}
		toNextToken(it, end);
	}
	return res;
}
