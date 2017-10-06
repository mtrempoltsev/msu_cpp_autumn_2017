#include <iostream>
#include <stdexcept>

enum class Token {
	Plus,
	Minus,
	Mult,
	Div,
	Num,
	End,
	Invalid,
};

std::string tokenToStr(Token token) {
	switch (token) {
		case Token::Plus: return "Plus";
		case Token::Minus: return "Minus";
		case Token::Mult: return "Mult";
		case Token::Div: return "Div";
		case Token::Num: return "Num";
		case Token::End: return "End";
		case Token::Invalid: return "Invalid";
	}
	return "Unknown";
}

Token _getToken(const char*& str, int& val) { // if token is a number then put it into val
	while (auto c = *str++) {
		switch (c) {
			case ' ': continue; // Skip whitespaces
			case '+': return Token::Plus;
			case '-': return Token::Minus;
			case '*': return Token::Mult;
			case '/': return Token::Div;
		}

		if ((c >= '0') && (c <= '9')) {
			val = c - '0';
			while ((*str >= '0') && (*str <= '9')) { // str is pointing at symbol following c
				val = val * 10 + (*str++) - '0'; //Shift digits on one position left and write new digit there
			}
			return Token::Num;
		}
		throw std::runtime_error(std::string("Invalid symbol: ") + c);
		//return Token::Invalid;
	}
	return Token::End;
}

int getToken(const char*& str, Token& nextToken) {
	int val = 0;
	nextToken = _getToken(str, val);
	return val;
}

int getNumber(const char*& str, Token& nextToken) {
	int number = getToken(str, nextToken);
	if (nextToken == Token::Num) {
		getToken(str, nextToken);
		return number;
	}
	if (nextToken == Token::Minus) { // Numbers may start with '-' sign
		number = -getToken(str, nextToken);
		if (nextToken == Token::Num) {
			getToken(str, nextToken); // When we done with a number we need to read token for next operation ('*', '/', '+', '-', 'EOF')
			return number;
		}
	}
	throw std::runtime_error("Unexpected token: " + tokenToStr(nextToken));
	return 0;
}

int getItem(const char*& str, Token& nextToken) {
	int result = getNumber(str, nextToken);
	while ((nextToken == Token::Mult) || (nextToken == Token::Div)) {
		if (nextToken == Token::Mult) {
			result *= getNumber(str, nextToken);
		} else {
			int num = getNumber(str, nextToken);
			if (num == 0) {
				throw std::runtime_error("Zero division!");
			}
			result /= num;
		}
	}
	return result;
}

int calc(const char* str) {
	Token nextToken;
	int result = getItem(str, nextToken); // Here we add or subtract items. Item is a sequence of multiplications/divisions
	while ((nextToken == Token::Plus) || (nextToken == Token::Minus)) {
		if (nextToken == Token::Plus) {
			result += getItem(str, nextToken);
		} else {
			result -= getItem(str, nextToken);
		}
	}
	return result;
}

int assert(const char* expr, int expect) {
	static int testNumber = 1;
	int result = calc(expr);
	if (result == expect) {
		std::cout << "Test " << testNumber << " succeeded! (" << expr << " = " << expect << ")" << std::endl;
		++testNumber;
		return 0;
	} else {
		std::cout << "Test " << testNumber << " failed. :(" << std::endl;
		std::cout << "For [" << expr << "] got " << result << ". " << expect << " expexted." << std::endl;
		++testNumber;
		return 1;
	}
}

int doTests() {
	int fails = 0;
	fails += assert("1", 1);
	fails += assert("01", 1);
	fails += assert("123", 123);
	fails += assert("1 + 1", 2);
	fails += assert("2 * 2", 4);
	fails += assert("1 + 2 * 3", 7);
	fails += assert("2 * 3 + 1", 7);
	fails += assert("2 * 3 * 4 * 5 * 6", 720);
	fails += assert("1 + 2 + 3 + 4", 10);
	fails += assert("1 + 2 * 3 + 4 * 5 + 6 * 7 + 8 * 9 * 10", 789);
	fails += assert("-5", -5);
	fails += assert("1 + -1", 0);
	fails += assert("1 - -1", 2);
	fails += assert("2 + 10 * -1 + 1", -7);
	fails += assert("1+-2", -1);
	fails += assert("-1", -1);
	fails += assert("-1 - 1 -5 -8*0", -7);
	fails += assert("10*2/7", 2);
	fails += assert("10*2/-7", -2);
	fails += assert("20/-7", -2);

	if (fails == 0) {
		std::cout << "All tests have passed successfully!" << std::endl;
	}
	return fails;
}

int main(int argc, char const *argv[]) {
	try {
		if (argc > 1) {
			std::cout << calc(argv[1]) << std::endl;
		} else {
			doTests();
		}
	} catch (const std::runtime_error& e) {
		std::cout << "During calculation error occured: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}