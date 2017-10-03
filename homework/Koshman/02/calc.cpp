#include <iostream>
#include <stdexcept>
using namespace std;

enum class Token
{
	Invalid,
	Minus,
	Plus,
	Mul,
	Div,
	Number,
	End
};


Token getToken(const char*& text, bool reverse = false, const char* limit = 0)
{
	// function for parsing tokens
	//
	//    text: the starting point
	// reverse: whether to move forward or backwards
	//   limit: the point to stop at when moving backwards


	while (const auto c = *text)
	{
		if (limit && reverse && (text <= limit))
			break;

		reverse ? (--text) : (++text);
		
		switch (c)
		{
			case ' ': continue;
			case '-': return Token::Minus;
			case '+': return Token::Plus;
			case '*': return Token::Mul;
			case '/': return Token::Div;
		}

		if (c >= '1' && c <= '9')
		{
			for (auto c = *text; c >= '0' && c <= '9';)
				{
					reverse ? (--text) : (++text);
					if (limit && reverse && (text <= limit))
						break;
					c = *text; 
				}
			return Token::Number;
		}
		return Token::Invalid;
	}
	return Token::End;

}


int number(const char* start, const char* end)
{

	// function for parsing numbers
	int result = 0;
	int sign = 1;

	//ignore trailing minus
	if (*end == '-')
		--end;
	
	while (start <= end){
		if (*start != ' '){
			if (*start == '-'){
				sign *= -1;
			} else {
				if (*start >= '0' && *start <= '9')
					result = result * 10 + *start - 48;
			}
		}
		++start;
	}
	return sign * result;

}


int term(const char* start, const char* end)
{
	// function for parsing terms

	// function invariant: start <= ptr1 <= ptr2 <= end
	// current token is between ptr1 and ptr2

	if (start == end)
		return number(start, end);
	const char* ptr1 = end;
	const char* ptr2 = end;

	while (ptr1 > start){
		// explanation why the pointer moves backwards is in the readme
		auto token = getToken(ptr1, true, start);
		if (token == Token::Mul)
		{
			return term(start, ptr1) * number(ptr2, end); 
		} else if (token == Token::Div) {
			int denominator = number(ptr2, end);
			if (not denominator)
				throw std::overflow_error("Exception: zero division");
			return term(start, ptr1) / denominator;
		}
		if (ptr1 == ptr2)
			--ptr1;
		ptr2 = ptr1;
	}

	return number(start, end);

}


int expr(const char* start, const char* end)
{	
	// function for parsing expressions

	// function invariant: start <= ptr1 <= ptr2 <= end
	// current token is between ptr1 and ptr2
	
	if (start >= end)
		return 0;

	// binaryMinus is needed to understand if we need to split the expression
	bool binaryMinus = false;
	const char* ptr1 = start;
	const char* ptr2 = start;

	while (ptr2 < end){
		auto token = getToken(ptr2);
		
		if (token == Token::Plus) {
			return term(start, ptr1) + expr(ptr2, end); 
		} else if ((token == Token::Minus) && binaryMinus){
			return term(start, ptr1) + expr(ptr1, end);
		}

		binaryMinus = (token == Token::Number) ? true : false;
		ptr1 = ptr2;
	}
	return term(start, end);

}


int main(int argc, char const *argv[])
{
	if (argc == 1){
		cout << "No expression provided";
		return 1;
	}
	const char* start = argv[1];
	const char* end = start;
	bool invalid = false;
	bool NAN = true; 

	auto token = getToken(end);
	while (token != Token::End)
	{	
		switch (token)
		{
			case Token::Invalid: {
				invalid = true;
				break;
			}
			case Token::Number: {
				if (not NAN)
					invalid = true;
				NAN = false;
				break;
			}
			case Token::Minus: {
				NAN = true;	
				break;
			}
			default: {
				if (NAN)
					invalid = true;
				NAN = true;
			}
		}
		if (invalid)
			break;
		token = getToken(end);
	}

	if (invalid || NAN){
		cout << "Invalid expression";
		return 1;
	} else {
		try {
	    	cout << expr(start, end);
	    } catch (std::overflow_error e) {
	        std::cout << e.what();
	        return 1;
	    }
	}	
	return 0;

}