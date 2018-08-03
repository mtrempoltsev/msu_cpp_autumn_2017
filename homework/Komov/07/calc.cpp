#include <iostream>
#include <map>
#include <limits>
#include <cmath>

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

template <class T> struct NumericTraits{};

template <> struct NumericTraits <double> {
	
	static constexpr double min = numeric_limits<double>::min();
	static constexpr double max = numeric_limits<double>::max();
};

template <> struct NumericTraits <int> {
	
	static constexpr int min = numeric_limits<int>::min();
	static constexpr int max = numeric_limits<int>::max();
};

template <> struct NumericTraits <long> {
	
	static constexpr long min = numeric_limits<long>::min();
	static constexpr long max = numeric_limits<long>::max();
};

template <class T> struct Parser {};

template <> struct Parser <int> {

	static int Get(const char*& input) {
  	
		--input;
		auto c = *input;
		int n = 0;
	    
		while (c >= '0' && c <= '9') {
		
			n = 10 * n + (c - '0');
			++input;
			c = *input;
		}

		if (n < NumericTraits<int>::min || n > NumericTraits<int>::max)
	    		throw "Error (overflow)";

		return n;
	}
};

template <> struct Parser <long> {
	
	static long Get(const char*& input) {
		
		--input;
		auto c = *input;
		long n = 0;
	    
		while (c >= '0' && c <= '9') {
		
	    		n = 10 * n + (c - '0');
			++input;
	    		c = *input;
		}
	
		if (n < NumericTraits<long>::min || n > NumericTraits<long>::max)
	    		throw "Error (overflow)";
	
		return n;
	}
};

template <> struct Parser <double> {
	
	static double Get(const char*& input) {
		
		double frac = 10;
		--input;
		auto c = *input;
		double n = 0;
	    
		if (c == '.')
	    		throw "Not a number";
	
		while (c >= '0' && c <= '9') {

			n = 10 * n + (c - '0');
			++input;
			c = *input;
		}
	
		if (c == '.') {
	    	
	      		++input;
	      		c = *input;
	
	      		if (c >= '0' && c <= '9')
	        		while (c >= '0' && c <= '9')
	        		{
		          		n += (c - '0') / frac;
		          		frac *= 10;
		          		++input;
		          		c = *input;
	        		}
	    		else
	        		throw "There are no numbers after point";
		}
	
		if (n < NumericTraits<double>::min || n > NumericTraits<double>::max)
			throw "Error (overflow)";
	    
		return n;
	}
};

template <class T> class Calculator {

	public:
	  	Calculator();
	  	Calculator(const char*& input);
	  	T expression();
	  	int bracket_count;
	
	private:
	  	Token nextToken();
	  	T primary();
	  	T term();
	  	
	  	Token token;
	  	const char* input;
};

template <class T> Calculator<T>::Calculator() {
	
	input = nullptr;
	token = Token::Null;
	
	bracket_count = 0;
}

template <class T> Calculator<T>::Calculator(const char*& inp) {
	
	token = Token::Null;
	input = inp;
	
	bracket_count = 0;
}

template <class T> Token Calculator<T>::nextToken() {
	
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

		if (c == 'e') {
			
	    		return Token::Exp;
		}

		return Token::Invalid;
	}

  	return Token::End;
}

template <class T> T Calculator<T>::expression () {
	
	T result = term();
	
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

template <class T> T Calculator<T>::term () {
	
	T result = primary();
	
	while (token != Token::End) {
    
		switch(token) {
			
	    		case Token::Multiply: {
	        	
				result *= primary();
				break;
			}
			case Token::Divide: {
	        	
				T n = primary();
				
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

template <class T> T Calculator<T>::primary () {
  	
	token = nextToken();
  	
	switch(token) {
		
		case Token::Number: {
	      	
			T n = Parser<T>::Get(input);
	      		token = nextToken();
	      	
			return n;
		}
		case Token::Exp: {
	    	
			T n = constants["e"];
	        	token = nextToken();
	        
			return n;
		}
		case Token::Pi: {
	        
	        	T n = constants["Pi"];
	        	token = nextToken();
	        
			return n;
		}
		case Token::Left_bracket: {
	        
			bracket_count++;
	        	T n = expression();
	        
			if (token != Token::Right_bracket) {
	        	
				throw "The right bracket is needed";
				break;
	        	}
	        
			token = nextToken();

			return n;
		}
		case Token::Null: {
	        
			T n = 0;
	        	token = nextToken();
	        
			return n;
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
		Calculator<double> calc(input);
		double result = calc.expression();

		if (calc.bracket_count != 0) {
	      	
			cout << "Incorrect number of brackets" << endl;
			return 1;
		}

		cout << result << endl;
		return 0;
  	}
	catch (const char* s) {
  		
    		cout << s << endl;
		return 1;
	}
}

