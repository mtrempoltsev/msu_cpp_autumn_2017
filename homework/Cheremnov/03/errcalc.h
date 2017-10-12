#pragma once

#include <iostream>
#include <limits.h>

enum
{
	//Error when user enters more or less arguments than is required
	INVALID_NUMBER_OF_ARGUMENTS = 1,
	
	//Error when overflow occures
	OVERFLOW = 2,
	
	//Error when user enters wrong expression
	INVALID_EXPRESSION = 3,
	
	//Error when in user's expression is found division by zero
	DIVISION_BY_ZERO = 4,
	
	//Error when user enters invalid constant
	INVALID_CONSTANT = 5,
	
	//Error when brackets are mismatched
	MISMATCHED_BRACKET = 6
	
};

//In this function we process errors.
int process_errors(int errcode)
{
	switch(errcode){
		case INVALID_NUMBER_OF_ARGUMENTS:
			std::cout << "You've entered invalid number of command line arguments" << std::endl;
			return INVALID_NUMBER_OF_ARGUMENTS; 
		case OVERFLOW:
			std::cout << "The calculator can't calculate this expression due to overflow" << std::endl;
			return OVERFLOW;
		case INVALID_EXPRESSION:
			std::cout << "Invalid construction of expression" << std::endl;
			return INVALID_EXPRESSION;
		case DIVISION_BY_ZERO:
			std::cout << "In the expression is found division by zero. Stopping the programm" << std::endl;
			return DIVISION_BY_ZERO;
		case INVALID_CONSTANT:
			std::cout << "Invalid constant is entered" << std::endl;
			return INVALID_CONSTANT;
		default:
			//If errcode doesn't match any error code
			std::cout << "Unexpected error. Aborting program execution" << std::endl;
			return -1;
	}
}

//We check if multiplication will result in overflow
bool check_overflow_mul(double a1, double b1)
{
	int a = (int) a1;
	int b = (int) b1;
	if((a == 0) || (b == 0))
		return 1;
	//Check if multiplication will give the result above or equal to zero. 
	//If a * b > 0, then must be held a * b <= INT_MAX
	//If a * b < 0, then must be held a * b >= INT_MIN 
	if(a > 0 && b > 0)
		return a <= INT_MAX / b;
	if(a > 0 && b < 0)
		return a <= INT_MIN / b;
	if(a < 0 && b > 0)
		return a >= INT_MIN / b;
	return a >= INT_MAX / b;
}

//We check if summation will result in overflow
bool check_overflow_sum(double a1, double b1)
{
	int a = (int) a1;
	int b = (int) b1;
	//If a + b < INT_MIN, summation results in overflow
	if(a < 0 && b < 0)
		return a >= INT_MIN - b;
	//If a + b > INT_MAX, summation results in overflow
	if(a > 0 && b > 0)
		return a <= INT_MAX - b;
	//If a and b are different signs, overflow won't occure
	return 1;
}

//We check if subtraction will result in overflow
bool check_overflow_sub(double a1, double b1)
{
	int a = (int) a1;
	int b = (int) b1;
	//if b == INT_MIN, -(INT_MIN), will result in overflow
	if(b == INT_MIN)
		return 0;
	return check_overflow_sum(a, (-1) * b);
}
