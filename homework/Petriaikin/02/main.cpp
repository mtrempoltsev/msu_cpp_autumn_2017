#include <iostream>
#include <string>

#include "Parser.h"

#define ERROR_CODE 1

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
	expr.erase(std::remove(expr.begin(), expr.end(), ' '), expr.end()); //Игнорируем пробелы
}

//=========================================================================================

int main(int count_args, char* args [])
{
	std::string source_str;
	GetExpression(source_str, count_args, args);

	int result = 0;
	int final_position = 0;
	try //Может быть деление на 0!
	{
		final_position = GetBinaryGrammarElementFromString(source_str, 0, Grammar_c [0], result, true);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return ERROR_CODE;
	}

	if (final_position != source_str.length()) //Разбор не дошел до конца - вероятно, встретился неизвестный символ
	{
		if (final_position < 0) { final_position = -final_position - 1; } //Т.к. был передан -pos-1

		std::cout << source_str << std::endl;
		std::cout << std::string(final_position, ' ') << '^' << std::endl;
		std::cout << "There is in error in the input string near the marked position" << std::endl;
		return ERROR_CODE;
	}
	else
	{
		std::cout << result << std::endl;
	}
	return 0;
}