#include "Calculator.h"
#include <cmath>


Calculator::Calculator(std::string ex)
{
	expr_ = ex;
	index_ = 0;
}


double Calculator::Calculate()
{
	while (index_ < expr_.size())
	{
		GetToken();
		if (curr_token_ == END)
			break;
		double res = Expr(false);
		if(curr_token_ == END)
			return res;
		throw std::string("Invalid");
	}
	return 0.0;
}


Calculator::~Calculator()
{
}

void Calculator::GetToken()
{
	char c;
	bool operation = false;
	do
	{
		if (index_ >= expr_.size())
		{
			curr_token_ = END;
			return;
		}
		c = expr_[index_++];
	} while (c == ' ');
	switch (c)
	{
	case MULL:
	case DIV:
	case PLUS:
	case MINUS:
	case LB:
	case RB:
		curr_token_ = Token(c);
		operation = true;
	}

	if (c >= '0' && c <= '9')
	{
		std::string strNumber;
		strNumber.push_back(c);
		while (index_ < expr_.size())
		{
			c = expr_[index_];
			if (c >= '0' && c <= '9')
			{
				index_++;
				strNumber.push_back(c);
			}
			else
				break;
		}
		std::stringstream ss;
		ss << strNumber;
		ss >> number_;
		curr_token_ = NUMBER;
	}
	else if (c == 'P')
	{
		if (expr_[index_] == 'i')
		{
			number_ = MyConst::pi;
			curr_token_ = NUMBER;
			index_++;
		}
	}
	else if (c == 'e')
	{		
		number_ = MyConst::e;
		curr_token_ = NUMBER;
	}
	else if (!operation)
	{
		throw std::string("Invalid");
	}
}

double Calculator::Expr(bool getToken)
{
	double left = Term(getToken);
	while (1)
	{
		switch (curr_token_)
		{
		case PLUS:
			left += Term(true);
			break;
		case MINUS:
			left -= Term(true);
			break;
		default:
			return left;
		}
	}
	return 0;
}

double Calculator::Term(bool getToken)
{
	double left = Prim(getToken);
	while (1)
	{
		switch (curr_token_)
		{
		case MULL:
			left *= Prim(true);
			break;
		case DIV:
		{
			double a = Prim(true);
			if (std::abs(a) > MyConst::eps)
			{
				left /= a;
				break;
			}
			throw std::string("Divide by zero");
		}
		default:
			return left;
		}
	}
	return 0;
}

double Calculator::Prim(bool getToken)
{
	if (getToken)
	{
		GetToken();
	}
	switch (curr_token_)
	{
	case NUMBER:
	{
		double val = number_;
		GetToken();
		return val;
	}
	case MINUS:
		return -Prim(true);
	case LB:
	{
		double ex = Expr(true);
		if (curr_token_ != RB)
			throw std::string("Not balance break");
		GetToken();
		return ex;
	}
	default:
		throw std::string("Invalid");
	}
	return 0;
}
