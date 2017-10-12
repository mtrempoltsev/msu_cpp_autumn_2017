#include <string>
#include <iostream>
#include <unordered_map>
#include <math.h>
#include "errcalc.h"

using namespace std;

//This is enum for Tokens
enum class Token
{
	//Shows if error occured
	Error,
	//Shows if token found '+'
	Plus,
	//Shows if token found '-'
	Minus,
	//Shows if token found '/'
	Div,
	//Shows if token found '*'
	Mul,
	//Shows if token found is number
	Number,
	//Shows if token found is constant
	Constant,
	//Shows if token found '('
	OpenBracket,
	//Shows if token found ')'
	ClosedBracket,
	//Shows if there is EOF
	End
};
//This class is used for transforming string into sequence of tokens
class Tokenizer{
	public:
	//Two iterators, that iterate on the string
	string::const_iterator _start;
	string::const_iterator _finish;
	//Constructor of Tokenizer
	Tokenizer(string::const_iterator start, string::const_iterator finish){
		_start = start;
		_finish = finish;
	}
	//Function for getting token
	Token get_token()
	{
		//Move away all space symbols
		while (_start != _finish && isspace(*_start)) {
			_start++;
		}
		//Choose which token will be returned. (More description above)
		switch (*_start) {
			case '(':
				return Token::OpenBracket;
			case ')':
				return Token::ClosedBracket;
			case '-': 
				return Token::Minus;
			case '+': 
				return Token::Plus;
			case '*': 
				return Token::Mul;
			case '/': 
				return Token::Div;
			case '\0': 
				return Token::End;
		}
		//Check if current symbol is digit
		if (isdigit(*_start)) {
			return Token::Number;
		}
		//Check is current symbol could be the start of the constant)
		if (isalpha(*_start)) {
			return Token::Constant;
		}
		//If current symbol isn't digit, error has occured
		return Token::Error;
	}
};
//Class for parsing expressions
class Calculator{
	public:
	Tokenizer _tokenize;
	//Two iterators, that iterate on the string
	string::const_iterator _start;
	string::const_iterator _finish;
	//Map for constants
	unordered_map<string, double> _constants;
	//Constructor for Calculator
	Calculator(string::const_iterator start, string::const_iterator finish, unordered_map<string, double> constants, Tokenizer tok)
	: _start(start), _finish(finish), _constants(constants), _tokenize(tok) {}
	//Read number from string.
	double get_number(int flag){
		//Get the token
		Token tok = _tokenize.get_token();
		//We use this to synchrosize two iterators of different classes
		_start = _tokenize._start;
		//Start value of the res(which would be returned) is assigned as 0
		double res = 0;
		//Check if current symbol is really digit
		if(tok == Token :: Number){
			//Read while we can
			while(_start != _finish && isdigit(*_start)){
				//Now in digit we have number from 0 to 9
				double digit = *_start++ - '0';
				//We use this to synchrosize two iterators of different classes
				_tokenize._start = _start;
				//If the number is below zero
				if(flag){
					//We check if the overflow's occured
					if(check_overflow_mul(res, 10) && check_overflow_sub(res * 10, digit)){
						//If all is fine, we process symbol
						res = res * 10 - digit;
					}
					else{
						//If the overflow's occured, we leave the program
						exit(process_errors(OVERFLOW_CASE));
					}
				}
				//If the number is above or equal zero
				else{
					//We check if the overflow's occured
					if(check_overflow_mul(res, 10) && check_overflow_sum(res * 10, digit)){
						//If all is fine, we process symbol
						res = res * 10 + digit;
					}
					else{
						//If the overflow's occured, we leave the program
						exit(process_errors(OVERFLOW_CASE));
					}
				}
			}
			//Return number that we've got
			return res;
		}
		//If current symbol isn't digit, the expression has the error in it
		exit(process_errors(INVALID_EXPRESSION));
	}
	//This is function for making this action: prim = number | -number, referring to calculator's grammatics
	double get_prim() 
	{
		//In flag we contain information if number is or isn't below zero
		double flag = 0;
		//Get the token
		Token tok = _tokenize.get_token();
		_start = _tokenize._start;
		if (tok == Token :: Minus) {
			//If it is below zero, we make flag up
			_start++;
			_tokenize._start = _start;
			return (-1) * get_fact();
		}
		//Then we return the result of function get_number. Thar function already returns number with sign that we need
		return get_fact();
	}
	//This is function for making this action: term = prim | term * prim | term / prim, 
	//referring to calculator's grammatics
	 double get_term() 
	{
		//The res variable we move prim 
		 double res = get_prim();
		_start = _tokenize._start;
		//We find what operation is it (Or it isn't operation)
		Token op = _tokenize.get_token();
		_start = _tokenize._start;
		while (_start != _finish && (op == Token::Mul || op == Token::Div)) {
			//While we can execute '*' or '/' operations, we do this
			_start++;
			_tokenize._start = _start;
			//In the val we move the value of another operand of expression(res*val or res/val)
			 double val = get_prim();
			_start = _tokenize._start;
			if (op == Token::Mul) {
				//If it is multiplication, we check for overflow
				if(check_overflow_mul(res, val)){
					res *= val;
				}
				else{
					//If the overflow's occured, we leave the program
					exit(process_errors(OVERFLOW_CASE));
				}
			}
			else {
				//If it is division, we check for division by zero
				if(val != 0){
					res /= val;
				}
				else{
					//If division by zero's occured, we leave the program 
					exit(process_errors(DIVISION_BY_ZERO));
				}
			}
			//Then we get another token of operation
			op = _tokenize.get_token();
			_start = _tokenize._start;
		}
		//Check if the error's occured
		if(op == Token :: Error){
			//If the error's occured, we leave the program
			exit(process_errors(INVALID_EXPRESSION));
		}
		return res;
	}
	//In this part of program, expr = term | expr + term | expr - term is calculated
	//In get_term we've already calculated operations '*' and '/'
	double get_expression(){
		double res = get_term();
		_start = _tokenize._start;
		//We get the token of operation
		Token op = _tokenize.get_token();
		_start = _tokenize._start;
		//We need to process remaining operations '+' and '-'
		while (op == Token::Plus || op == Token::Minus) {
			_start++;
			_tokenize._start = _start;
			//We got another result of already calculated operations '*' and '/'
			double val = get_term();
			_start = _tokenize._start;
			if (op == Token::Plus) {
				//We check for overflow
				if(check_overflow_sum(res,val)){
					res += val;
				}
				else{
					//If the overflow's occured, we leave the program
					exit(process_errors(OVERFLOW_CASE));
				}
			}
			else {
				//We check for overflow
				if(check_overflow_sub(res,val)){
					res -= val;
				}
				else{
					//If the overflow's occured, we leave the program
					exit(process_errors(OVERFLOW_CASE));
				}
			}
			//Then we get another token of operation
			op = _tokenize.get_token();
			_start = _tokenize._start;
		}
		//If we haven't read to the end or to the end of the expression
		if(op != Token::End && op != Token::ClosedBracket){
			exit(process_errors(INVALID_EXPRESSION));
		}
		return res;
	}
	//In grammatics reference, fact = number | constant | (expr)
	double get_fact() {
		_tokenize._start = _start;
		//Get token
		Token tok = _tokenize.get_token();
		_start = _tokenize._start;
		//Find, whether token is number, constant, openbracket or invalid token
		if (tok == Token::Number) {
			//We get number from string
			double value = get_number(0);
			_tokenize._start = _start;
			return value;
		}

		if (tok == Token::Constant) {
			string constant_name = "";
			//In constant_name we read composition of letters, that could be a constant
			while(isalpha(*_start)){
				constant_name += *_start;
				_start++;
			}
			_tokenize._start = _start;
			//We check, if this composition of letters is a constant
			auto key_value = _constants.find(constant_name);
			if (key_value != _constants.end()) {
				return key_value->second;
			}
			else {
				exit(process_errors(INVALID_CONSTANT));
			}
		}
		
		if (tok == Token::OpenBracket) {
			_start++;
			_tokenize._start = _start;
			//We get result of expression in brackets
			double value = get_expression();
			//If brackets are mismatched, this is an error
			if (_tokenize.get_token() != Token::ClosedBracket) {
				exit(process_errors(MISMATCHED_BRACKET));
			}
			_start = _tokenize._start;
			_start++;
			_tokenize._start = _start;
			return value;
		}
		exit(process_errors(INVALID_EXPRESSION));
	}
};
int main(int argc, char** argv) {
	//If the command line arguments don't fit into our standart, we don't do
	if(argc != 2){
		exit(process_errors(INVALID_NUMBER_OF_ARGUMENTS));
	}
	//We iterate on this string
	string str = argv[1];
	//Map of constants
	unordered_map<string, double> constants = {
		{ "Pi", 3.14 },
		{ "e", 2.7 }
	};
	//Using const_iterators for iterating on the string
	string::const_iterator start = str.begin();
	string::const_iterator finish = str.end();
	if(start == finish){
		//If the string is empty, no actions are executed 
		return 0;
	}
	//Initialising objects of classes
	Tokenizer _tok = Tokenizer(start, finish);
	Calculator calc = Calculator(start, finish, constants, _tok);
	//Calculating expression
	double res = calc.get_expression();
	if(calc._tokenize.get_token() != Token::End){
		exit(process_errors(MISMATCHED_BRACKET));
	}
	printf("%lf", res);
	return 0;
}
