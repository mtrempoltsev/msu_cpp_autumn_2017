#include <iostream>
#include <map>

using namespace std;

map <string, double> constants = { { "e", 2.73 }, { "Pi", 3.14 } };

enum class Token {

	Minus,
	Plus,
	Multiply,
	Divide,
	Left_bracket,
	Right_bracket,
	Number,
	Exp,
	Pi,
	End,
	Null,
	Invalid
};

class Calculator {

	public:
	  
		Calculator();
		Calculator(const char*& input);
		
		int expression();
		int bracket_count;

	private:
	  
		Token nextToken();
	
		int primary();
		int term();
		
		Token token;
		const char* input;
};

Calculator::Calculator() {

	token = Token::Null;
	input = nullptr;

	bracket_count = 0;
}

Calculator::Calculator(const char*& input_) {
  
	token = Token::Null;
	input = input_;

	bracket_count = 0;
}

Token Calculator::nextToken() {
	
	while (auto c = *input++) {

		switch (c) {

		  case ' ': continue;
		  case '-': return Token::Minus;
		  case '+': return Token::Plus;
		  case '*': return Token::Multiply;
		  case '/': return Token::Divide;
		  case '(': return Token::Left_bracket;
		  case ')': return Token::Right_bracket;
		}

		if (c >= '0' && c <= '9')
			return Token::Number;
	    
		if (c == 'P') {

			c = *input++;

			if (c == 'i') {

				return Token::Pi;
			}
			else 
				return Token::Invalid;
		}

		if (c == 'e')
			return Token::Exp;
    
		return Token::Invalid;
	}
  
	return Token::End;
}

int Calculator::expression() {
  
	int result = term();
  
	while (token != Token::End) {
    
		switch(token) {

			case Token::Plus: {

				result += term();
				break;
			}
			case Token::Minus: {

				result -= term();
				break;
			}
			case Token::End: {

				return result;
			}
			default:
				return result;
		}
	}
  
	return result;
}

// Summands
int Calculator::term() {

	int result = primary();

	while (token != Token::End) {

		switch(token) {

			case Token::Multiply:{
			
				result *= primary();
				break;
			}
			case Token::Divide: {

				int n = primary();
				
				if (n == 0) {

					throw "ZeroDivisionError";
					break;
				}
				else {
					
					result /= n;
					break;
				}
			}
			case Token::Plus: {

				return result;
			}
			case Token::Minus: {

				return result;
			}
			case Token::End: {

				return result;
			}
			case Token::Right_bracket: {

				bracket_count--;
				return result;
			}
			default:
				throw "Invalid expression (term)";
			
			return result;
		}
	}
  
	return result;
}

int Calculator::primary() {

	token = nextToken();
	
	switch(token){
		
		case Token::Number: {
		
			--input;
			
			auto c = *input;
			
			int n = 0;
			
			while (c >= '0' && c <= '9') {
			
				n = 10 * n + (c - '0');
				++input;
				c = *input;
			}

			token = nextToken();
			return n;
		}
		case Token::Exp: {
			
			double n = 0;
			n = constants["e"];
			token = nextToken();

			return n;
		}
		case Token::Pi: {
			
			double n = 0;
			n = constants["Pi"];
			
			token = nextToken();
			return n;
		}

		// If the character is a left bracket then it starts to count the value of expression.
		case Token::Left_bracket: {
			
			bracket_count++;
			int num = expression();
			
			if (token != Token::Right_bracket) {
			
				throw "The right bracket is needed";
      			break;
			}

			token = nextToken();
			return num;
		}
		case Token::Null: {

			int num = 0;
			token = nextToken();
			
			return num;
		}

		// Unary minus
		case Token::Minus: {
		
			return -primary();
		}
		default:
			throw "Invalid expression (primary)";
		
		return 1;
	  }
}

int main(int argc, char* argv[])
{
	
	if (argc != 2) {
		
		cout << "Invalid input expression (argc)" << endl;
		
		return 1;
	}	
	
	try {

		const char* input = argv[1];
		
		Calculator calc(input);
		
		int result = calc.expression();

		if (calc.bracket_count != 0) {

			cout << "Incorrect number of brackets" << endl;
			
			return 1;
		}

		cout << result << endl;

		return 0;
	}
	catch(const char* str) {

		cout << str << endl;

		return 1;
	}
}
