#include "Grammar.h"
#include "Grammar.hpp"

//=========================================================================================

void GetExpression(std::string& expr, int count_args, char* args [])
{
	if (count_args < 2)
	{
		std::cout << "Please, enter an expression: ";
		std::getline(std::cin, expr);
	}
	else
	{
		expr = args [1];
	}
}

//=========================================================================================

int main(int count_args, char* args [])
{
	std::string source_str;
	GetExpression(source_str, count_args, args);

	return Calculator<double>::GetValue(source_str);
}