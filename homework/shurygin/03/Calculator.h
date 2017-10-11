#pragma once
#include <string>
#include <sstream>

namespace MyConst
{
	const double pi = 3.14;
	const double e = 2.72;
	const double eps = 0.0001;
};

enum Token
{
	NUMBER,
	PLUS = '+',
	MINUS = '-',
	MULL = '*',
	DIV = '/',
	LB = '(',
	RB = ')',
	END = ' '
};

class Calculator
{
public:
	Calculator(std::string);
	double Calculate();
	~Calculator();
private:
	void GetToken();
	double Expr(bool);
	double Term(bool);
	double Prim(bool);
	std::string expr_;
	unsigned int index_;
	double number_;
	Token curr_token_;	
};

