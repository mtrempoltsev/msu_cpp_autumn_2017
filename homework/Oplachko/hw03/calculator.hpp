#pragma once
#include <string>
#include <unordered_map>

enum class Operation {
	add,
	sub,
	mul,
	div,
	notOp,
	endOfExpr
};

class Calculator
{
private:
	std::string s;
	std::string::const_iterator it;
	static std::unordered_map<std::string, double> constants;
	void skipSpaces();
	void backSkipSpaces();
	void nextTokenPos();
	void prevTokenPos();
	Operation getOpType();
	int getNumberSign();
	bool isThisConstant(const std::string &);
	double getConstant();
	double getNumber();
	double getPrim();
	double getExtPrim();
	double getTerm();
public:
	Calculator(const std::string &);
	double calcExpr(bool = false);
};
