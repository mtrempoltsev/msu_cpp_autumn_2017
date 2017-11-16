#include <iostream>

using namespace std;

enum class Token
{
    Minus,
    Plus,
    Multiply,
    Divide,
    Number,
    End
};

// Calculator grammatics:

// expr = term
//     | expr - term
//     | expr + term
// term = prim
//     | term / factor
//     | term * factor
// factor = number
//     | -number
// number = [0-9]+

Token next(const char*& input, int& n) {

    while(auto c = *input++) {

    	switch(c) {
			
		case ' ': continue;
        	case '-': return Token::Minus;
        	case '+': return Token::Plus;
        	case '*': return Token::Multiply;
        	case '/': return Token::Divide;
        }
       
        if (c >= '0' && c <= '9') {

		n = 0;
		
		while (c >= '0' && c <= '9') {
			
			// Multidigit number
			n = 10 * n + (c - '0');
			c = *input++;
		}
			
		--input;
            
		return Token::Number;
        }
        
        else {
        	
		cerr << "Invalid input expression (tokens)" << endl;

		exit(3);
	}
    }
    
    return Token::End;
}

int number(const char*& input) {
	
	int result = 0;
	Token token = next(input, result);
	
	if (token == Token::Number)
		return result;

	else if (token == Token::Minus)
		return -number(input); 
	
	else {
		
		cerr << "Invalid input expression (number)" << endl;
		
		exit(3);
	}	
}

int term(Token& last_token, const char*& input) {
	
	int new_number;
	int result = number(input);
	last_token = next(input, new_number); 

	while (last_token == Token::Multiply || last_token == Token::Divide || last_token == Token::Number) {
		
		if (last_token == Token::Multiply)
			result *= number(input);
		
		else if (last_token == Token::Divide) {
			
			size_t n = number(input);
			
			if (n == 0) {
				
				cerr << "ZeroDivisionError" << endl;
				
				exit(3);
			}
			
			else
				result /= n;
		}

		else
		{
			cerr << "Invalid input expression (term)" << endl;
			
			exit(3);
		}

		last_token = next(input, new_number);
	}

    return result;
}

int expr(const char*& input) {
	
	Token last_token;
	int result = term(last_token, input);

	while (last_token != Token::End) {
		
		if (last_token == Token::Plus)
			result += term(last_token, input);
		
		else if (last_token == Token::Minus)
			result -= term(last_token, input);
		
		else {
			cerr << "Invalid input expression (expr)" << endl;
			
			exit(3);
		}
	}

    return result;
}

int main(int argc, char* argv[])
{

	if (argc != 2) {
		
		cerr << "Invalid input expression (argc)" << endl;
		
		return 1;
	}

	const char* input = argv[1];

	auto result = expr(input);

	cout << result << endl;	

    return 0;
}
