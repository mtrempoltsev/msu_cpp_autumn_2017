#include <iostream>
#include <stdexcept>
#include <unordered_map>

enum class Token {
	Plus,
	Minus,
	Mult,
	Div,
	Num,
	OpenBracket,
	CloseBracket,
	Word,
	End,
	Invalid,
};

class Tokenizer {
public:
	void set(const char* str) {
		this->str = str;
		value = 0;
		currentToken = Token::Invalid;
	}

	int getToken() {
		while (auto c = *str++) {
			switch (c) {
				case ' ':
					continue; // Skip whitespaces
				case '+':
					currentToken = Token::Plus;
					return 0;
				case '-':
					currentToken = Token::Minus;
					return 0;
				case '*':
					currentToken = Token::Mult;
					return 0;
				case '/':
					currentToken = Token::Div;
					return 0;
				case '(':
					++level;
					currentToken = Token::OpenBracket;
					return 0;
				case ')':
					--level;
					if (level < 0) {
						throw std::runtime_error("Unexpected ')'");
					}
					currentToken = Token::CloseBracket;
					return 0;
			}
			
			if ((c >= '0') && (c <= '9')) {
				value = c - '0';
				while ((*str >= '0') && (*str <= '9')) { // str is pointing at symbol following c
					value = value * 10 + (*str++) - '0'; // Shift digits on one position left and write new digit there
				}
				currentToken = Token::Num;
				return value;
			}

			if (std::isalpha(c)) {
				int i = 0;
				wordBuffer[i] = c;
				while (std::isalpha(*str)) { // probably it should be alphanum
					wordBuffer[++i] = *str++;
				}
				wordBuffer[++i] = 0;
				currentToken = Token::Word;
				return 0;
			}
			throw std::runtime_error(std::string("Invalid symbol: ") + c);
			//return Token::Invalid;
		}
		if (level > 0) {
			throw std::runtime_error(std::string("Expected ") + std::to_string(level) + std::string(" more ')'."));
		}
		currentToken = Token::End;
		return 0;
	}

	std::string tokenToStr(Token token) {
		switch (token) {
			case Token::Plus: return "Plus";
			case Token::Minus: return "Minus";
			case Token::Mult: return "Mult";
			case Token::Div: return "Div";
			case Token::Num: return "Num";
			case Token::OpenBracket: return "OpenBracket";
			case Token::CloseBracket: return "CloseBracket";
			case Token::Word: return "Word";
			case Token::End: return "End";
			case Token::Invalid: return "Invalid";
		}
		return "Unknown";
	}

	Token getCurrentToken() {
		return currentToken;
	}

	int getValue() {
		return value;
	}

	char* getWordBuffer() {
		return wordBuffer;
	}

private:
	const char* str;
	Token currentToken;
	int value;
	char wordBuffer[128]; // this buffer is used for reading constants
	int level = 0; // number of '(' minus number of ')' encountered 
};

class Calculator {
public:

	int calculate(const char* str) {
		tokenizer.set(str);
		return _calc();
	}
private:
	Tokenizer tokenizer;

	std::unordered_map<std::string, double> constants = {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

	int _calc() { // Here we add or subtract items. Item is a sequence of multiplications/divisions
		int result = getItem();
		while ((tokenizer.getCurrentToken() == Token::Plus) || (tokenizer.getCurrentToken() == Token::Minus)) {
			if (tokenizer.getCurrentToken() == Token::Plus) {
				result += getItem();
			} else {
				result -= getItem();
			}
		}
		return result;
	}

	int getItem() {
		int result = getNumber();
		while ((tokenizer.getCurrentToken() == Token::Mult) || (tokenizer.getCurrentToken() == Token::Div)) {
			if (tokenizer.getCurrentToken() == Token::Mult) {
				result *= getNumber();
			} else {
				int value = getNumber();
				if (value == 0) {
					throw std::runtime_error("Zero division!");
				}
				result /= value;
			}
		}
		return result;
	}

	int getNumber() {
		int result = tokenizer.getToken();
		int sign = 1;
		if (tokenizer.getCurrentToken() == Token::Minus) { // Things may start with '-' sign
			result = tokenizer.getToken();
			sign = -1;
		}
		if (tokenizer.getCurrentToken() == Token::Num) { // The simplest case
			tokenizer.getToken(); // When we done with a number we need to read token for next operation ('*', '/', '+', '-', 'END')
			return result * sign;
		}
		if (tokenizer.getCurrentToken() == Token::OpenBracket) {
			result = _calc();
			if (tokenizer.getCurrentToken() == Token::CloseBracket) { // _calc() returns control if it encountered 'END' or ')'. Operation after ')' should be read
				tokenizer.getToken();
			}
			return result * sign;
		}
		if (tokenizer.getCurrentToken() == Token::Word) {
			auto wordContainer = constants.find(tokenizer.getWordBuffer());
			if (wordContainer == constants.end()) {
				throw std::runtime_error("Unknown word: " + std::string(tokenizer.getWordBuffer()));
			}
			result = wordContainer->second;
			tokenizer.getToken();
			return result * sign;
		}
		throw std::runtime_error("Unexpected token: " + tokenizer.tokenToStr(tokenizer.getCurrentToken()));
		return 0;
	}
};

int assert(const char* expr, int expect) {
	static int testNumber = 1;
	Calculator calc;
	int result = calc.calculate(expr);
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
	fails += assert("(1)", 1);
	fails += assert("(1) + 1", 2);
	fails += assert("1 + (1)", 2);
	fails += assert("(1) * 3", 3);
	fails += assert("(-1)", -1);
	fails += assert("3 * (-1)", -3);
	fails += assert("(2) * (1 + 5)", 12);
	fails += assert("(2) * (1 + 5) + (3 + 2) / (-2)", 10);
	fails += assert("2 * (1) + -2", 0);
	fails += assert("(5 + 3 * (8 / 3) * 4) + (1)", 30);
	fails += assert("(5 + 3 * (8 / Pi) * 4) + (1)", 30);
	fails += assert("-Pi", -3);
	fails += assert("Pi", 3);
	fails += assert("-(Pi)", -3);

	if (fails == 0) {
		std::cout << "All tests have passed successfully!" << std::endl;
	}
	return fails;
}

int main(int argc, char const *argv[]) {
	try {
		if (argc > 1) {
			Calculator calc;
			std::cout << calc.calculate(argv[1]) << std::endl;
		} else {
			doTests();
		}
	} catch (const std::runtime_error& e) {
		std::cout << "During calculation error occured: " << e.what() << std::endl;
		return 1;
	}
	
	return 0;
}