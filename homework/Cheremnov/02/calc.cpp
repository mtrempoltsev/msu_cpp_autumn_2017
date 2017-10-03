#include <string>
#include <iostream>
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
    //Shows if there is EOF
    End
};

//Function for getting token
Token get_token(string::const_iterator &start, string::const_iterator finish)
{
	//Move away all space symbols
    while (start != finish && isspace(*start)) {
        start++;
    }
    //Choose which token will be returned. (More description above)
    switch (*start) {
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
    if (isdigit(*start)) {
        return Token::Number;
    }
	//If current symbol isn't digit, error has occured
    return Token::Error;
}
//Read number from string. We use flag, because -(INT_MIN) != (INT_MAX), and so the overflow of int_type varies if the value is below or above zero
int get_number(string::const_iterator &start, string::const_iterator finish, int flag){
	//Get the token
	Token tok = get_token(start, finish);
	//Start value of the res(which would be returned) is assigned as 0
	int res = 0;
	//Check if current symbol is really digit
	if(tok == Token :: Number){
		//Read while we can
		while(start != finish && isdigit(*start)){
			//Now in digit we have number from 0 to 9
			int digit = *start++ - '0';
			//If the number is below zero
			if(flag){
				//We check if the overflow's occured
				if(check_overflow_mul(res, 10) && check_overflow_sub(res * 10, digit)){
					//If all is fine, we process symbol
					res = res * 10 - digit;
				}
				else{
					//If the overflow's occured, we leave the program
					exit(process_errors(OVERFLOW));
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
					exit(process_errors(OVERFLOW));
				}
			}
		}
		//Return number that we've got
		return res;
	}
	//If current symbol isn't digit, the expression has the error in it
	exit(process_errors(WRONG_EXPRESSION));
}
//This is function for making this action: prim = number | -number, referring to calculator's grammatics
int get_prim(string::const_iterator &start, string::const_iterator finish) 
{
	//In flag we contain information if number is or isn't below zero
	int flag = 0;
	//Get the token
	Token tok = get_token(start, finish);
	if (tok == Token :: Minus) {
		//If it is below zero, we make flag up
		start++;
		flag = 1;
	}
	else if(tok == Token :: Plus){
		start++;
	}
	//Then we return the result of function get_number. Thar function already returns number with sign that we need
	return get_number(start, finish, flag);
}
//This is function for making this action: term = prim | term * prim | term / prim, referring to calculator's grammatics
int get_term(string::const_iterator &start, string::const_iterator finish) 
{
	//The res variable we move prim 
    int res = get_prim(start, finish);
    //We find what operation is it (Or it isn't operation)
    Token op = get_token(start, finish);
    while (start != finish && (op == Token::Mul || op == Token::Div)) {
		//While we can execute '*' or '/' operations, we do this
        start++;
        //In the val we move the value of another operand of expression(res*val or res/val)
        int val = get_prim(start, finish);
        if (op == Token::Mul) {
			//If it is multiplication, we check for overflow
			if(check_overflow_mul(res, val)){
				res *= val;
			}
			else{
				//If the overflow's occured, we leave the program
				exit(process_errors(OVERFLOW));
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
        op = get_token(start, finish);
    }
    //Check if the error's occured
    if(op == Token :: Error){
		//If the error's occured, we leave the program
		exit(process_errors(WRONG_EXPRESSION));
	}
    return res;
}


int main(int argc, char** argv) {
	//If the command line arguments don't fit into our standart, we don't do
	if(argc != 2){
		exit(process_errors(INVALID_NUMBER_OF_ARGUMENTS));
	}
	//Str is a string, that contains arithematic equation
	string str = argv[1];
	//Using const_iterators for iterating on the string
	string::const_iterator start = str.begin();
	string::const_iterator finish = str.end();
	if(start == finish){
		//If the string is empty, no actions are executed 
		return 0;
	}
	//In this part of program, expr = term | expr + term | expr - term is calculated
	//In get_term we've already calculated operations '*' and '/'
	int res = get_term(start, finish);
	//We get the token of operation
	Token op = get_token(start, finish);
	//We need to process remaining operations '+' and '-'
    while (op == Token::Plus || op == Token::Minus) {
        start++;
        //We got another result of already calculated operations '*' and '/'
        int val = get_term(start, finish);
        if (op == Token::Plus) {
			//We check for overflow
			if(check_overflow_sum(res,val)){
				res += val;
			}
			else{
				//If the overflow's occured, we leave the program
				exit(process_errors(OVERFLOW));
			}
		}
		else {
			//We check for overflow
			if(check_overflow_sub(res,val)){
				res -= val;
			}
			else{
				//If the overflow's occured, we leave the program
				exit(process_errors(OVERFLOW));
			}
		}
		//Then we get another token of operation
		op = get_token(start, finish);
    }
    //If we haven't read to the end
    if(op != Token::End)
		exit(process_errors(WRONG_EXPRESSION));
	printf("%d", res);
	return 0;
}
