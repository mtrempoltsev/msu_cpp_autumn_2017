#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <regex>

#include "Grammar.h"

#define ERROR_CODE 1

//=========================================================================================

const std::unordered_map<std::string, std::string> constants_c =
{
	{"Pi", "3.14"},
	{"e", "2.7"}
};

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
	expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end()); //Игнорируем пробелы

	for (auto pair : constants_c)
	{
		expr = std::regex_replace(expr, std::regex(pair.first), pair.second);
	}
}

//=========================================================================================

int main(int count_args, char* args [])
{
	std::string source_str;
	GetExpression(source_str, count_args, args);

	int final_position = 0;
	
	try //Могут быть исключения!
	{
		SumDifference grammar(source_str.c_str(), 0);
		final_position = grammar.GetShift();

		if (final_position != source_str.length()) //Разбор не дошел до конца - вероятно, встретился неизвестный символ
		{
			std::cout << source_str << std::endl;
			std::cout << std::string(final_position, ' ') << '^' << std::endl;
			std::cout << "There is in error in the input string near the marked position" << std::endl;
			return ERROR_CODE;
		}
		else
		{
			std::cout << grammar.GetValue() << std::endl;
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return ERROR_CODE;
	}

	return 0;
}